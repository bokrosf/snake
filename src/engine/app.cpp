#include <map>
#include <queue>
#include <ranges>
#include <vector>
#include <engine/app.h>
#include <engine/component/behavior.h>
#include <engine/component/renderer.h>
#include <engine/component/updatable.h>
#include <engine/display.h>
#include <engine/game_time.h>
#include <engine/input.h>
#include <engine/scene_traversal.h>
#include <engine/subsystem_initialization_failed.h>

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
    _messenger.subscribe<entity_created>(*this);
    _messenger.subscribe<entity_destroyed>(*this);
    _messenger.subscribe<component_added>(*this);
    _messenger.subscribe<component_destroyed>(*this);
    _messenger.subscribe<entity_parent_changed>(*this);
    _active_scene = create_start_scene();
    _active_scene->initialize();
    _running = true;
    
    while (_running)
    {
        _active_scene->initialize_components();
        _collision_engine.detect_collisions(*_active_scene);
        handle_user_input();
        update_game_state();
        _active_scene->destroy_marked_objects();
        render();
        game_time::end_frame();
    }

    shutdown();
}

void app::receive(const entity_created &message)
{
    _active_scene->update_root_status(message.created);
}

void app::receive(const entity_destroyed &message)
{
    _active_scene->mark_as_destroyed(message.entity);
}

void app::receive(const component_added &message)
{
    _active_scene->register_added_component(message.added);
}

void app::receive(const component_destroyed &message)
{
    _active_scene->mark_as_destroyed(message.component);
}

void app::receive(const entity_parent_changed &message)
{
    _active_scene->update_root_status(message.entity);
}

void app::initialize_subsystems()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw subsystem_initialization_failed(std::string("SDL Video initialization failed. ").append(SDL_GetError()));
    }

    display::initialize();
    SDL_DisplayMode display_mode = display::current_mode();
    SDL_Window *window = SDL_CreateWindow(_app_name.c_str(), 0, 0, display_mode.w, display_mode.h, SDL_WINDOW_SHOWN);

    if (!window)
    {
        throw subsystem_initialization_failed(std::string("SDL Window creation failed. ").append(SDL_GetError()));
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        throw subsystem_initialization_failed(std::string("SDL Renderer creation failed. ").append(SDL_GetError()));
    }

    _window = window;
    _renderer = renderer;
}

void app::shutdown()
{
    _messenger.unsubscribe<entity_created>(*this);
    _messenger.unsubscribe<entity_destroyed>(*this);
    _messenger.unsubscribe<component_added>(*this);
    _messenger.unsubscribe<component_destroyed>(*this);
    _messenger.unsubscribe<entity_parent_changed>(*this);
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

void app::handle_user_input()
{
    std::vector<SDL_Event> events;
    SDL_Event current_event;

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

    input::update_events(std::move(events));
}

void app::update_game_state()
{
    std::vector<updatable *> updatables;
    
    auto add_updatable = [&updatables](entity *entity)
    {
        auto cast_to_updatable = [](behavior *b) { return dynamic_cast<updatable *>(b); };
        auto filter = [cast_to_updatable](behavior *b) { return cast_to_updatable(b) && b->active(); };
        
        for (updatable *u : entity->all_attached_components<behavior>() | std::views::filter(filter) | std::views::transform(cast_to_updatable))
        {
            updatables.push_back(u);
        }
    };

    scene_traversal::traverse(*_active_scene, scene_traversal::filter_active_entity, add_updatable);

    for (updatable *u : updatables)
    {
        u->update();
    }
}

void app::render()
{
    std::map<int, std::vector<renderer *>> rendering_layers;
    
    auto add_layer = [&rendering_layers](entity *entity)
    {
        for (renderer *r : entity->all_attached_components<renderer>())
        {
            rendering_layers[r->layer_order()].push_back(r);
        }
    };

    scene_traversal::traverse(*_active_scene, scene_traversal::filter_active_entity, add_layer);
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
