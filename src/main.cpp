#include <iostream>
#include <exception>
#include <SDL2/sdl.h>
#include "game_engine/app.h"
#include "game_engine/logging/logger.h"
#include "game_engine/logging/console_logger.h"
#include "game/snake_app.h"

void sdl_test();

int main(int argc, char *argv[])
{
    console_logger::initialize();
    
    try
    {
        app *app = new snake_app();
        app->run();

        return 0;
    }
    catch (const std::exception &ex)
    {
        logger::instance().error(ex.what());
        return 1;
    }
}

void sdl_test()
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        std::cout << "Init failed." << std::endl;
        return;
    }

    SDL_Window *window = nullptr;
    window = SDL_CreateWindow("Snake SDL", 200, 200, 800, 600, SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cout << "Window Creation failed." << std::endl;
        return;
    }

    SDL_Renderer *renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        std::cout << "Renderer Creation failed." << std::endl;
    }

    SDL_Event event;
    bool running = true;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            std::cout << "event: " << event.type << std::endl;

            if (event.type == SDL_EventType::SDL_QUIT)
            {
                running = false;
            }
            else if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);

        SDL_Rect rect;
        rect.x = 100;
        rect.y = 200;
        rect.w = 300;
        rect.h = 200;

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
    }    

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_Quit();
}
