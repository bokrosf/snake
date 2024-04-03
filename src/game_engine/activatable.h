#ifndef SNAKE_GAMEENGINE_ACTIVATABLE_H
#define SNAKE_GAMEENGINE_ACTIVATABLE_H

class activatable
{
public:
    bool active() const;
    void activate(bool active);
protected:
    activatable();
private:
    bool _active;
};

#endif
