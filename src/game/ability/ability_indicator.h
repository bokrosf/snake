#ifndef SNAKE_GAME_ABILITY_ABILITYINDICATOR_H
#define SNAKE_GAME_ABILITY_ABILITYINDICATOR_H

#include <engine/component/behavior.h>
#include <engine/component/initializable.h>
#include <engine/entity.h>
#include <engine/messaging/recipient.h>
#include <game/ability/ability.h>
#include <game/ability/ability_expired.h>
#include <game/ability/ability_usage_changed.h>

class ability_indicator : public behavior, public initializable, public recipient<ability_usage_changed>, public recipient<ability_expired>
{
public:
    ability_indicator(entity &attached_to);
    ~ability_indicator() override;
    void initialize() override;
    void track(::ability &ability);
    float percentage() const;
    void receive(const ability_usage_changed &message);
    void receive(const ability_expired &message);
private:
    void stop_tracking();

    float _percentage;
    ability *_ability;
};

#endif