#ifndef SNAKE_GAME_EXECUTIONPRIORITY_H
#define SNAKE_GAME_EXECUTIONPRIORITY_H

#include <engine/component/updatable.h>

namespace execution_priority
{
    const int controller = updatable::default_priority + 1;
}

#endif