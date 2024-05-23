#ifndef SNAKE_GAME_SCENE_CLASSICSCENE_H
#define SNAKE_GAME_SCENE_CLASSICSCENE_H

#include <engine/scene.h>

class classic_scene : public scene
{
public:
    classic_scene(int id);
    void initialize() override;
};

#endif
