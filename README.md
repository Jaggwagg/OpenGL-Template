# OpenGL-Template

OpenGL-Template is a simple template file for basic modern, core OpenGL 3.3 with CMake 3.1.

This template contains commonly used libraries GLFW, GLAD, GLM, and STB.

Requires git and CMake 3.1 or later to build.

## Testing Environment
* OS: Arch Linux
* Kernel: x86_64 5.13.13-zen1-1-zen

## Dependencies
* CMake 3.1 or greater
* OpenGL 3.3 or higher supported graphics card and drivers
* C++ compiler

## Compiling and Running

```shell
git clone https://github.com/Jaggwagg/OpenGL-Template.git
cd OpenGL-Template
git submodule init
git submodule update
mkdir bin/build
cd build
cmake ..
make
./opengl
```

## License
[MIT](https://choosealicense.com/licenses/mit/)