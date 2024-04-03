#ifndef SNAKE_GAMEENGINE_MESSAGING_MESSENGER_H
#define SNAKE_GAMEENGINE_MESSAGING_MESSENGER_H

#include <unordered_map>
#include <unordered_set>
#include <typeindex>
#include "recipient.h"

class messenger
{
public:
    static messenger &instance();
    
    template<typename Message>
    void send(const Message &message);

    template<typename Message>
    void subscribe(const recipient<Message> &recipient);

    template<typename Message>
    void unsubscribe(const recipient<Message> &recipient);
private:
    using registration_set = std::unordered_set<void *>;
    
    static messenger *_instance;
    std::unordered_map<std::type_index, registration_set> _registrations;
    messenger() = default;
};

template<typename Message>
void messenger::send(const Message &message)
{
    std::type_index key = std::type_index(typeid(Message));

    if (!_registrations.contains(key))
    {
        return;
    }

    for (void *general_recipient : _registrations[key])
    {
        if (auto r = reinterpret_cast<recipient<Message> *>(general_recipient))
        {
            r->receive(message);
        }
    }
}

template<typename Message>
void messenger::subscribe(const recipient<Message> &recipient)
{
    std::type_index key = std::type_index(typeid(Message));
    _registrations[key].insert(const_cast<void *>(reinterpret_cast<const void *>(&recipient)));
}

template<typename Message>
void messenger::unsubscribe(const recipient<Message> &recipient)
{
    std::type_index key = std::type_index(typeid(Message));

    if (!_registrations.contains(key))
    {
        return;
    }
    
    _registrations[key].erase(const_cast<void *>(reinterpret_cast<const void *>(&recipient)));

    if (_registrations[key].empty())
    {
        _registrations.erase(key);
    }
}

#endif
