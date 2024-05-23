#ifndef SNAKE_GAME_SCENE_MAGICFOODSCENE_H
#define SNAKE_GAME_SCENE_MAGICFOODSCENE_H

#include <engine/scene.h>

class magic_food_scene : public scene
{
public:
    magic_food_scene(int id);
    void initialize() override;
};

#endif
