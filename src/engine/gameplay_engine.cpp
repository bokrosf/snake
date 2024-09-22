#include <vector>
#include <engine/component/behavior.h>
#include <engine/component/updatable.h>
#include <engine/entity.h>
#include <engine/gameplay_engine.h>

void gameplay_engine::update(const scene &scene)
{
    std::vector<updatable *> updatables;
    auto filter_entity = [](const entity *e){ return e->active() && e->life_state() == life_state::alive; };

    for (const entity &entity : scene.traverse(filter_entity))
    {
        auto cast_to_updatable = [](behavior *b) { return dynamic_cast<updatable *>(b); };
        auto filter_behavior = [&cast_to_updatable](behavior *b) { return cast_to_updatable(b) && b->active() && b->life_state() == life_state::alive; };

        for (updatable *u : entity.all_attached_components<behavior>()
            | std::views::filter(filter_behavior)
            | std::views::transform(cast_to_updatable))
        {
            updatables.push_back(u);
        }
    }

    for (updatable *u : updatables)
    {
        u->update();
    }
}
