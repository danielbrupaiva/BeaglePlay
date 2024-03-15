# GUI with Dear ImGUI framework

Opensource Graphical User Interface in C++ using Dear ImGui Framework

Key features:
- Modern C++20 
- CMake -> FetchContent (~ package management)
- Native (x86_64) and Cross (arm64) compilation
- App-Core architecture
- Immediate mode GUI (Dear IMGUI)
- OpenGL + SDL3 renderer graphics backend (GLFW to be implemented)
- PostgreSQL database (PQxx)
- Modbus TCP/IP connection (to be implemented)
- CAN-BUS connection (to be implemented)
- Remote access via OpenVPN (to be implemented)

## Targets

- Host on Linux
- BeagleBone Play (AARCH64)
  - https://www.beagleboard.org/boards/beagleplay
  - https://docs.beagleboard.org/latest/boards/beagleplay/
  <img src="./resources/beagleplay.png" width="500" >
- Raspberry Pi4 (AARCH64) (to be implemented)
  - https://www.raspberrypi.com/products/raspberry-pi-4-model-b/
    <img src="./resources/raspberry.png" width="500" >
# Libraries
  - OpenGL https://www.opengl.org/  
![opengl.png](resources%2Fopengl.png)
  - Simple DirectMedia Layer (SDL) Version 3.0 + SDL_image 3.0
    - https://www.libsdl.org/
    - https://github.com/libsdl-org/SDL.git
    - https://github.com/libsdl-org/SDL_image.git
- Dear IMGUI 
  - Project fork from source
  - https://github.com/ocornut/imgui.git
  - Add CMakeList.txt file to integrate with project
  - https://github.com/danielbrupaiva/imgui.git 
- PostgreSQL 16.1
  - [postgresql.md](Database/postgresql.md)
- PQXX Official C++ client API for PostgreSQL 7.8.1
  - https://www.postgresql.org/
  - https://pqxx.org/
  - https://libpqxx.readthedocs.io/en/stable/
- Catch2 v3.4.0
  - https://github.com/catchorg/Catch2.git
- Spdlog v1.13.0
  - https://github.com/gabime/spdlog.git

Package Management:

- CMake -> FetchContent (~package manager)
- https://cmake.org/cmake/help/latest/module/FetchContent.html
- CONAN (to be implement)

![cmake_lib.png](resources%2Fcmake_lib.png)

https://decovar.dev/blog/2021/03/08/cmake-cpp-library/

### PQXX 


Catch2
Spdlog

### Dear IMGUI


### SDL3

[Link] https://github.com/libsdl-org/SDL.git

    $ cd SDL
    $ git checkout dad1a84be4e9236267dd7c5393b56c60b3ed7875
    $ sudo su
    $ cmake -S . -B build && cmake --build build && cmake --install build

### SDL3_image

[Link] https://github.com/libsdl-org/SDL_image.git

    $ git clone https://github.com/libsdl-org/SDL_image.git
    $ cd SDL_image
    $ git checkout 77441588fa084269d4fe99ba21e2690853245764
    $ sudo su
    $ cmake -S . -B build && cmake --build build && cmake --install build


## Build

    $ sudo apt-get install -y mesa-utils \
                              libglu1-mesa-dev \
                              freeglut3-dev \
                              mesa-common-dev \
                              libxrandr-dev \
                              libxinerama-dev \
                              libxcursor-dev \
                              libxi-dev
    
    $ mkdir build && cd build
    $ cmake -GNinja -DCROSS_COMPILER=ON -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain.cmake ..
    $ ninja

# TODO

- Review toolchain for targets
- ~~Review build dependencies~~
- Work on tests
- Implement Git workflow for build
- Implement CONAN as package manager ? 

On App (Frontend)
- OpenGL + SDL3/renderer
- Load texture
- State Machine
- Mouse swipe
- Mockup UI on Figma and implementation

On Core (Backend)
- Logger
- User
- PostgreSQL database with connection pooling
- Modbus TCP/IP
- OpenCV

Target Linux (System)
- Remote access (OpenVPN)
- Customized Linux


# References

  - https://en.cppreference.com/
  - https://github.com/ocornut
  - https://github.com/MikeShah
  - https://github.com/TheCherno/Cherno
  - https://www.youtube.com/@CppCon
  - https://www.youtube.com/@LearnQtGuide
  - https://www.youtube.com/@ulasdikme7307
  - https://www.youtube.com/@DavesGarage
  - https://www.youtube.com/@ZenSepiol