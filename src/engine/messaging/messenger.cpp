#include <engine/messaging/messenger.h>

messenger *messenger::_instance = nullptr;

messenger::messenger()
    : _sending(false)
{
}

messenger &messenger::instance()
{
    if (_instance == nullptr)
    {
        _instance = new messenger();
    }

    return *_instance;
}


messenger::subscription::subscription(void *object)
    : object(object)
    , removed(false)
{
}