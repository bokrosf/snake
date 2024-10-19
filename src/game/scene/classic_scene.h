#ifndef SNAKE_GAME_SCENE_CLASSICSCENE_H
#define SNAKE_GAME_SCENE_CLASSICSCENE_H

#include <engine/scene.h>
#include <game/food/normal_food_factory.h>

class classic_scene : public scene
{
public:
    classic_scene(int id);
    void initialize() override;
private:
    normal_food_factory _food_factory;
};

#endif
