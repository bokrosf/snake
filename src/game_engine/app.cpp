#include <map>
#include <queue>
#include <vector>
#include "app.h"
#include "component/renderer.h"
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
    _messenger.subscribe<component_added>(*this);
    _messenger.subscribe<game_object_parent_changed>(*this);
    _active_scene = create_start_scene();
    _active_scene->initialize();
    _running = true;

    while (_running)
    {
        // TODO 2024-04-10 Implement GameLoop.
        // [] Frame start time recording.
        // [x] Initialize components.
        // [] Detect collisions
        // [] Handle user input.
        // [] Logic:
        //      [] Update game state by traversing the game_object tree.
        //      [] Don't process Inactive game_object subtree.
        //      [] Only active behaviors updated.
        // [x] Graphical rendering.
        // [] Frame end time recording.
        // [] Delta-time update.
        
        _active_scene->initialize_components();
        handle_user_input();
        render();
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
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EventType::SDL_QUIT)
        {
            _running = false;
        }
        else if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            _running = false;
        }
    }

    // TODO 2024-04-10 Implement.
}

void app::update_game_state()
{
    // TODO 2024-04-10 Implement.
}

void app::render()
{
    std::queue<const game_object *> checked_objects;
    std::map<int, std::vector<renderer *>> rendering_layers;

    for (const game_object *root : _active_scene->root_objects())
    {
        checked_objects.push(root);
    }

    while (!checked_objects.empty())
    {
        const game_object *object = checked_objects.front();
        checked_objects.pop();

        if (object->active())
        {
            if (renderer *r = object->find_component<renderer>())
            {
                rendering_layers[r->layer_order()].push_back(r);
            }
            
            for (const game_object *child : object->children())
            {
                checked_objects.push(child);
            }
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

void app::receive(const component_added &message)
{
    _active_scene->register_added_component(message.added);
}

void app::receive(const game_object_parent_changed &message)
{
    _active_scene->update_root_status(message.object);
}
