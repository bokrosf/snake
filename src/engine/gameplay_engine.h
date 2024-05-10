#ifndef ENGINE_GAMEPLAYENGINE_H
#define ENGINE_GAMEPLAYENGINE_H

#include <engine/scene.h>

class gameplay_engine
{
public:
    gameplay_engine() = default;
    ~gameplay_engine() = default;
    void update(const scene &scene);
};

#endif
