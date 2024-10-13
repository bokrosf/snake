#ifndef SNAKE_GAME_ABILITY_ABILITYSLOT_H
#define SNAKE_GAME_ABILITY_ABILITYSLOT_H

#include <concepts>
#include <engine/component/component.h>
#include <engine/entity.h>

class ability_slot : public component
{
public:
    ability_slot(entity &attached_to);
    void detach() override;
    void remove();

    template<typename Ability>
        requires std::derived_from<Ability, component>
    void add();
private:
    component *_ability;
};

template<typename Ability>
    requires std::derived_from<Ability, component>
void ability_slot::add()
{
    remove();
    _ability = &attached_to().add_component<Ability>();
}

#endif
