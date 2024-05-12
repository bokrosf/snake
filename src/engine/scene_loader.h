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
    std::tuple<scene_id, Scene &> load(Args&&... args);

    void unload(scene_id id);
    void unload_all();
    void activate(scene_id id);
    scene &active() const;
private:
    scene_id _last_loaded_id;
    std::unordered_map<scene_id, scene *> _loaded_scenes;
    scene *_active_scene;
};

template<typename Scene, typename... Args>
    requires std::derived_from<Scene, scene>
std::tuple<scene_loader::scene_id, Scene &> scene_loader::load(Args &&...args)
{
    Scene *scene = nullptr;

    try
    {
        scene = new Scene(std::forward<Args>(args)...);
        _loaded_scenes[++_last_loaded_id] = scene;
    }
    catch (...)
    {
        delete scene;
        throw;
    }

    return std::make_tuple(_last_loaded_id, std::ref(*scene));
}

#endif
