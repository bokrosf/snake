#ifndef SNAKE_GAME_ABILITY_ABILITYSLOT_H
#define SNAKE_GAME_ABILITY_ABILITYSLOT_H

#include <concepts>
#include <SDL2/SDL.h>
#include <engine/component/component.h>
#include <engine/component/initializable.h>
#include <engine/entity.h>
#include <game/ability/ability.h>
#include <game/ability/ability_indicator.h>
#include <game/ability/ability_indicator_renderer.h>

class ability_slot : public component, public initializable
{
public:
    ability_slot(entity &attached_to);
    void initialize() override;
    void detach() override;
    void remove();

    template<typename Ability>
        requires std::derived_from<Ability, ability>
    void add(SDL_Color color, float duration);
private:
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
    _indicator->track(*_ability);
    _indicator_renderer->change_material(material{color});
}

#endif
