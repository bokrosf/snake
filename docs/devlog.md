Summary of project evolution. Contains architectural decisions, problems, future ideas.

Topics to write about
- entity, component destroy request queueing instead of immediate destroyal
- unsubscribe all
- collision
- input
- update

# Rendering
2024-04-15
- Active renderer components must be queried from entities.
- If two rendered images overlap than the one rendered later will be fully visible. To have control over the rendering order a layer order must be defined for renderers. The higher order drawn over the lower layers.
- Renderers must be grouped by ```renderer::layer_order``` and drawn in order. This can be easily achieved if every renderer is stored in an ordered map with a key of the layer and with the value of a set of renderers. The ordering of the elements guaranteed by the container's type invariant. This ensures that iterating over it's elements happens in the wanted order. After that each renderer within the layer group can be drawn in random order.
- Before rendering the current frame the rendering context must be cleared with a single color to clear the previously rendered image.
- Rendering methods can be called by taking into account the rendering order.
- Frame rendering must be commited that invokes the swapping of the back buffer and the front buffer that presents the rendered frame to the user.

# Entity hierarchy traversal
2024-04-15
- Entities traversed from the root elements.
- Root entities queried from the scene and they are queued for traversal.
- When an entity selected from a queue and only processed further if it's active and alive. This way it's easy to deactivate a child tree of an entity and it's temporarily appears as inactive or non existent.
- After that it's active child entities queried and added to the traversal queue.
- This process repeated until no more entities to be processed.
- Entities can be processed in random order. Not any special use case for using in depth graph traversal. It's simply just a convinient way of pushing to and popping from the queue.
- After querying the entities the proper subengine's operation executed to each entity. Subengine's can use their own predicates and traversal algorythms to traverse the entity trees, but they are similar.
- Improvement ideas:
  - If a need arises for prioritizing the entities then an additional priority metadata needed and an ordered map can be used. The ordered map indexed by the priority and contains a set of entities that at the specified priority level can be processed in random order.
  - Subengine's can have the same collection for each scene to not allocate a new one. But they can also use some kind of caching strategy for entities to be processed.

# Main loop
2024-04-15

Executes when the application is ready to be used by the user and stops when requested by the user.
1. Frame start time recording
2. Initializing components
3. Detecting collisions
4. Handling user input
5. Advancing game logic
6. Deleting entities marked for deletion
7. Graphical rendering
8. Frame end time recording
9. Updating delta time

# Delta time
2024-04-15
- Storing the time elapsed since the rendering of the last frame.
- Chose the namespace and static storage approach instead of the static class approach.
- The elapsed time value needed since the start of the main loop.
- It must be queryable or updatable from the calling place without it being a dependency.
- Static class using approach would be almost the same but a static class is almost like just a namespace, so it's an unnecessary abstraction and inconvinent for internal implementation.
- It's value must be zero during the first frame's cycle, because that's the starting time point and the application state must be projected exactly as it is at the given time point.
- After rendering it's value must be updated to contain the time elapsed between starting the frame and finishing the rendering.
- Each frame's timeline position in real time can be calculated by accumulating each delta time until that time point. So if each cycle applies the delta time to the required components they are exactly at the state where they should be at the time of the start of the cycle.
- It was useful, to convert elapsed milliseconds int value returned by SDL, to a float value that represents seconds. This way it can be used as a fractional value for example applying to movement speed, and realtime movement easily achievable.

# Component addition
2024-04-15
- Can only be created by ```entity::add_component``` method. This ensures that the component only belongs to exactly one entity and triggers the component added event.
- Each initialization is scheduled to the beginning of the next frame.
- ```app``` class handles the component added event and registers the component to the currently active scene.
- ```scene``` registers the component for initialization by adding it to a collection.
- ```app``` class calls the component initialization method on the currently active scene at the beginning of every frame.

# Entity lifetime management
2024-04-15
### Creation
  - Can only be created by the ```entity::create``` static method. This is important because the currently active scene must register the entity to it's root objects. This method triggers the creation event that can be handled.
  - ```app``` class handles the entity creation event and adds the entity to the currently active scene.
  - ```scene``` handles the addition by checking if the specified entity is a root object and adds it to the root objects.

