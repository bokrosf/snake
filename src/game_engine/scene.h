#ifndef SNAKE_GAMEENGINE_SCENE_H
#define SNAKE_GAMEENGINE_SCENE_H

#include <unordered_set>
#include <queue>
#include "game_object.h"
#include "component/component.h"
#include "messaging/messenger.h"
#include "messaging/recipient.h"
#include "game_object_parent_changed.h"
#include "component_added.h"

class scene : public recipient<game_object_parent_changed>, public recipient<component_added>
{
public:
    scene(messenger &messenger);
    ~scene();
    void initialize();
    void receive(const game_object_parent_changed &message) override;
    void receive(const component_added &message) override;
private:
    messenger &_messenger;
    std::unordered_multiset<game_object *> _root_objects;
    std::queue<component *> _components_to_initialize;
};

#endif
