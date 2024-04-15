#include <algorithm>
#include "input.h"

namespace
{
    std::vector<SDL_Event> events;
}

void input::update_events(const std::vector<SDL_Event> &events)
{
    ::events = events;
}

bool input::key_down(SDL_KeyCode key)
{
    auto predicate = [key](const SDL_Event &event) { return event.type == SDL_KEYDOWN && event.key.keysym.sym == key; };

    return std::any_of(events.begin(), events.end(), predicate);
}
