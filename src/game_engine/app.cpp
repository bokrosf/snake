#include <map>
#include <queue>
#include <vector>
#include <ranges>
#include "app.h"
#include "component/behavior.h"
#include "component/renderer.h"
#include "component/updatable.h"
#include "game_time.h"
#include "input.h"
#include "subsystem_initialization_failed.h"

app::app(const std::string &app_name)
    : _messenger(messenger::instance())
    , _window(nullptr)
    , _renderer(nullptr)
    , _active_scene(nullptr)
    , _running(false)
    , _app_name(app_name)
{
}

app::~app()
{
    shutdown();
}

void app::run()
{
    initialize_subsystems();
    _messenger.subscribe<game_object_created>(*this);
    _messenger.subscribe<game_object_destroyed>(*this);
    _messenger.subscribe<component_added>(*this);
    _messenger.subscribe<game_object_parent_changed>(*this);
    _active_scene = create_start_scene();
    _active_scene->initialize();
    _running = true;

    Uint64 frame_started_at = 0;
    Uint64 frame_ended_at = 0;

    while (_running)
    {
        // TODO 2024-04-10 Implement GameLoop.
        // [x] Frame start time recording.
        // [x] Initialize components.
        // [] Detect collisions
        // [x] Handle user input.
        // [x] Logic:
        //      [x] Update game state by traversing the game_object tree.
        //      [x] Don't process Inactive game_object subtree.
        //      [x] Only active behaviors updated.
        // [x] Delete game_objects marked for deletion.
        // [x] Graphical rendering.
        // [x] Frame end time recording.
        // [x] Delta-time update.
        _active_scene->initialize_components();
        handle_user_input();
        update_game_state();
        _active_scene->destroy_marked_objects();
        render();
        frame_ended_at = SDL_GetTicks64();
        game_time::update_delta_time(frame_started_at, frame_ended_at);
        frame_started_at = frame_ended_at;
    }

    shutdown();
}

void app::initialize_subsystems()
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        throw subsystem_initialization_failed("SDL Video initialization failed. " + std::string(SDL_GetError()));
    }

    SDL_Window *window = SDL_CreateWindow(_app_name.c_str(), 0, 0, 1920, 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);

    if (!window)
    {
        throw subsystem_initialization_failed("SDL Window creation failed. " + std::string(SDL_GetError()));
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        throw subsystem_initialization_failed("SDL Renderer creation failed. " + std::string(SDL_GetError()));
    }

    _window = window;
    _renderer = renderer;
}

void app::shutdown()
{
    _messenger.unsubscribe<game_object_created>(*this);
    _messenger.unsubscribe<game_object_destroyed>(*this);
    _messenger.unsubscribe<component_added>(*this);
    _messenger.unsubscribe<game_object_parent_changed>(*this);
    shutdown_subsystems();
}

void app::shutdown_subsystems()
{
    if (_renderer)
    {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }

    if (_window)
    {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }

    SDL_Quit();
}

void app::detect_collisions()
{
    // TODO 2024-04-10 Implement.
}

void app::handle_user_input()
{
    SDL_Event current_event;
    std::vector<SDL_Event> events;

    while (SDL_PollEvent(&current_event))
    {
        
        if (current_event.type == SDL_EventType::SDL_QUIT)
        {
            _running = false;
            return;
        }
        else if (current_event.key.keysym.sym == SDLK_ESCAPE)
        {
            _running = false;
            return;
        }

        events.push_back(current_event);
    }

    input::update_events(events);
}

void app::update_game_state()
{
    std::queue<game_object *> checked_objects;
    std::vector<updatable *> updatables;
    auto active_object = [](const game_object *object) { return object->active(); };

    for (game_object *root : std::views::filter(_active_scene->root_objects(), active_object))
    {
        checked_objects.push(root);
    }

    while (!checked_objects.empty())
    {
        game_object *object = checked_objects.front();
        checked_objects.pop();
        
        for (behavior *b : object->all_attached_components<behavior>() | std::views::filter([](behavior *b) { return b->active(); }))
        {
            updatables.push_back(b);
        }

        for (game_object *child : std::views::filter(object->children(), active_object))
        {
            checked_objects.push(child);
        }
    }

    for (updatable *u : updatables)
    {
        u->update();
    }
}

void app::render()
{
    std::queue<const game_object *> checked_objects;
    std::map<int, std::vector<renderer *>> rendering_layers;
    auto active_object = [](game_object *object) { return object->active(); };

    for (const game_object *root : std::views::filter(_active_scene->root_objects(), active_object))
    {
        checked_objects.push(root);
    }

    while (!checked_objects.empty())
    {
        const game_object *object = checked_objects.front();
        checked_objects.pop();

        if (renderer *r = object->find_component<renderer>())
        {
            rendering_layers[r->layer_order()].push_back(r);
        }
        
        for (const game_object *child : std::views::filter(object->children(), active_object))
        {
            checked_objects.push(child);
        }
    }

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    for (const auto &[layer, renderers] : rendering_layers)
    {
        for (renderer *r : renderers)
        {
            r->render(_renderer);
        }
    }

    SDL_RenderPresent(_renderer);
}

void app::receive(const game_object_created &message)
{
    _active_scene->update_root_status(message.created);
}

void app::receive(const game_object_destroyed &message)
{
    _active_scene->mark_as_destroyed(message.object);
}

void app::receive(const component_added &message)
{
    _active_scene->register_added_component(message.added);
}

void app::receive(const game_object_parent_changed &message)
{
    _active_scene->update_root_status(message.object);
}
