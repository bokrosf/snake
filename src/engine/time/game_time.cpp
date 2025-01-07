#include <unordered_map>
#include <vector>
#include <SDL2/SDL.h>
#include <engine/time/game_time.h>
#include <engine/time/time_point.h>

namespace
{
    const float precision = 0.001F;

    struct context
    {
        context(game_time::context_id);

        const game_time::context_id id;
        Uint64 switched_away;
        std::vector<time_point *> bound_times;
    };

    std::unordered_map<game_time::context_id, context> contexts;
    context *current;
    Uint64 frame_started_at;
    float delta = 0;
}

::context::context(game_time::context_id id)
    : id(id)
    , switched_away(0)
{
}

void game_time::initialize(game_time::context_id id)
{
    current = &contexts.emplace(id, id).first->second;
    frame_started_at = SDL_GetTicks64();
}

void game_time::reset(game_time::context_id id)
{
    Uint64 now = SDL_GetTicks64();

    if (current)
    {
        current->switched_away = now;
    }

    current = &contexts.try_emplace(id, id).first->second;
    frame_started_at = now;
    ::delta = 0;
    float switch_duration = precision * (now - current->switched_away);

    for (auto *bounded : current->bound_times)
    {
        bounded->_seconds += switch_duration;
    }
}

void game_time::erase(context_id id)
{
    contexts.erase(id);

    if (current && current->id == id)
    {
        current = nullptr;
    }
}

void game_time::end_frame()
{
    Uint64 now = SDL_GetTicks64();
    ::delta = precision * (now - frame_started_at);
    frame_started_at = now;
}

float game_time::delta()
{
    return ::delta;
}

float game_time::now()
{
    return precision * frame_started_at;
}

float game_time::real_now()
{
    return precision * SDL_GetTicks64();
}

game_time::context_id game_time::bind(time_point &time)
{
    current->bound_times.emplace_back(&time);

    return current->id;
}

void game_time::unbind(context_id id, time_point &bounded)
{
    std::erase(contexts.at(id).bound_times, &bounded);
}