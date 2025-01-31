# Improvement ideas

### Resetting scene
- Implementation could use the copy-swap idiom. This would create and empty uninitialized scene object and copies it's contents into the already existing scene's address. The old scene instance would be copied into the new address and it's destructor will be called when the swap operation finished.
- Content should be moved instead of copying. This way the performance penalty would be as minimal as it can be.
- This way the reset operation is open for addition and closed for modification because all of it's automatically handled and resetted properly.

### Transform component
- Child entities' position always relative to their parent's position. This must be calculated when a child attached to a parent or a transformation applied to the child.
- Adding rotation and scaling functionality.

### Unsubscribe all
- The pointer of the base class should be stored alongside the address ofthe subscribed **recipient<Message>**.
- The subscription must be searchable by the concrete **recipient\<message\>** type and also by the base class type.
- A struct or class with template specialized inheritance or storing baseand reciever class pointers could be used to store data. Also it mustimplement the **==** and **!=** comparison operators for set searching. Maybe even a hash_code too.
- Subscription must call the appropriate **receive\<message\>** method onthe dereferenced pointer.
- It should not contain runtime polymorphism if there is a direct sane way of notifying the subscribed object. But the runtime polymorphism in this case shouldn't cause that much of an overhead so it's also a reasonable path.

### Collision engine
- Reduce the O(n^2) complexity.
- The game world could be divided to fix sized disjunct rectangle areas that represent possible collision hotspots. Called **hotspot tiles**. This way the spacial position could be used as a hash function. Each collider would be hashed by their position and added to the spacial buckets they overlap. (n) operation but the collider area tiled subdivisions should be taken into account too. The algorythm should check those buckets that contains more than one collider O(n) operation. Approximately it's an O(n + tile_subdivision) + O(n) = O(2n + tile_subdivision) operation.

### Material rendering
- Shaders can be attached to material.

### Entity hierarchy traversal
- If a need arises for prioritizing the entities then an additional priority metadata needed and an ordered map can be used. The ordered map indexed by the priority and contains a set of entities that at the specified priority level can be processed in random order.
- Subengines can have the same collection for each scene to not allocate a new one. But they can also use some kind of caching strategy for entities to be processed.
