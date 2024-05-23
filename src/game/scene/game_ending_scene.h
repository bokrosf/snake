#ifndef SNAKE_GAME_SCENE_GAMEENDINGSCENE_H
#define SNAKE_GAME_SCENE_GAMEENDINGSCENE_H

#include <engine/scene.h>

class game_ending_scene : public scene
{
public:
    game_ending_scene(int id, bool won);
    void initialize() override;
private:
    bool _won;
};

#endif
