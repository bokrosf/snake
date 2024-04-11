#ifndef SNAKE_GAME_SCENE_TESTSCENE_H
#define SNAKE_GAME_SCENE_TESTSCENE_H

#include <game_engine/scene.h>

class test_scene : public scene
{
public:
    test_scene() = default;
    void initialize() override;
};

#endif
