Summary of project evolution. Contains architectural decisions, problems, improvement ideas.

For improvement ideas search the following text for each section: **Improvement ideas**

Topics to write about
- transform property of entity
- querying entity by name
- app handles scene navigation, batched scene navigation, delta time
- scene navigation
- scene loading
- pausing the game
- awake

# Rendering engine
2024-04-29
- ```rendering_engine``` class created to encapsulate the ```app::render``` method's funcionality and store rendering context.
- Must be initialized at app startup.
- Stores the SDL_Renderer renderer.
- Renders the specified scene. Active and alive entities and components rendered only by traversing the root entity trees.

# Component destroy request queueing
2024-04-27

### Problem
- Components should be deallocated after each operation performed on them and before rendering.
- Entity must differentiate between marking a component destroyed and deallocating them.
- Entity's destructor must deallocate components not marking them for destroyal.
- Components be able to signal eachother or execute specific cleanup when they marked for removal. It's called **detaching**. This needed when a component controls other component's lifetime. For example a slot component that ensures addition and removal of a special kind of component and enforce that only one component can be present at a time. So whenever a new component added it removes the previously added one.
- Marking for destroyal, detaching, deallocation of components mustn't cause recursive execution.

### Solution
- ```life_state``` enum introduction for storing the state of the component and entity. This way it can be detected if the object marked for destroyal or in any other state. Values are:
  - alive
  - destroyed
- component and entity classes store their life state.
- ```component::destroy``` checks whether the component has already been
marked for destroyal and returns if it has. If it's alive then changes life state to destroyed, detaching and notifies the scene about destroyal. Changing the life state eliminates recursive detaching and unnecessary event triggering.
- ```entity::destroy_component<T>``` only calls ```component::destroy``` on the component if it's attached.
- Scene receives the message and adds the component's entity to a set that stores entities whose have a removed component. This way the destroyed state only stored at one place at the component, moreover the entity class is responsible for removing the marked component that it can query. Deallocation can be optimized because if an entity is marked for destroyal and it also has a marked component then there's no need for a seperate component deallocation the entity will deallocate all of it's components either way.
- Concrete deallocation occures by the ```entity::erase_destroyed_components``` method that filters components by their life states and it's called by the ```scene::destroy_components``` method.

### Remarks
- When ```entity::destroy``` called then no further ```entity::destroy``` or ```component::destroy``` called on it's children or components. This is because performance reasons to not traverse the entire tree. It also seems a rare use case where a non child component's detach should be called. A workaround could be to query the specific component or trigger a specific event that specific components can subscribe to.

# Unsubscribe all
2024-04-17
- The current model of the messenger class does not support the implementation of the ```messenger::unsubscribe_all``` method. It should be used when an object no longer wants to receive any notifications. Useful in destructors or other cleanup code because of the open-closed principle.
- Problem:
  - ```message``` class stores the subscribed recipient as a **void \*** that is the value of a **recipient<Message> \***, but it should store the pointer of the base class to find all subscriptions of the actual object.
  - In C++ when a pointer to a base class **dynamic_cast**ed to a subclass then the subclass' address maybe different from the base class'.
  - Moreover dynamic_cast is not available for **void \*** type because technically it can be converted to any type and it would always return true, but it does not have a base class with the target type. If the base class' address stored as **void \*** and **reinterpret_cast**ed to a subclass, then it would return the original address of the base class.
- Improvement ideas:
  - The pointer of the base class should be stored alongside the address of the subscribed **recipient<Message>**.
  - The subscription must be searchable by the concrete **recipient\<message\>** type and also by the base class type.
  - A struct or class with template specialized inheritance or storing base and reciever class pointers could be used to store data. Also it must implement the **==** and **!=** comparison operators for set searching. Maybe even a hash_code too.
  - Subscription must call the appropriate **receive\<message\>** method on the dereferenced pointer.
  - It should not contain runtime polymorphism if there is a direct sane way of notifying the subscribed object. But the runtime polymorphism in this case shouldn't cause that much of an overhead so it's also a reasonable path .

# Collision detection
2024-04-17
- Two entities collide when their colliders intersect eachother in 2D space. Except when only the collider's edges touching. In this case it's not detected because the snake game is tile based and it would detect false collisions if the snake's body can occupy the whole tile area.
- Collision engine's brief working:
  - Specified entities can contain any number of colliders.
  - The collision engine checks for intersecting colliders. When a collision detected the collided entities notified about the collision.
  - Collision details passed to the collision notification.
  - Collision handlers receive the collision notification and handles them.

### BoxCollider
- 2D rectangular area that describes the area checked for collisions. Described by a 2D vector as width and height.
- Also has a world position that is the center of the collider.

### Collision
- Information passed to the collision handler.
- Holds a reference to the entity that the notified entity collided with.

### Collision handler
- Interface with the ```collision_handler::collide``` method that has a ```collision``` parameter.
- Usually behaviors implement the ```collision_handler``` interface. The collision parameter represents the entity that the current behavior's owner entity collided with.

### Collision engine
- Traverses the root entity trees by querying the active entity nodes and their active ```box_collider``` components.
- Checks every box_collider with every other box_collider components which is a O(n^2) operation. It's slow in theory but the snake game contains only a few number of objects at a given time so it doesn't run slowly.
- When a collision detected between two entities their ```collision_handler``` capability is queried and the ```collide``` method called if they support it.
- If entity A collides with { X1, X2, ..., Xn } entities then **collisions** :=
{
  (A, X1),
  (A, X2),
  ...
  (A, Xn),
  (X1, A),
  (X2, A),
  ...
  (Xn, A)
}
- This implies:
    - **collisions** is a set of ordered entity pairs.
    - Both entities of the collision pair must be notified if they implement the handler.
    - This model only cares about entity collisions, so at the implementation level collisions with the same entity's different colliders must be treated as one collision.
- Improvement ideas:
  - Reduce the O(n^2) complexity.
  - The game world could be divided to fix sized disjunct rectangle areas that represent possible collision hotspots. Called **hotspot tiles**. This way the spacial position could be used as a hash function. Each collider would be hashed by their position and added to the spacial buckets they overlap O(n) operation but the collider area tiled subdivisions should be taken into account too. The algorythm should check those buckets that contains more than one collider O(n) operation. Approximately it's an O(n + tile_subdivision) + O(n) = O(2n + tile_subdivision) operation.

# Material rendering
2024-04-17
- Material class describes the surface properties of the rendered object. Kind of like arguments for rendering.
- Entities only rendered if a material is assigned to the renderer.
- Currently only stores the **drawing color**.
- Improvement ideas:
  - Shaders can be attached to the material.

# Input handling
2024-04-15
- Chose the free function approach and creation of the input namespace. Current inputs should be accessible by any behavior or the app class without it being their dependencies.
- More convenient to implement this way than using a singleton approach.
- In every frame previous input is cleared and then the current input read from the input queue.
- The current input added to the static collection inside the input namespace.
- Each behavior or the app class can query if an input type or keypress has been occured and react to it.
- Input querying usually implemented inside update methods. This approach is much simpler than the first thought of triggering events when input read. This way only the active behaviors react that are part of an active entity subtree. Pause automatically handled no need to implement any check. If the game paused no unwanted update method will be scheduled for execution. No need for event subscription management and event occurance can be simply queried only whenever it's needed.

# Update game state
2024-04-15
- Active updatable behaviors must be queried from entities by traversing the entity tree.
- Update methods called in random order.

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
