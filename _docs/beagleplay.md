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
    $ sudo apt update && sudo apt full-upgrade -y
    $ sudo apt install -y libtool pkg-config build-essential autoconf automake make ninja-build cmake gcc git bison python3 libreadline-dev gawk texinfo bison file wget libssl-dev curl xorg-dev libwayland-dev libxkbcommon-dev wayland-protocols extra-cmake-modules libglm-dev

- OpenGL
- Vulkan

        $ sudo apt install libvulkan1 mesa-vulkan-drivers vulkan-tools vulkan-validationlayers-dev spirv-tools

- GLFW3
  https://www.glfw.org/docs/3.3/build_guide.html

        $ cd ~  
        $ git clone -b 3.3-stable https://github.com/glfw/glfw.git
        $ cd glfw
        $ cmake -S . -B build && cmake --build build && sudo cmake --install build


- SDL3 / SDL3_image
- https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/
- https://trenki2.github.io/blog/2017/07/04/using-sdl2-image-with-cmake/

(from source)

        $ cd ~
        $ git clone -b 495e432fb https://github.com/libsdl-org/SDL.git
        $ cd SDL
        $ cmake -S . -B build && cmake --build build && sudo cmake --install build
        
        $ cd ~
        $ git clone -b 5baa3c8c7a https://github.com/libsdl-org/SDL_image.git
        $ cd SDL_image
        $ cmake -S . -B build && cmake --build build && sudo cmake --install build

- DOCKER
  - https://docs.docker.com/engine/install/debian/#install-using-the-repository
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

- POSTGRESQL

        $ sudo sh -c 'echo "deb https://apt.postgresql.org/pub/repos/apt $(lsb_release -cs)-pgdg main" > /etc/apt/sources.list.d/pgdg.list'
        $ wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
        $ sudo apt-get update
        $ sudo apt-get -y install libpq-dev postgresql-16

    [Note] remove default service -> postgresql will be start from docker container
        
        $ sudo systemctl stop postgresql
        $ sudo systemctl disable postgresql
        $ sudo iptables -I INPUT 1 -p tcp --dport [PORT] -j ACCEPT

- PQXX (NOTE install postgres first)

        $ git clone -b 7.8.1 https://github.com/jtv/libpqxx.git
        $ cd libpqxx
        $ cmake -S . -B build -DBUILD_DOC=OFF -DBUILD_TEST=OFF -DSKIP_BUILD_TEST=ON && cmake --build build && sudo cmake --install build

##  [TODO] PREEMPT_RT
https://bootlin.com/doc/training/preempt-rt/preempt-rt-slides.pdf

## Enable zRAM

    $ sudo apt install zram-tools
    $ echo -e "ALGO=zstd\nPERCENT=60" | sudo tee -a /etc/default/zramswap
    $ sudo service zramswap reload

https://wiki.debian.org/ZRam
https://wiki.archlinux.org/title/Zram

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

## [TODO] Create a Target TOOLCHAIN
