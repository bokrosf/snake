#ifndef SNAKE_ENGINE_MESSAGING_MESSENGER_H
#define SNAKE_ENGINE_MESSAGING_MESSENGER_H

#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <engine/messaging/recipient.h>

class messenger
{
public:
    static messenger &instance();
    
    template<typename Message>
    void send(const Message &message);

    template<typename Message>
    void subscribe(recipient<Message> &recipient);

    template<typename Message>
    void unsubscribe(recipient<Message> &recipient);
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
void messenger::subscribe(recipient<Message> &recipient)
{
    std::type_index key = std::type_index(typeid(Message));
    _registrations[key].insert(&recipient);
}

template<typename Message>
void messenger::unsubscribe(recipient<Message> &recipient)
{
    std::type_index key = std::type_index(typeid(Message));

    if (!_registrations.contains(key))
    {
        return;
    }
    
    _registrations[key].erase(&recipient);

    if (_registrations[key].empty())
    {
        _registrations.erase(key);
    }
}

#endif
