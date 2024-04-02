#include "messenger.h"

messenger *messenger::_instance = nullptr;

messenger &messenger::instance()
{
    if (_instance == nullptr)
    {
        _instance = new messenger();
    }

    return *_instance;
}
