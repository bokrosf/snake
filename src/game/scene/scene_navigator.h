#ifndef SNAKE_GAME_SCENE_SCENENAVIGATOR_H
#define SNAKE_GAME_SCENE_SCENENAVIGATOR_H

#include <concepts>
#include <stack>
#include <utility>
#include <engine/scene.h>
#include <engine/scene_loader.h>

class scene_navigator
{
public:
    static void initialize(scene_loader &loader);
    static void shutdown();
    static scene_navigator &instance();

    template<typename Scene, typename... Args>
        requires std::derived_from<Scene, scene>
    void push(Args &&...args);

    void pop();

    template<typename Scene, typename... Args>
        requires std::derived_from<Scene, scene>
    void reset_root(Args &&...args);
private:
    scene_navigator(scene_loader &loader);
    
    static scene_navigator *_instance;
    scene_loader &_loader;
    std::stack<scene_loader::scene_id> _scenes;
};

template<typename Scene, typename... Args>
    requires std::derived_from<Scene, scene>
void scene_navigator::push(Args &&...args)
{
    _loader.queue([this, ...args = std::forward<Args>(args)](scene_loader &sl)
    {
        auto [id, scene] = sl.load<Scene>(std::forward<Args>(args)...);
        _scenes.push(id);
        sl.activate(id);
        scene.initialize();
    });
}

template<typename Scene, typename... Args>
    requires std::derived_from<Scene, scene>
void scene_navigator::reset_root(Args &&...args)
{
    _loader.queue([this, ...args = std::forward<Args>(args)](scene_loader &sl)
    {
        sl.unload_all();

        while (!_scenes.empty())
        {
            _scenes.pop();
        }

        push<Scene>(std::forward<Args>(args)...);
    });
}

#endif
