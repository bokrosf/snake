#ifndef ENGINE_MESSAGING_MESSENGER_H
#define ENGINE_MESSAGING_MESSENGER_H

#include <ranges>
#include <typeindex>
#include <unordered_map>
#include <vector>
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
    struct subscription
    {
        subscription(void *object);
        
        void *object;
        bool removed;
    };

    messenger();
    
    static messenger *_instance;
    std::unordered_map<std::type_index, std::vector<subscription>> _subscriptions;
    bool _sending;
};

template<typename Message>
void messenger::send(const Message &message)
{
    std::type_index key = std::type_index(typeid(Message));

    if (!_subscriptions.contains(key))
    {
        return;
    }

    _sending = true;

    for (auto &s : _subscriptions[key])
    {
        if (auto r = reinterpret_cast<recipient<Message> *>(s.object))
        {
            r->receive(message);
        }
    }

    _sending = false;
    std::erase_if(_subscriptions[key], [](const auto &s) { return s.removed; });
}

template<typename Message>
void messenger::subscribe(recipient<Message> &recipient)
{
    std::type_index key = std::type_index(typeid(Message));
    _subscriptions[key].emplace_back(&recipient);
}

template<typename Message>
void messenger::unsubscribe(recipient<Message> &recipient)
{
    std::type_index key = std::type_index(typeid(Message));

    if (!_subscriptions.contains(key))
    {
        return;
    }
    
    if (_sending)
    {
        for (auto &s : _subscriptions[key] | std::views::filter([&recipient](const auto &s) { return s.object == &recipient; }))
        {
            s.removed = true;
        }
    }
    else
    {
        std::erase_if(_subscriptions[key], [&recipient](const auto &s) { return s.object == &recipient; });
    }
}

#endif