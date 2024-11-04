#include <engine/entity.h>
#include <engine/input.h>
#include <game/game_coordinator.h>
#include <game/scene/game_ending_scene.h>
#include <game/scene/pause_scene.h>
#include <game/scene/scene_navigator.h>

game_coordinator::game_coordinator()
    : _food_spawner(nullptr)
{
    _start_requirements.insert(game_start_requirement::food_spawner_ready);
}

game_coordinator::~game_coordinator()
{
    _messenger.unsubscribe<game_event>(*this);
    _messenger.unsubscribe<game_start_requirement>(*this);
}

void game_coordinator::initialize()
{
    _food_spawner = &attached_to().attached_component<food_spawner>();
    _messenger.subscribe<game_event>(*this);
    _messenger.subscribe<game_start_requirement>(*this);
}

void game_coordinator::update()
{
    if (input::key_down(SDLK_ESCAPE) || input::key_down(SDLK_p))
    {
        scene_navigator::instance().push<pause_scene>();
    }
}

void game_coordinator::receive(const game_event &message)
{
    switch (message)
    {
        case game_event::food_eaten:
            _food_spawner->spawn();
            break;
        case game_event::food_storage_depleted:
            scene_navigator::instance().push<game_ending_scene>(true);
            break;
        case game_event::game_lost:
            scene_navigator::instance().push<game_ending_scene>(false);
            break;
    }
}

void game_coordinator::receive(const game_start_requirement &message)
{
    _start_requirements.erase(message);
    
    if (_start_requirements.empty())
    {
        _messenger.unsubscribe<game_start_requirement>(*this);
        start_game();
    }
}

void game_coordinator::start_game()
{
    if (!_start_requirements.empty())
    {
        return;
    }

    _food_spawner->spawn();
}
