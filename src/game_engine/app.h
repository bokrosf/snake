#ifndef SNAKE_GAMEENGINE_APP_H
#define SNAKE_GAMEENGINE_APP_H

#include <string>
#include <SDL2/SDL.h>
#include <game_engine/collision/collision_engine.h>
#include <game_engine/component_added.h>
#include <game_engine/component_destroyed.h>
#include <game_engine/entity_created.h>
#include <game_engine/entity_destroyed.h>
#include <game_engine/entity_parent_changed.h>
#include <game_engine/messaging/messenger.h>
#include <game_engine/messaging/recipient.h>
#include <game_engine/scene.h>

class app : 
    public recipient<entity_created>,
    public recipient<entity_destroyed>,
    public recipient<component_added>,
    public recipient<component_destroyed>,
    public recipient<entity_parent_changed>
{
public:
    virtual ~app();
    void run();
    void receive(const entity_created &message) final;
    void receive(const entity_destroyed &message) final;
    void receive(const component_added &message) final;
    void receive(const component_destroyed &message) final;
    void receive(const entity_parent_changed &message) final;
protected:
    app(const std::string &app_name);
    messenger &_messenger;
    virtual scene *create_start_scene() = 0;
private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    scene *_active_scene;
    bool _running;
    collision_engine _collision_engine;
    const std::string _app_name;
    void initialize_subsystems();
    void shutdown();
    void shutdown_subsystems();
    void handle_user_input();
    void update_game_state();
    void render();
};

#endif
