#include <stdexcept>
#include <game/scene/scene_navigator.h>

scene_navigator *scene_navigator::_instance = nullptr;

scene_navigator::scene_navigator(scene_loader &loader)
    : _loader(loader)
{
}

void scene_navigator::initialize(scene_loader &loader)
{
    delete _instance;

    try
    {
        _instance = new scene_navigator(loader);
    }
    catch (...)
    {
        delete _instance;
        _instance = nullptr;
        throw;
    }
}

scene_navigator &scene_navigator::instance()
{
    if (!_instance)
    {
        throw std::logic_error("Navigator must be initialized before used.");
    }
    
    return *_instance;
}

void scene_navigator::shutdown()
{
    delete _instance;
    _instance = nullptr;
}

void scene_navigator::pop()
{
    if (_scenes.empty())
    {
        return;
    }

    _loader.unload(_scenes.top());
    _scenes.pop();
    _loader.activate(_scenes.top());
}
