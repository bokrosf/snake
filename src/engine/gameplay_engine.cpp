#include <vector>
#include <engine/component/behavior.h>
#include <engine/component/updatable.h>
#include <engine/entity.h>
#include <engine/gameplay_engine.h>
#include <engine/scene_traversal.h>

void gameplay_engine::update(const scene &scene)
{
    std::vector<updatable *> updatables;
    
    auto add_updatable = [&updatables](entity *entity)
    {
        auto cast_to_updatable = [](behavior *b) { return dynamic_cast<updatable *>(b); };
        auto filter = [cast_to_updatable](behavior *b) 
        { 
            return cast_to_updatable(b) 
                && b->active()
                && (b->life_state() == life_state::alive || b->life_state() == life_state::destroyed);
        };
        
        for (updatable *u : entity->all_attached_components<behavior>() | std::views::filter(filter) | std::views::transform(cast_to_updatable))
        {
            updatables.push_back(u);
        }
    };

    auto filter = [](const entity *e)
    {
        return e->active()
            && (e->life_state() == life_state::alive || e->life_state() == life_state::destroyed);
    };

    scene_traversal::traverse(scene, filter, add_updatable);

    for (updatable *u : updatables)
    {
        u->update();
    }
}
