[Back](../README.md)
# Dependencies
## Install project dependencies

    $ sudo apt install ca-certificates
    $ sudo apt update && sudo apt full-upgrade -y
    $ sudo apt install -y libtool pkg-config build-essential autoconf \
                          automake make ninja-build cmake gcc git bison \
                          python3 libreadline-dev gawk texinfo bison file \
                          wget libssl-dev curl xorg-dev libwayland-dev \
                          libxkbcommon-dev wayland-protocols extra-cmake-modules libglm-dev

### OpenGL

      $ sudo apt-get install -y libgl1-mesa-dev

### Vulkan 
    
      $ sudo apt install -y libvulkan1 mesa-vulkan-drivers vulkan-tools vulkan-validationlayers-dev spirv-tools
      $ git clone https://github.com/KhronosGroup/Vulkan-Headers.git
      $ cd Vulkan-Headers
      $ cmake -S . -B build && cmake --build build && sudo cmake --install build

### [GLFW3](https://www.glfw.org/docs/3.3/build_guide.html)

        $ cd ~  
        $ git clone -b 3.3-stable https://github.com/glfw/glfw.git
        $ cd glfw
        $ cmake -S . -B build && cmake --build build && sudo cmake --install build

### [POSTGRESQL](postgresql.md)

        $ sudo sh -c 'echo "deb https://apt.postgresql.org/pub/repos/apt $(lsb_release -cs)-pgdg main" > /etc/apt/sources.list.d/pgdg.list'
        $ wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
        $ sudo apt-get update
        $ sudo apt-get -y install libpq-dev postgresql-16

  [Note] remove default service -> postgresql will be start from docker container

        $ sudo systemctl stop postgresql
        $ sudo systemctl disable postgresql
        $ sudo iptables -I INPUT 1 -p tcp --dport [PORT] -j ACCEPT

#### DOCKER

- https://docs.docker.com/engine/install/debian/#install-using-the-repository
- Add Docker's official GPG key
- 
        $ sudo apt-get update
        $ sudo apt-get install -y ca-certificates curl
        $ sudo install -m 0755 -d /etc/apt/keyrings
        $ sudo curl -fsSL https://download.docker.com/linux/debian/gpg -o /etc/apt/keyrings/docker.asc
        $ sudo chmod a+r /etc/apt/keyrings/docker.asc

- Add the repository to Apt sources:

        $ echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/debian $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
        $ sudo apt-get update

- To install the latest version, run:

        $ sudo apt-get install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

- Verify that the installation is successful by running the hello-world image:

        $ sudo docker run hello-world

- Install Docker service     

        $ sudo nano /etc/systemd/system/docker-compose-database.service
        $ sudo systemctl enable docker-compose-database
        $ sudo iptables -I INPUT 1 -p tcp --dport 5432 -j ACCEPT

### PQXX (NOTE install postgres first)

    $ git clone -b 7.8.1 https://github.com/jtv/libpqxx.git
    $ cd libpqxx
    $ sudo su
    $ cmake -S . -B build -DCMAKE_CXX_STANDARD=20 -DBUILD_DOC=OFF -DBUILD_TEST=OFF -DSKIP_BUILD_TEST=ON
    $ cmake --build build
    $ sudo cmake --install build

### SPDLOG

    $ git clone -b v1.13.0 https://github.com/gabime/spdlog.git
    $ cd spdlog
    $ sudo su
    $ cmake -S . -B build
    $ cmake --build build
    $ sudo cmake --install build

### CATCH2

    $ git clone -b v3.4.0 https://github.com/catchorg/Catch2.git
    $ cd Catch2
    $ sudo su
    $ cmake -S . -B build
    $ cmake --build build
    $ sudo cmake --install build

### LIBMODBUS
  
    $ git clone -b v3.1.10 --recursive https://github.com/stephane/libmodbus.git
    $ cd libmodbus
    $ sudo ./autogen.sh
    $ sudo ./configure 
    $ sudo make install    

### QT dependencies (future usage)

      $ sudo apt-get install -y libboost-all-dev libudev-dev libinput-dev libts-dev libmtdev-dev \
                                libjpeg-dev libfontconfig1-dev libssl-dev libdbus-1-dev libglib2.0-dev \
                                libxkbcommon-dev libegl1-mesa-dev libgbm-dev libgles2-mesa-dev mesa-common-dev \
                                libasound2-dev libpulse-dev gstreamer1.0-omx libgstreamer1.0-dev \
                                libgstreamer-plugins-base1.0-dev  gstreamer1.0-alsa libvpx-dev libsrtp2-dev \ 
                                libsnappy-dev libnss3-dev "^libxcb.*" flex bison libxslt-dev ruby gperf \
                                libbz2-dev libcups2-dev libatkmm-1.6-dev libxi6 libxcomposite1 libfreetype6-dev \
                                libicu-dev libsqlite3-dev libxslt1-dev

      $ sudo apt-get install -y libavcodec-dev libavformat-dev libswscale-dev libx11-dev freetds-dev libsqlite3-dev \
                                libpq-dev libiodbc2-dev firebird-dev libgst-dev libxext-dev libxcb1 libxcb1-dev \
                                libx11-xcb1 libx11-xcb-dev libxcb-keysyms1 libxcb-keysyms1-dev libxcb-image0 \
                                libxcb-image0-dev libxcb-shm0 libxcb-shm0-dev libxcb-icccm4 libxcb-icccm4-dev \
                                libxcb-sync1 libxcb-sync-dev libxcb-render-util0 libxcb-render-util0-dev \
                                libxcb-xfixes0-dev libxrender-dev libxcb-shape0-dev libxcb-randr0-dev \
                                libxcb-glx0-dev libxi-dev libdrm-dev libxcb-xinerama0 libxcb-xinerama0-dev \
                                libatspi2.0-dev libxcursor-dev libxcomposite-dev libxdamage-dev libxss-dev \
                                libxtst-dev libpci-dev libcap-dev libxrandr-dev libdirectfb-dev libaudio-dev \
                                libxkbcommon-x11-dev

