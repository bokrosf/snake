#ifndef SNAKE_GAME_SPECIALABILITY_SPECIALABILITYSLOT_H
#define SNAKE_GAME_SPECIALABILITY_SPECIALABILITYSLOT_H

#include <concepts>
#include <game_engine/component/component.h>

class special_ability_slot : public component
{
public:
    special_ability_slot(game_object &attached_to);
    ~special_ability_slot();
    void remove();

    template<typename Ability>
        requires std::derived_from<Ability, component>
    void add();
private:
    component *_ability;
};

template<typename Ability>
    requires std::derived_from<Ability, component>
void special_ability_slot::add()
{
    remove();
    _ability = &attached_to().add_component<Ability>();
}

#endif
