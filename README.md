# Tetris

Lagless clone of [Tetris The Grand Master 1](https://tetris.fandom.com/wiki/Tetris_The_Grand_Master) with custom backgrounds written in C++ and OpenGL. The background changes every 100 levels.

## Usage:

There are multiple executables built with different controls. For now, to use your own keys, edit the keys in [common.hpp](https://github.com/caoculus/Tetris/blob/6cd5a72e675ff5d483a5618f1623d84c9f099533/game/common.hpp#L104-L110) and build from source.

The program allows the user to specify the transparency of the playfield. Using 10 equal divisions on Gamma 2.2, the user can specify a value of the executable between 0 and 9. By default, if no argument is given, the transparency is 4.

It is also possible to use your own texture atlas. Follow the template to specify the location of each game object in [texatlas.layout](https://github.com/caoculus/Tetris/blob/6cd5a72e675ff5d483a5618f1623d84c9f099533/assets/texatlas.layout) in the assets.

## Build:

Only building on linux is currently supported. To build for linux, clone the master branch of the release and ensure the following dependencies are installed

Ubuntu: 
```bash
sudo apt install libglfw3 libglfw3-dev libglew2.2 libglew-dev libpng-dev cimg-dev
```
Arch:
```bash
sudo pacman -S glfw-x11 glew libpng cimg
```

To build for windows, please clone the windows branch and use [MinGW-w64](https://www.mingw-w64.org/). On arch linux, the build dependencies can be installed from the AUR with
```bash
yay -S mingw-w64-binutils mingw-w64-cmake mingw-w64-configure mingw-w64-crt mingw-w64-environment mingw-w64-gcc mingw-w64-glew mingw-w64-glfw mingw-w64-gmp mingw-w64-headers mingw-w64-libpng mingw-w64-lzlib mingw-w64-make mingw-w64-pkg-config mingw-w64-winpthreads mingw-w64-zlib
```

If you want to build on windows, please use [WSL](https://docs.microsoft.com/en-us/windows/wsl/install). The configuration for building on windows is not present at the time.

## Screenshots:

First 100 levels with default dimming during a line clear.
![image](https://user-images.githubusercontent.com/71615343/148637532-5395e4f3-1ced-44ab-a327-fd666acb217d.png)

S1 with 0 dimming.
![image](https://user-images.githubusercontent.com/71615343/148637474-0ea49e90-a686-44b8-a0fb-e652dd40835d.png)

Death at S2 with full dimming (9)
![image](https://user-images.githubusercontent.com/71615343/148637204-b8c2b68a-0e74-4282-b01d-fe1e7a63cd8e.png)

