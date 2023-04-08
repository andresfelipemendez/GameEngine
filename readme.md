# Game Engine
## Introduction

This is a game engine project that aims to be cross-platform. Currently, all commands are Windows-specific, but I plan to make the project compatible with other operating systems.
Development Environment

## How to use

Run the start script with `start.py`

Use `venv` to manage script dependencies:
```powershell
python -m venv game_engine
pip install -r requirements.txt
python start.py
```

To develop the start script use nodemon:
```powershell
nodemon --exec python start.py
```

# Notes
 - The project no longer uses Visual Studio as it doesn't allow me to compile a library while it's in use. I might switch to using [RebedyBG](https://remedybg.handmade.network) instead.
The plan is to have a file watcher that auto-compiles on save and reloads the game engine library at runtime.
 - I aim to make the python script cross-platform
 - If the changed file belongs to a lib, reload that lib.
    -
 - If the file changed is the "front end" executable, reload that.

## To-Do
 - [x] Check if CMake is installed. 
    - [ ] If not, install it.
 - [ ] Check Visual Studio installation.
 - [x] Check Vcpkg installation
    - [ ] If not, install it.
 - [ ] Make the project cross-platform. Switch between Windows, Linux, and Mac.
    - [x] Windows
    - [ ] Linux
    - [ ] OSX
 - [ ] Create an env file to manyally set the paths to these tools.
    - [ ] 

this folder structure does not exist yet but its how I plan to put it as it comes
alon
```
project_root/
│
├── engine/                     # Game engine source code
│   ├── core/                   # Core engine functionality
│   │   ├── include/            # Header files for the core engine
│   │   ├── src/                # Source files for the core engine
│   │   └── CMakeLists.txt      # CMake configuration for the core engine library
│   │
│   ├── renderer/               # Renderer component
│   │   ├── include/            # Header files for the renderer
│   │   ├── src/                # Source files for the renderer
│   │   └── CMakeLists.txt      # CMake configuration for the renderer library
│   │
│   ├── physics/                # Physics component
│   │   ├── include/            # Header files for the physics
│   │   ├── src/                # Source files for the physics
│   │   └── CMakeLists.txt      # CMake configuration for the physics library
│   │
│   └── CMakeLists.txt          # Top-level CMake configuration for the engine components
│
├── launcher/                   # Launcher (small executable) source code
│   ├── include/                # Header files for the launcher
│   ├── src/                    # Source files for the launcher
│   ├── CMakeLists.txt          # CMake configuration for the launcher executable
│   └── ...
│
├── game/                       # Game-specific source code
│   ├── include/                # Header files for the game
│   ├── src/                    # Source files for the game
│   ├── CMakeLists.txt          # CMake configuration for the game executable
│   └── ...
│
├── external/                   # External dependencies, e.g., libraries, frameworks
│   ├── vcpkg/                  # if vcpkg is not installed put it here
│   └── ...
│
├── build/                      # Build output directory (add to .gitignore)
│
├── CMakeLists.txt              # Top-level CMake configuration
├── start.py                    # Top-level script for watching and building
└── .gitignore                  # Add build/ and other unwanted files and directories
```