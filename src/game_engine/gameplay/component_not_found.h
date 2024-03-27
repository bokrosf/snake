#ifndef SNAKE_GAMEENGINE_GAMEPLAY_COMPONENTNOTFOUND_H
#define SNAKE_GAMEENGINE_GAMEPLAY_COMPONENTNOTFOUND_H

#include <stdexcept>
#include <string>

class component_not_found : public std::logic_error
{
public:
    component_not_found(const std::string &what_arg);
    component_not_found(const char *what_arg);
    component_not_found(const std::logic_error &other) noexcept;
};

#endif