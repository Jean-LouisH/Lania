# Architecture

The engine is meant to be data-driven through application projects. In development, these can be accessed by the editor as directories with asset files, a project configuration and an icon image. These will be exported to file archives for assets and runtime boot data. Script code will be compiled into a dynamic library to bind with the release build export template.

"Application" is the general term used for the scene and scripting data that describe the simulation or game being executed with the engine's "Core". The "Core" is the software layer below the application that contains all relevant data to the hardware platform, I/O and operating system. It also contains its own record of the executable name (for export templates), active renderer, application configuration (for startup), FPS and frame count, engine states, and high resolution timers (for profiling).

The application has an active scene which contains, namely, an asset cache (for instancing), action input maps, and lists of 2D & 3D sub scenes. The sub scenes represent frames of entities that are processed in their own distinct groups. They are listed and layered in order with 2D sub scenes appearing over 3D and vice versa. 

This enables applications to have, for example, a 2D background with a 3D entity, and a 2D heads up display or UI appearing in front of everything else. Physics and other algorithms would only have entities interact among themselves within the same sub scene. So, for example, particle effects in a 2D gameplay sub scene layer would not affect interactive elements in a heads up display 2D sub scene layer.