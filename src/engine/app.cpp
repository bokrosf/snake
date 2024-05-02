#include <engine/app.h>
#include <engine/display.h>
#include <engine/game_time.h>
#include <engine/input.h>
#include <engine/subsystem_initialization_failed.h>

app::app(const app_configuration &configuration)
    : _configuration(configuration)
    , _messenger(messenger::instance())
    , _active_scene(nullptr)
    , _running(false)
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
        _gameplay_engine.update(*_active_scene);
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

    display::initialize(_configuration.title);
    _rendering_engine.initialize(display::window());
}

void app::shutdown()
{
    _messenger.unsubscribe<entity_created>(*this);
    _messenger.unsubscribe<entity_destroyed>(*this);
    _messenger.unsubscribe<component_added>(*this);
    _messenger.unsubscribe<component_destroyed>(*this);
    _messenger.unsubscribe<entity_parent_changed>(*this);
    display::shutdown();
    SDL_Quit();
}

void app::handle_user_input()
{
    input::read_events();
    
    if (input::occured(SDL_QUIT) || input::key_down(SDLK_ESCAPE))
    {
        _running = false;
    }
}
