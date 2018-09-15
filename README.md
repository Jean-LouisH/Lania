Lania Engine
========

###  Table of Contents

1. [Introduction](#introduction)
2. [Architecture](#architecture)
2.1 [Entity Component System](#entity-component-system)
2.2 [Scripting and Virtual Machine](#scripting-and-virtual-machine)
3. [Rendering Engines](#rendering-engines)
4. [Gallery](#gallery)

## 1. Introduction

**Note: This engine is experimental in nature and is under alpha development. The runtime feature set is incomplete and there is currently no implementation of the scene editor. It is not currently suitable for creating games.**

Lania Engine, named after the Laniakea Supercluster (Hawaiian for "immeasurable heaven"), is a 2D & 3D real-time simulation and game engine. It is being developed as a personal exercise in applying my learning outcomes from university and reading. I also intend to have it as a modifiable codebase for future real-time applications like games and simulation software. 

My learning objectives include; scene architecture & management; scripting, interpreters & programming language development; file parsing & formatting; cache locality optimizations; multithreading; data structures; profiling; physics & collision algorithms; audio programming; rendering;  and APIs such as Simple DirectMedia Layer (SDL), OpenGL and Vulkan. 

This software is free, open source and [MIT Licenced](https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE). You can find the software repository [here](https://github.com/Jean-LouisH/LaniaEngine).

## 2. Architecture

The engine is meant to be data-driven through application projects. In development, these application projects can be accessed by the runtime or editor as directories with asset files, an init configuration and an icon image. A packaging format is in consideration for Lania Engine to run as an export template for application release. 

"Application" is the general term used for the scene and scripting data that describe the game or simulation being executed by the engine's "Core". The "Core" is the software layer below the application that contains all relevant data to the hardware platform, I/O and operating system. It also contains its own record of the executable name (for export templates), active renderer, application configuration (for startup), FPS and frame count, engine states, and high resolution timers (for profiling).

The application has an active scene which contains, namely, an asset cache (for instancing), scripting bytecode, action input maps, and 2D & 3D subscenes. The subscenes represent frames of game objects that are processed in their own distinct groups. They are layered in order with 2D subscenes appearing over 3D and vice versa. 

This enables applications to have, for example, a 2D background with a 3D object, and a 2D heads up display or UI appearing in front of everything else. Physics and other algorithms would only have objects interact among themselves within the same subscene. So, for example, particle effects in a 2D gameplay subscene layer would not affect interactive elements in a heads up display 2D subscene layer.

### 2.1 Entity Component System

Each subscene, whether 2D or 3D is composed of an entity component system architecture. The entities are listed by ID numbers and contain transform data, a map of components and their index numbers, a reference to a parent entity, and a list of children entities.

Components are also listed in the architecture to encourage linear access by processing systems such as Physics or Rendering. All components have references to their entity containers and additional data for the systems to operate on them. They are separated in the subscene by active and inactive lists to encourage existence-based processing. 

A current camera component index is stored to allow the Renderer to quickly reference the source view for rasterization. Other data include a map for entity name registry for the editor, and collision events lists for physics and scripted response.

### 2.2 Scripting and Virtual Machine

**To be determined**

## 3. Rendering Engines

**To be determined**

## 4. Gallery

### 2D

![Magnemite](https://jean-louish.github.io/LaniaEngine/Documentation/Images/sprite_test.png)

### 3D

**to be developed**