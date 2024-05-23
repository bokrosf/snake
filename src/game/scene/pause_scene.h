#ifndef SNAKE_GAME_SCENE_PAUSESCENE_H
#define SNAKE_GAME_SCENE_PAUSESCENE_H

#include <engine/scene.h>

class pause_scene : public scene
{
public:
    pause_scene(int id);
    void initialize() override;
};

#endif
