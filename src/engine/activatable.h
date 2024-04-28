#ifndef SNAKE_ENGINE_ACTIVATABLE_H
#define SNAKE_ENGINE_ACTIVATABLE_H

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
