Summary of project evolution. Contains architectural decisions, problems, future ideas.

Topics to write about
- entity, component destroy request queueing instead of immediate destroyal
- unsubscribe all
- collision
- input
- update
- render
- entity hierarchy traversal
- app
- scene

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
