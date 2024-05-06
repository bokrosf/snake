#include <game/game_coordinator.h>

game_coordinator::game_coordinator(entity &attached_to)
    : component(attached_to)
    , _food_spawner(nullptr)
{
}

game_coordinator::~game_coordinator()
{
    _messenger.unsubscribe<game_event>(*this);
}

void game_coordinator::initialize()
{
    _food_spawner = &attached_to().attached_component<food_spawner>();
    _messenger.subscribe<game_event>(*this);
}

void game_coordinator::start()
{
    _food_spawner->spawn();
}

void game_coordinator::receive(const game_event &message)
{
    switch (message)
    {
        case game_event::food_eaten:
            _food_spawner->spawn();
            break;
        case game_event::food_storage_depleted:
            win_game();
            break;
        case game_event::game_lost:
            lose_game();
            break;
    }
}

void game_coordinator::win_game()
{
    // TODO 2024-05-06 Implement.
}

void game_coordinator::lose_game()
{
    // TODO 2024-05-06 Implement.
}
