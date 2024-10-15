#ifndef SNAKE_GAME_SCENE_MAGICFOODSCENE_H
#define SNAKE_GAME_SCENE_MAGICFOODSCENE_H

#include <engine/scene.h>
#include <game/food/magic_food_factory.h>

class magic_food_scene : public scene
{
public:
    magic_food_scene(int id);
    void initialize() override;
private:
    magic_food_factory _food_factory;
};

#endif
