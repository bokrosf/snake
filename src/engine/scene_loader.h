#ifndef ENGINE_SCENELOADER_H
#define ENGINE_SCENELOADER_H

#include <concepts>
#include <functional>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <engine/scene.h>

class scene_loader final
{
public:
    using scene_id = int;

    scene_loader();
    ~scene_loader();    

    template<typename Scene, typename... Args>
        requires std::derived_from<Scene, scene>
    scene_id load(Args&&... args);

    void unload(scene_id id);
    void unload_all();
    void activate(scene_id id);
    scene &active() const;
private:
    scene_loader::scene_id _last_loaded_id;
    std::unordered_map<scene_loader::scene_id, scene *> _loaded_scenes;
    scene *_active_scene;
};

template<typename Scene, typename... Args>
    requires std::derived_from<Scene, scene>
scene_loader::scene_id scene_loader::load(Args &&...args)
{
    scene *scene = nullptr;

    try
    {
        scene = new Scene(std::forward<Args>(args)...);
        scene->initialize();
        _loaded_scenes[++_last_loaded_id] = scene;
    }
    catch (...)
    {
        delete scene;
        throw;
    }

    return _last_loaded_id;
}

#endif
