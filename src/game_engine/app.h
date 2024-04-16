#ifndef SNAKE_GAMEENGINE_APP_H
#define SNAKE_GAMEENGINE_APP_H

#include <string>
#include <SDL2/SDL.h>
#include "messaging/messenger.h"
#include "messaging/recipient.h"
#include "scene.h"
#include "game_object_created.h"
#include "game_object_destroyed.h"
#include "component_added.h"
#include "game_object_parent_changed.h"

class app : 
    public recipient<game_object_created>,
    public recipient<game_object_destroyed>,
    public recipient<component_added>, 
    public recipient<game_object_parent_changed>
{
public:
    app(const std::string &app_name);
    virtual ~app();
    void run();
    void receive(const game_object_created &message) final;
    void receive(const game_object_destroyed &message) final;
    void receive(const component_added &message) final;
    void receive(const game_object_parent_changed &message) final;
protected:
    messenger &_messenger;
    virtual scene *create_start_scene() = 0;
private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    scene *_active_scene;
    bool _running;
    const std::string _app_name;
    void initialize_subsystems();
    void shutdown();
    void shutdown_subsystems();
    void detect_collisions();
    void handle_user_input();
    void update_game_state();
    void render();
};

#endif
