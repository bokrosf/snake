#ifndef SNAKE_GAME_ABILITY_ABILITYSLOT_H
#define SNAKE_GAME_ABILITY_ABILITYSLOT_H

#include <concepts>
#include <SDL2/SDL.h>
#include <engine/component/component.h>
#include <engine/component/initializable.h>
#include <engine/entity.h>
#include <engine/messaging/recipient.h>
#include <game/ability/ability.h>
#include <game/ability/ability_expired.h>
#include <game/ability/ability_indicator.h>
#include <game/ability/ability_indicator_renderer.h>

class ability_slot : public component, public initializable, public recipient<ability_expired>
{
public:
    ability_slot(entity &attached_to);
    ~ability_slot() override;
    void initialize() override;
    void detach() override;
    void receive(const ability_expired &message) override;

    template<typename Ability>
        requires std::derived_from<Ability, ability>
    void add(SDL_Color color, float duration);
private:
    void remove();

    ability *_ability;
    ability_indicator *_indicator;
    ability_indicator_renderer *_indicator_renderer;
};

template<typename Ability>
    requires std::derived_from<Ability, ability>
void ability_slot::add(SDL_Color color, float duration)
{
    remove();
    _ability = &attached_to().add_component<Ability>(duration);
    _messenger.subscribe<ability_expired>(*this);
    _indicator->track(*_ability);
    _indicator_renderer->material(material{color});
}

#endif