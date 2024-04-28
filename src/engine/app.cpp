#include <vector>
#include <engine/app.h>
#include <engine/component/behavior.h>
#include <engine/component/updatable.h>
#include <engine/display.h>
#include <engine/game_time.h>
#include <engine/input.h>
#include <engine/scene_traversal.h>
#include <engine/subsystem_initialization_failed.h>

app::app(const std::string &app_name)
    : _messenger(messenger::instance())
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
        _rendering_engine.render(*_active_scene);
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
        throw subsystem_initialization_failed(std::string("SDL initialization failed.").append(SDL_GetError()));
    }

    display::initialize(_app_name);
    _rendering_engine.initialize(display::window());
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
    display::shutdown();
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
