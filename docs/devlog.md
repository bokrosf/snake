# Project evolution

Contains architectural decisions, problems. Used as a development diary to look back later on the process.

# Unsubscribe during send
2024-10-28

### Problem
- When a reciever unsubscribes from a message while handling it then segmentation fault can occur.
- Segmantation fault occurs because of iterator invalidation. The send method iterates through all the handlers and calls them sequentially. When unsubscribe called then the handler removed from the container.

### Solution
- Handler removal can only happen if there is no active sending.
- If there is an active sending then the handler marked for removal.
- After sending all marked handlers are removed.
- This means if a handler was subscribed it gets the message even if unsubscribed during a send call.
- If there is no active sending during the unsubscribe call then the handler physically removed.

# Pausing the game
2024-10-27

### Problem
- ```update``` method only called when the scene is active.
- If a behavior stores a future real time point and it's compared inside the ```update``` method with the scene's start time point then scene changing can cause a problem.
- After the scene has been switched back the current scene's start time point might passes the stored time point. This would mean that time has elapsed during scene changes.
- Desired behavior from a scene's perspective is that no time should be elapsed during a scene change. When switched back to a scene it should continue from where it has been paused.

### Solution
- Real time continuously goes forward and represented by ```game_time::real_now```, independent of scene switching.
- A stored time point must be synchronized when a scene switch back occures. It's must be increased with the duration of the scene not being active.
- This means the stored time points belong to a scene's game time context. Time point references should be stored per scene.
- ```behavior``` subsclasses stores the time points and the ```game_time``` module references and refreshes these time points when neccessary.
- ```behavior``` subclasses' ```initialize``` and ```start``` methods can be used to set an initial time point.
- ```time_point``` class stores the synchronizable time points. It should have bind and unbind methods that can be used to turn on or off the synchronization functionality. ```unbind``` automatically called by ```time_point``` class' destructor so it's advisable that ```behavior```s store ```time_point``` instances as members without the need of additional destructors for using it.

# Resetting scene
2024-05-21

- Resetting scene's state to initial state. It's useful if the player wants to restart the game at the current scene.
- ```scene::reset``` method introduced and it cleans up the scene's state, destroys every entity and calls ```scene::initialize``` on itself.
- Reset operation must be queued and executed by **commiting** to not interfere with the current frame's scene processing.

# Transform component
2024-05-15

- ```transform``` is a component that stores the world position of the entity and applies transformation to move the entity with an offset to another position.
- It's a necessary component, every entity has it when constructed, and initialized with the (0, 0) world position.

# Querying entity by name
2024-05-15

- Entity must have a name field. It's default value is empty but it can contain any string. A specific value must be passed to the ```entity::create``` method.
- Entity names must be unique per scene except the empty string. If the scene's entity creation handler detects an already existing name then it throws an ```entity_name_collision``` exception.
- ```scene``` stores unique names in a hash set container. Container item's lifetime is the same as the entity's.
- ```scene::find_entity``` method can be used to retrieve and entity by name. If not found it returns **nullptr**.

# Handling scene navigation
2024-05-13

- Switching to another scene must be executed after the current scene processed in the current frame.
- Scene switching and activation requests must be queued in a form of a function, because they will happen later in time not simultaneously when the request created. The parameter lambda has a ```scene_loader``` parameter that is used to specify the operation to be executed. Other parameters must be passed by value because the caller's stack will be already destroyed when **committed** by ```app::run```.
- Scene manipulation requests processed in queueing order and processed as a batch. Signaling the start of execution called **committing** the scene loader.
- When the active scene changed **delta time** must be **reset to zero**. This is because each scene represents another simulated world. It's simulation must be continued from the exact time point when it's switched to. Moreover when switching back to a previous scene the previous scene must continue from the time point where it has been left. The exact time point can not be achieved but the delta time being zero has the same effect.
- ```app``` class contians an instance of the ```scene_loader``` class.
- Scene manipulation in order:
  1. ```app::run``` calls the abstract ```app::load_start_scene``` method. ```app::create_start_scene``` method renamed to this and return type changed to void.
  2. Concrete implementation of ```app``` class defines the abstract loader method and initializes it's scene navigator and loads necessary scenes and marks one active.
  3. ```app::run``` commits the scene loader that executes the scene manipulation requests in order and then starts the main loop.
  4. At the beginning of each frame the active scene is queried.
  5. Collision detection, input reading, logic update and other main loop processes executed.
  6. After the rendering phase **committing** occures and the scenes are loaded, activated as they have been requested.
  7. Delta time updated according to if the scene stayed the same or changed.
     - Stayed the same: Stores the elapsed time of processing the current scene.
     - Changed: Elapsed time set to zero.

