#ifndef SNAKE_GAME_SCENE_MAINSCENE_H
#define SNAKE_GAME_SCENE_MAINSCENE_H

#include <engine/scene.h>

class main_scene : public scene
{
public:
    main_scene(int id);
    void initialize() override;
};

#endif
