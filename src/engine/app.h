#ifndef ENGINE_APP_H
#define ENGINE_APP_H

#include <engine/app_configuration.h>
#include <engine/app_event.h>
#include <engine/collision/collision_engine.h>
#include <engine/component_added.h>
#include <engine/component_destroyed.h>
#include <engine/entity_created.h>
#include <engine/entity_destroyed.h>
#include <engine/entity_parent_changed.h>
#include <engine/gameplay_engine.h>
#include <engine/messaging/messenger.h>
#include <engine/messaging/recipient.h>
#include <engine/rendering/rendering_engine.h>
#include <engine/scene_loader.h>

class app : 
    public recipient<app_event>,
    public recipient<entity_created>,
    public recipient<entity_destroyed>,
    public recipient<component_added>,
    public recipient<component_destroyed>,
    public recipient<entity_parent_changed>
{
public:
    virtual ~app();
    void run();
    void receive(const app_event &message) final;
    void receive(const entity_created &message) final;
    void receive(const entity_destroyed &message) final;
    void receive(const component_added &message) final;
    void receive(const component_destroyed &message) final;
    void receive(const entity_parent_changed &message) final;
protected:
    app(const app_configuration &configuration);
    virtual void load_start_scene(scene_loader &loader) = 0;
    
    messenger &_messenger;
private:
    void initialize_subsystems();
    void shutdown();
    void handle_user_input();
        
    const app_configuration _configuration;
    scene_loader _scene_loader;
    bool _running;
    collision_engine _collision_engine;
    gameplay_engine _gameplay_engine;
    rendering_engine _rendering_engine;
};

#endif
