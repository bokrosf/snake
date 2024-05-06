#ifndef SNAKE_GAME_GAMECOORDINATOR_H
#define SNAKE_GAME_GAMECOORDINATOR_H

#include <engine/component/component.h>
#include <engine/component/initializable.h>
#include <engine/component/startable.h>
#include <engine/entity.h>
#include <engine/messaging/recipient.h>
#include <game/food/food_spawner.h>
#include <game/game_event.h>

class game_coordinator : public component, public initializable, public startable, public recipient<game_event>
{
public:
    game_coordinator(entity &attached_to);
    ~game_coordinator() override;
    void initialize() override;
    void start() override;
    void receive(const game_event &message) override;
private:
    void win_game();
    void lose_game();

    food_spawner *_food_spawner;
};

#endif