# Scene navigation
2024-05-12

- Scene navigation must use the scene loader and loader must be independent of the navigation.
- Each navigation mode should have it's own class for example stacked or other kinds of.
- I chose stack navigation mode because it fits having a menu and a game scene and switching between them. It seems to be usable by other games too.

### Stack navigation
- It's similar to navigation between mobile app screens. Only one scene visible at the full screen.
- Operations:
  - **push**: Loads the scene specified by a template type argument and forwards arguments required for the scene's constructor. Activates the newly loaded scene. Initializes the scene that must occure after activating it, because the created entities, components will be added to the active scene.
  - **pop**: Unloads the active scene and activates the previous scene.
  - **active**: Queries the active scene that is at the top of the stack.
  - **reset_root**: Unloads all scenes and loads the provided scene with the same arguments as push and activates it.

# Scene loading
2024-05-12

- Need a class that can load/unload scenes into memory, manages their lifetime and can mark a scene as active. This class is ```scene_loader```.
- Every scene has an int id. Id's start from 0 and increased by 1 after a scene loaded. Unloading a scene does not effect the next id's value.
- Currently scenes are not serialized and stored as assets. Because of this they are defined by code first approach, and must be loaded by providing a type template parameter to the loading method. Optionally scene arguments can be provided to the loading method that forwards them to the scene's constructor.
- Marking a scene as active is a manual instruction.
- Active scene's significance:
  - Only one scene can be marked as active.
  - Entities and components will be added only to the active scene.
  - Only applied to the active scene:
    - collision detection
    - update
    - rendering
    - entity, component lifetime
- Unloading a scene requires an int id parameter. Removes the scene from the container and deallocates it.

# Pausing the game
2024-05-12

### Problem
- When the game is paused these conditions must be met:
  - Don't execute ```update``` or if it's executed then it should act like as time frozen.
  - Specific entities don't handle user input.

### Possible solutions
- Deactivate objects
  - Search specific objects by name, tag or type and deactivate them.
  - Subscribe to specific events and in their handlers deactivate the objects.
  - This adds additional complexity, state and event handling to game logic.
- **Switching active scene to another scene.** I chose this.
  - Only the currently active scene passed to collision detection, update and rendering. The previous scene stays at the same state as it was before switching scenes.
  - Input never handled when the scene is inactive because it occures inside ```update``` by checking the return value of the ```input::key_down(<key>)``` bool function.
  - Games usually have a pause screen or a menu that is independent of the game world. Moreover stacked UI can be built with this technique.
  - This seems a to be a good candidate for this and future games. It results in a more easily maintainable game logic codebase by not adding additional complexity to it.
  - If popups or the need for rendering multiple scenes arises then it must be solved, but until then don't want to solve a not existing problem.

# Start method and initialization refactoring
2024-05-05

### Problem
- Components reference another component in ```initializable::initialize``` method and also call a method on it or treat as already initialized. For example A->B means component A depends on B. When A->B and B->C and A::initialize calls B::method and B::method calls C::method, then B::C reference might not be initialized and this can cause invalid dereferencing.
- Initialization must be split into two phases **setup** and **performing action**.
- When a new entity, component created during initialization phase it must be also initialized at the start of the same frame, moreover objects created by them too and so on.

### Solution
- Defining the ```life_state::initializing``` enum value. This is the value setted by the entity and component class' constructors.
- Splitting the initialization phase into two:
  - ```initialize::initialize```: Used for querying other components, field initialization.
  - ```startable::start```: Perform an action before the first update when the component is already in an initialized state and can use the components it depends on. Also useful for not having to handle a flag in update and check for the first execution. This way the update method can keep it's original function and performance.
- Introduction of ```object_initializer``` class. It's responsible for registering the entity and component initialization requests, and performing the two staged initialization.
  - Initializes every object created during the initialization phase of the current frame.
  - Uses double buffering per entities and per components too. One buffer used to process the currently batched objects. The other buffer used to collect the new objects that created during the first buffer's processing. They are swapped in every cycle. The process ends when there are no more objects to initialize.
  - entity initialization:
    - Sets the life_state: initializing -> **alive**
  - component initialization:
    - Calls **initialize** on each component
    - Calls **start** on each component. This **order is important because** every component must be initialized before executing it's start method. For example A->B->C component dependency.
    - Sets the life_state: initializing -> **alive**
  - If a new object created then it's added to the **scheduled_object** buffer and will be initialized in the next initialization cycle within the current frame.

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

# Material rendering
2024-04-17
- Material class describes the surface properties of the rendered object. Kind of like arguments for rendering.
- Entities only rendered if a material is assigned to the renderer.
- Currently only stores the **drawing color**.

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
