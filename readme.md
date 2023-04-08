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