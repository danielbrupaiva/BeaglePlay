# BeaglePlay
https://docs.beagleboard.org/latest/intro/support/getting-started.html#beagleboard-getting-started

## Debian image for BeaglePlay on-board eMMC flash
- https://www.beagleboard.org/distros/beagleplay-11-8-2023-10-07-10gb-emmc-xfce-flasher
- Linux Image: BeaglePlay 11.8 2023-10-07 10GB eMMC Xfce Flasher
- Kernel: 5.10.168-ti-arm64-r111
- U-Boot: https://git.beagleboard.org/beagleboard/u-boot/-/tree/v2021.01-ti-BeaglePlay-Release

- Download and flash into a SDCard
- Insert card, boot and wait the magic
- This process will set emmc with the linux image

## Wifi configuration
https://docs.beagleboard.org/latest/boards/beagleplay/demos-and-tutorials/connect-wifi.html#beagleplay-connect-wifi

## SSH
- default username:password is [debian:temppwd]
- [//]: # (  TODO: create a ssh  key)
      $ ssh debian@BeaglePlay

## Install project dependencies
    $ sudo apt install ca-certificates
    $ sudo apt update && sudo apt full-upgrade
    $ sudo apt install -y libtool pkg-config build-essential autoconf automake make ninja-build cmake gcc git bison python3\
                          libreadline-dev gawk texinfo bison file wget libssl-dev curl 
NEED to review
                      glibc-source libc6 libxxf86vm-dev libxi-dev
                      libboost-all-dev libudev-dev libinput-dev libts-dev libmtdev-dev libjpeg-dev libfontconfig1-dev libssl-dev libdbus-1-dev libglib2.0-dev libxkbcommon-dev libegl1-mesa-dev libgbm-dev libgles2-mesa-dev mesa-common-dev libasound2-dev libpulse-dev gstreamer1.0-x libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev  gstreamer1.0-alsa libvpx-dev libsrtp2-dev libsnappy-dev libnss3-dev "^libxcb.*" flex bison libxslt-dev ruby gperf libbz2-dev libcups2-dev libatkmm-1.6-dev libxi6 libxcomposite1 libfreetype6-dev libicu-dev libsqlite3-dev libxslt1-dev \
                     libavcodec-dev libavformat-dev libswscale-dev libx11-dev freetds-dev libsqlite3-dev  libiodbc2-dev firebird-dev libgst-dev libxext-dev libxcb1 libxcb1-dev libx11-xcb1 libx11-xcb-dev libxcb-keysyms1 libxcb-keysyms1-dev libxcb-image0 libxcb-image0-dev libxcb-shm0 libxcb-shm0-dev libxcb-icccm4 libxcb-icccm4-dev libxcb-sync1 libxcb-sync-dev libxcb-render-util0 libxcb-render-util0-dev libxcb-xfixes0-dev libxrender-dev libxcb-shape0-dev libxcb-randr0-dev libxcb-glx0-dev libxi-dev libdrm-dev libxcb-xinerama0 libxcb-xinerama0-dev libatspi2.0-dev libxcursor-dev libxcomposite-dev libxdamage-dev libxss-dev libxtst-dev libpci-dev libcap-dev libxrandr-dev libdirectfb-dev libaudio-dev libxkbcommon-x11-dev
                      libclang-dev  gperf  libfontconfig1-dev libfreetype6-dev libx11-dev libx11-xcb-dev libxext-dev libxfixes-dev libxi-dev libxrender-dev libxcb1-dev libxcb-glx0-dev libxcb-keysyms1-dev libxcb-image0-dev libxcb-shm0-dev libxcb-icccm4-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-shape0-dev libxcb-randr0-dev libxcb-render-util0-dev libxcb-util-dev libxcb-xinerama0-dev libxcb-xkb-dev libxkbcommon-dev libxkbcommon-x11-dev libatspi2.0-dev libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev  gdbserver gdb-multiarch libxcb-cursor-dev
  - OpenGL
  - SDL2 / SDL2_image
  - https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/
    https://trenki2.github.io/blog/2017/07/04/using-sdl2-image-with-cmake/

  (from source)

      $ git clone https://github.com/libsdl-org/SDL.git
      $ cd SDL
      $ git checkout release-2.30.x
      $ cmake -S . -B build && cmake --build build
      $ sudo cmake --install build

      $ git clone https://github.com/libsdl-org/SDL_image.git
      $ cd SDL_image
      $ git checkout release-2.8.x
      $ cmake -S . -B build && cmake --build build
      $ sudo cmake --install build

NOTES: https://stackoverflow.com/questions/52813560/i-have-libsdl2-image-dev-installed-via-apt-get-but-cmake-cannot-find-it
- workaround
  Create a file in cmake configs folder /usr/lib/aarch64-linux-gnu/cmake/sdl2_image/sdl2_image-config.cmake

  and put this in it

  set(prefix "/usr")
  set(exec_prefix "${prefix}")
  set(libdir "${prefix}/lib/aarch64-linux-gnu")
  set(SDL2_IMAGE_PREFIX "/usr")
  set(SDL2_IMAGE_EXEC_PREFIX "/usr")
  set(SDL2_IMAGE_INCLUDE_DIRS "${prefix}/include/SDL2_image")
  set(SDL2_IMAGE_LIBRARIES "-lSDL2_image")


  - GLFW3
    https://www.glfw.org/docs/3.3/build_guide.html

        $ sudo apt install -y libglfw3-dev libglm-dev

  - Vulkan

        $ sudo apt install libvulkan1 mesa-vulkan-drivers vulkan-tools vulkan-validationlayers-dev spirv-tools

  - DOCKER
  https://docs.docker.com/engine/install/debian/#install-using-the-repository
    
    - Add Docker's official GPG key:
    
            $ sudo apt-get update
            $ sudo apt-get install ca-certificates curl
            $ sudo install -m 0755 -d /etc/apt/keyrings
            $ sudo curl -fsSL https://download.docker.com/linux/debian/gpg -o /etc/apt/keyrings/docker.asc
            $ sudo chmod a+r /etc/apt/keyrings/docker.asc
    
    - Add the repository to Apt sources:
    
           $ echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/debian $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
           $ sudo apt-get update
    
    - To install the latest version, run:

          $ sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
    
    - Verify that the installation is successful by running the hello-world image:
        
          $ sudo docker run hello-world


[//]: # (  TODO: Create docker compose file to start project database with docker)
- POSTGRESQL

        $ sudo sh -c 'echo "deb https://apt.postgresql.org/pub/repos/apt $(lsb_release -cs)-pgdg main" > /etc/apt/sources.list.d/pgdg.list'
        $ wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
        $ sudo apt-get update
        $ sudo apt-get -y install libpq-dev postgresql-16

    NOTES:
    - Installation will be used only for toolchain
      - Ensure service is not running

              $ sudo systemctl status postgresql
              $ sudo systemctl stop postgresq
              $ sudo systemctl disable postgresql

  - PQXX (NOTE install postgres first)

        $ git clone --recursive https://github.com/jtv/libpqxx.git -b 7.8.1
        $ cd libpqxx
        $ cmake -S . -B build -DBUILD_DOC=OFF -DBUILD_TEST=OFF -DSKIP_BUILD_TEST=ON && cmake --build build 
        $ sudo cmake --install build

##  PREEMPT_RT
https://bootlin.com/doc/training/preempt-rt/preempt-rt-slides.pdf
## Enable zRAM

    $ sudo apt install zram-tools
    $ echo -e "ALGO=zstd\nPERCENT=60" | sudo tee -a /etc/default/zramswap
    $ sudo service zramswap reload

https://wiki.debian.org/ZRam
https://wiki.archlinux.org/title/Zram
https://medium.com/@profjulianoramos/zram-para-melhorar-a-swap-do-linux-5d87a5718340

## Create a Target SYSROOT
[NOTE install all dependencies needed]
1 - RSYNC SYSROOT FROM TARGET

    $ mkdir sysroot sysroot/usr sysroot/opt
    
    $ cd sysroot   
    sudo rsync -avzS --rsync-path="rsync" --delete debian@BeaglePlay.local:/usr/local ./usr
    sudo rsync -avzS --rsync-path="rsync" --delete debian@BeaglePlay.local:/usr/include ./usr
    sudo rsync -avzS --rsync-path="rsync" --delete debian@BeaglePlay.local:/usr/lib ./usr
    sudo rsync -avzS --rsync-path="rsync" --delete debian@BeaglePlay.local:/lib .
    sudo rsync -avzS --rsync-path="rsync" --delete debian@BeaglePlay.local:/opt .

2 - Fix symbolic links

    $ sudo apt install symlinks
    $ cd ..
    $ symlinks -rc sysroot

## Create a Target TOOLCHAIN