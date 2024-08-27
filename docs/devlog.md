Summary of project evolution. Contains architectural decisions, problems, future ideas.

Topics to write about
- entity, component destroy request queueing instead of immediate destroyal
- unsubscribe all
- collision
- input
- update
- render
- entity hierarchy traversal

# 2024-04-15 Entity lifetime management
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

# 2024-04-15 App
- Entrypoint of the application
- Initializes the engine and subsystems
- Starts and stops the main loop
- Captures and forwards user input
- Stores the scene created by the abstract ```create_scene``` method.
- Handles entity and component events. For example **creation**, **component addition**, **parent change**.

# 2024-04-17 Scene
- Responsible for entities' lifetime
- Every created entity belongs to the current scene
- Acts as a container of entities
- Processing of entities will query only the root entities and traverse their trees
- Only root entities' pointers need to be stored because each entity represents a tree hierarchy
- Root object's container must be updated whenever an entity has been created or it's parent changed
- Whenever a component has been created it's pointer must be stored in a container to be able to call their ```initialize``` method
- Abstract ```initialize``` method needed for creating the entities and their components when a scene is created. Currently have no plans for a scene editor or persisting and loading a scene's state. It's easier to define a specialized scene's content by code.

# 2024-04-13 Logging
- Different kind of levels
- Write output to a stream
- Ability to change output destination
- Templated writer method for varargs. This way it's more convenient to specify a message with different type of parameters. Parameter types must define an override for ```operator<<```.

# 2024-04-03 | Messaging
- Objects can send and receive messages from other objects.
- It must be usable with different types of messages so a message type parameter is needed.
- It can used when an object wants to notifiy another object but doesn't need to know about the other object.
- Subscribers must implement the ```recipient<Message>``` interface and override it's ```void receive(const Message &message)``` method.
- Subscriptions represented as sets of pointers per message types.
- When a message is sent the set of subscribers is determined by the type of the message. Set of subscriber sets is indexed by the message type.
Then the code iterates through the appropriate subscriber set and calls the ```receive()``` method on all of them.

# 2024-03-25 | Entity and Component basics
- I choose the model of Unity in terms of the entity-component architecture.
- Needed a class that can represent a single object in the game world.
- Also needed a way to be able to add, remove different functionalities during runtime.
- Tree hierarchy is important because entities can be composed to represent a complex object. It can also be used in the future for applying transformations. For example it can be easily achieved that the child entities automatically follow their parent's position or rotate alongside with them. A subtree can also be easily disabled, removed or attached to another entity.

## Entity
Represents an object in the game world that can contain different kinds of data and have different kinds of behaviors.
Maintains a hierarchy by a tree structure. Entities without parents are root entities. They can have child entities.
Manages the lifetime of the added components, because a component must belong to an entity but it can only belong to the one that created it.
When an entity destroyed all of it's attached components and all of it's child entities destroyed.

## Component
Represents data or functionality that entities can be dynamically extended with during runtime.
This is more flexible than a classical inheritance focused OOP approach.
Always belongs to the entity it was created by. It can access the entity by referencing it.

# 2024-03-24 | Start of the project
- Added the gitignore and main.cpp.
