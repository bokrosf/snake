#include "scene.h"

scene::scene(messenger &messenger)
    : _messenger(messenger)
    , _running(false)
{
}

scene::~scene()
{
    _messenger.unsubscribe<game_object_parent_changed>(*this);
    _messenger.unsubscribe<component_added>(*this);
}

void scene::initialize()
{
    _messenger.subscribe<game_object_parent_changed>(*this);
    _messenger.subscribe<component_added>(*this);
}

void scene::play()
{
    // TODO 2024-04-04 Implement the following features.
    // - Frame start time recording.
    // - Initialize components.
    // - Detect collisions
    // - Handle user input.
    // - Logic:
    //      - Update game state by traversing the game_object tree.
    //      - Don't process Inactive game_object subtree.
    //      - Only active behaviors updated.
    // - Graphical rendering.
    // - Frame end time recording.
    // - Delta-time update.

    while (_running)
    {
        // size_t frame_started;
        initialize_components();
        detect_collisions();
        handle_user_input();
        update_game_state();
        render();
        // size_t frame_ended;
        // time::delta_time
    }
}

void scene::pause()
{
    _running = false;
}

void scene::receive(const game_object_parent_changed &message)
{
    if (message.object.parent())
    {
        _root_objects.erase(&message.object);
    }
    else
    {
        _root_objects.insert(&message.object);
    }
}

void scene::receive(const component_added &message)
{
    _components_to_initialize.push(&message.added);
}

void scene::initialize_components()
{
    while (!_components_to_initialize.empty())
    {
        _components_to_initialize.front()->initialize();
        _components_to_initialize.pop();
    }
}

void scene::detect_collisions()
{
    // TODO 2024-04-05 Implement.
}

void scene::handle_user_input()
{
    // TODO 2024-04-05 Implement.
}

void scene::update_game_state()
{
    // TODO 2024-04-05 Implement.
}

void scene::render()
{
    // TODO 2024-04-05 Implement.
}
