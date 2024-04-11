#ifndef SNAKE_GAMEENGINE_APP_H
#define SNAKE_GAMEENGINE_APP_H

#include <string>
#include <SDL2/SDL.h>
#include "messaging/messenger.h"
#include "scene.h"

class app
{
public:
    app(const std::string &app_name);
    virtual ~app();
    void run();
protected:
    messenger &_messenger;
    virtual scene *start() = 0;
private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    scene *_active_scene;
    bool _running;
    const std::string _app_name;
    void initialize_subsystems();
    void shutdown_subsystems();
    void detect_collisions();
    void handle_user_input();
    void update_game_state();
    void render();
};

#endif
