#ifndef SNAKE_GAMEENGINE_MESSAGING_RECIPIENT_H
#define SNAKE_GAMEENGINE_MESSAGING_RECIPIENT_H

template<typename T>
class recipient
{
public:
    virtual void receive(const T &message) = 0;
};

#endif
