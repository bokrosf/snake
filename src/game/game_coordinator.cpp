#include <game/game_coordinator.h>

game_coordinator::game_coordinator(entity &attached_to)
    : component(attached_to)
    , _food_spawner(nullptr)
    , _ending_renderer(nullptr)
{
}

game_coordinator::~game_coordinator()
{
    _messenger.unsubscribe<game_event>(*this);
}

void game_coordinator::initialize()
{
    _food_spawner = &attached_to().attached_component<food_spawner>();
    _ending_renderer = &attached_to().attached_component<game_ending_renderer>();
    _messenger.subscribe<game_event>(*this);
}

void game_coordinator::start()
{
    _food_spawner->spawn();
    _ending_renderer->activate(false);
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
    if (!_ending_renderer->material())
    {
        _ending_renderer->change_material(material());
    }

    _ending_renderer->material()->color = SDL_Color{0, 255, 0, 255};
    _ending_renderer->activate(true);
}

void game_coordinator::lose_game()
{
    // TODO 2024-05-06 Implement.
}
