# Entity Component System (ECS)

Each sub scene, whether 2D or 3D is composed of an entity-component-system (ECS) architecture. The entities form a tree, indexed by ID numbers and contain transform data, a map of components and their index numbers, a reference to a parent entity, and a list of children entities.

Components are also listed in the architecture to encourage linear access by processing systems such as Physics or Rendering. All components have references to their entity containers and additional data for the systems to operate on them. They are separated in the sub scene by active and inactive lists to encourage existence-based processing. 

A current camera component index is stored to allow the Renderer to quickly reference the source view for rasterization. Other data include a map for entity name registry for the editor, and collision events lists for physics and scripted response.