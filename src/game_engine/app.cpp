#include "app.h"
#include "subsystem_initialization_failed.h"

app::app(const std::string &app_name)
    : _messenger(messenger::instance())
    , _window(nullptr)
    , _renderer(nullptr)
    , _running(false)
    , _app_name(app_name)
{
}

app::~app()
{
    shutdown_subsystems();
}

void app::run()
{
    initialize_subsystems();
    start();

    while (_running)
    {
        // TODO 2024-04-10 Implement GameLoop.
    }

    shutdown_subsystems();
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

void app::initialize_components()
{
    // TODO 2024-04-10 Implement.
}

void app::detect_collisions()
{
    // TODO 2024-04-10 Implement.
}

void app::handle_user_input()
{
    // TODO 2024-04-10 Implement.
}

void app::update_game_state()
{
    // TODO 2024-04-10 Implement.
}

void app::render()
{
    // TODO 2024-04-10 Implement.
}
