# Tetris

Lagless clone of [Tetris The Grand Master 1](https://tetris.fandom.com/wiki/Tetris_The_Grand_Master) with custom backgrounds written in C++ and OpenGL. The background changes every 100 levels.

### Usage:

There are multiple executables built with different controls. For now, to use your own keys, edit the keys in [common.hpp](https://github.com/caoculus/Tetris/blob/6cd5a72e675ff5d483a5618f1623d84c9f099533/game/common.hpp#L104-L110) and build from source.

The program allows the user to specify the transparency of the playfield. Using 10 equal divisions on Gamma 2.2, the user can specify a value of the executable between 0 and 9. By default, if no argument is given, the transparency is 4.

It is also possible to use your own texture atlas. Follow the template to specify the location of each game object in [texatlas.layout](https://github.com/caoculus/Tetris/blob/6cd5a72e675ff5d483a5618f1623d84c9f099533/assets/texatlas.layout) in the assets.

### Screenshots:

![image](https://user-images.githubusercontent.com/71615343/148182568-b13dbca6-1521-476b-999c-12eba090119f.png)

![image](https://user-images.githubusercontent.com/71615343/148182964-f142f877-3d2c-4527-9ed7-04d50063b357.png)