### Deletion
  - ```entity::destroy``` method must be called for deletion. This method triggers the destroy requested event that can be handled.
  - Can not be reverted. If an entity once marked for destroyal then it will be destroyed.
  - This is needed because the destroyal isn't immediate but occurs after update and before the rendering phase. It ensures that entities deleted exactly once. Entities must be alive during the different instances's update calls. Updates called in undefined order. If an entity destroyed during an update call then that's the result of the update if it's interpreted as a program state transition. Therefore it doesn't need to be rendered to reflect the destroyed state.
  - ```app``` class handles the entity deletion event and marks the entity for deletion in the currently active scene.
  - ```scene::mark_as_destroyed``` marks the entities to be destroyed by adding them to a dictionary.
  - ```scene::destroy_marked_objects``` executes the concrete freeing up. It's invoked by the ```app``` class before the rendering phase.
    - Detaches each marked entities from their parents. This way they become root entities and they also removed from their parents' children collection.
    - They removed from the root objects because they are not part of the scene anymore.
    - Concrete delete operator called on each marked entities that frees them up by calling their constructor.
    - The marked object collection cleared.

# App
2024-04-15
- Entrypoint of the application
- Initializes the engine and subsystems
- Starts and stops the main loop
- Captures and forwards user input
- Stores the scene created by the abstract ```create_scene``` method.
- Handles entity and component events. For example **creation**, **component addition**, **parent change**.

# Scene
2024-04-17
- Responsible for entities' lifetime
- Every created entity belongs to the current scene
- Acts as a container of entities
- Processing of entities will query only the root entities and traverse their trees
- Only root entities' pointers need to be stored because each entity represents a tree hierarchy
- Root object's container must be updated whenever an entity has been created or it's parent changed
- Whenever a component has been created it's pointer must be stored in a container to be able to call their ```initialize``` method
- Abstract ```initialize``` method needed for creating the entities and their components when a scene is created. Currently have no plans for a scene editor or persisting and loading a scene's state. It's easier to define a specialized scene's content by code.

# Logging
2024-04-13
- Different kind of levels
- Write output to a stream
- Ability to change output destination
- Templated writer method for varargs. This way it's more convenient to specify a message with different type of parameters. Parameter types must define an override for ```operator<<```.

# Messaging
2024-04-03
- Objects can send and receive messages from other objects.
- It must be usable with different types of messages so a message type parameter is needed.
- It can used when an object wants to notifiy another object but doesn't need to know about the other object.
- Subscribers must implement the ```recipient<Message>``` interface and override it's ```void receive(const Message &message)``` method.
- Subscriptions represented as sets of pointers per message types.
- When a message is sent the set of subscribers is determined by the type of the message. Set of subscriber sets is indexed by the message type.
Then the code iterates through the appropriate subscriber set and calls the ```receive()``` method on all of them.

# Entity and Component basics
2024-03-25
- I choose the model of Unity in terms of the entity-component architecture.
- Needed a class that can represent a single object in the game world.
- Also needed a way to be able to add, remove different functionalities during runtime.
- Tree hierarchy is important because entities can be composed to represent a complex object. It can also be used in the future for applying transformations. For example it can be easily achieved that the child entities automatically follow their parent's position or rotate alongside with them. A subtree can also be easily disabled, removed or attached to another entity.

### Entity
Represents an object in the game world that can contain different kinds of data and have different kinds of behaviors.
Maintains a hierarchy by a tree structure. Entities without parents are root entities. They can have child entities.
Manages the lifetime of the added components, because a component must belong to an entity but it can only belong to the one that created it.
When an entity destroyed all of it's attached components and all of it's child entities destroyed.

### Component
Represents data or functionality that entities can be dynamically extended with during runtime.
This is more flexible than a classical inheritance focused OOP approach.
Always belongs to the entity it was created by. It can access the entity by referencing it.

# Start of the project
2024-03-24
- Added the gitignore and main.cpp.
