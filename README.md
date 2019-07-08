Lania
========

###  Table of Contents

1. [Introduction](#introduction)
1.1 [Name Origin](#name-origin)
2. [Architecture](#architecture)
2.1 [Entity Component System](#entity-component-system)
3. [Rendering Engines](#rendering-engines)
4. [Gallery](#gallery)

## 1. Introduction

**Note: This engine is experimental in nature and is under alpha development. The runtime feature set is incomplete and there is currently no implementation of the scene editor. It is not currently suitable for creating applications.**

**Lania** is a 2D/3D engine for real-time simulations and games. It is being developed as a personal exercise in applying my learning outcomes from university and reading. I also intend to use it as a testbed for small real-time simulations, scientific visualizations, artificial intelligence algorithms and games.

My learning objectives include; scene architecture & management; file parsing & formatting; cache locality optimizations; multithreading; data structures; profiling; physics & collision algorithms; audio programming; rendering; and APIs such as Simple DirectMedia Layer (SDL), PortAudio, OpenGL and Vulkan.

This software is free, and open source. You can find the software repository [here](https://github.com/Jean-LouisH/Lania).

### 1.1 Name Origin

**Lania** is named after the Laniakea Supercluster. Laniakea is Hawaiian for "immeasurable heaven". This relates to the engine's representation of physical space and also the endlessness of its feature support for the future.

## 2. Architecture

The engine is meant to be data-driven through application projects. In development, these can be accessed by the editor as directories with asset files, a project configuration and an icon image. These will be exported to file archives for assets and runtime boot data. Script code will be compiled into a dynamic library to bind with the release build export template.

"Application" is the general term used for the scene and scripting data that describe the simulation or game being executed with the engine's "Core". The "Core" is the software layer below the application that contains all relevant data to the hardware platform, I/O and operating system. It also contains its own record of the executable name (for export templates), active renderer, application configuration (for startup), FPS and frame count, engine states, and high resolution timers (for profiling).

The application has an active scene which contains, namely, an asset cache (for instancing), action input maps, and lists of 2D & 3D sub scenes. The sub scenes represent frames of entities that are processed in their own distinct groups. They are listed and layered in order with 2D sub scenes appearing over 3D and vice versa. 

This enables applications to have, for example, a 2D background with a 3D entity, and a 2D heads up display or UI appearing in front of everything else. Physics and other algorithms would only have entities interact among themselves within the same sub scene. So, for example, particle effects in a 2D gameplay sub scene layer would not affect interactive elements in a heads up display 2D sub scene layer.

### 2.1 Entity Component System (ECS)

Each sub scene, whether 2D or 3D is composed of an entity-component-system (ECS) architecture. The entities form a tree, indexed by ID numbers and contain transform data, a map of components and their index numbers, a reference to a parent entity, and a list of children entities.

Components are also listed in the architecture to encourage linear access by processing systems such as Physics or Rendering. All components have references to their entity containers and additional data for the systems to operate on them. They are separated in the sub scene by active and inactive lists to encourage existence-based processing. 

A current camera component index is stored to allow the Renderer to quickly reference the source view for rasterization. Other data include a map for entity name registry for the editor, and collision events lists for physics and scripted response.

## 3. Rendering Engines

**To be determined**

## 4. Gallery

### 2D

**to be developed**

### 3D

**to be developed**