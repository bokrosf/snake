#ifndef SNAKE_GAME_GAMECOORDINATOR_H
#define SNAKE_GAME_GAMECOORDINATOR_H

#include <unordered_set>
#include <engine/component/behavior.h>
#include <engine/component/initializable.h>
#include <engine/component/startable.h>
#include <engine/component/updatable.h>
#include <engine/messaging/recipient.h>
#include <game/food/food_spawner.h>
#include <game/game_event.h>
#include <game/game_start_requirement.h>

class game_coordinator 
    : public behavior
    , public initializable
    , public updatable
    , public recipient<game_event>
    , public recipient<game_start_requirement>
{
public:
    game_coordinator();
    ~game_coordinator() override;
    void initialize() override;
    void update() override;
    void receive(const game_event &message) override;
    void receive(const game_start_requirement &message) override;
private:
    void start_game();

    food_spawner *_food_spawner;
    std::unordered_set<game_start_requirement> _start_requirements;
};

#endif
