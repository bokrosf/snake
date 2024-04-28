#include <sstream>
#include <stdexcept>
#include <engine/display.h>
#include <engine/subsystem_initialization_failed.h>

namespace
{
    bool initialized = false;
    const int display_id = 0;
}

void display::initialize()
{
    if (initialized)
    {
        throw std::logic_error("Display subsystem already initialized.");
    }
    
    if (int display_count = SDL_GetNumVideoDisplays(); display_count < 1)
    {
        throw subsystem_initialization_failed(std::string("No video display available.").append(SDL_GetError()));
    }
   
    initialized = true;
}

SDL_DisplayMode display::current_mode()
{
    if (!initialized)
    {
        throw std::logic_error("Display subsystem must be initialized before querying the current display mode.");
    }
    
    SDL_DisplayMode display_mode;

    if (SDL_GetCurrentDisplayMode(display_id, &display_mode) != 0)
    {
        std::stringstream error("Current display mode querying failed. ");
        error << "display_id: " << display_id << " " << SDL_GetError();
        
        throw std::runtime_error(error.str());
    }

    return display_mode;
}
