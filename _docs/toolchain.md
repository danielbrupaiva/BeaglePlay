# CROSSTOOL-NG
~
[REFERENCE] BOOTLIN
[Link] https://toolchains.bootlin.com/releases_aarch64.html

[Link] https://wiki.qt.io/Cross-Compile_Qt_6_for_Raspberry_Pi

[Link] https://github.com/MuyePan/CrossCompileQtForRpi/tree/master

## @TARGET

    $ gcc --version -> gcc (Debian 10.2.1-6) 10.2.1 20210110
    $ ld --version -> GNU ld (GNU Binutils for Debian) 2.35.2
    $ ldd --version -> ldd (Debian GLIBC 2.31-13+deb11u8) 2.31
    $ uname -r -> 5.10.168-ti-arm64-r113


## @HOST

1 - Install Crosstool-NG

    TODO: review dependencies
    $ sudo apt install -y build-essential \
                            git \
                            autoconf \
                            bison \
                            flex \
                            texinfo \
                            help2man \
                            gawk \
                            libtool-bin \
                            libncurses5-dev \
                            unzip
    
    $ git clone https://github.com/crosstool-ng/crosstool-ng
    $ cd crosstool-ng/
    $ git checkout 36ad0b1
    
    $ ./bootstrap
    $ ./configure --enable-local
    $ make


2 - Configure the toolchain to produce
- Configure according version found in target
- Path and misc options: 
    * If not set yet, enable Try features marked as EXPERIMENTAL

- Target options:
    * Set Emit assembly for CPU (ARCH_CPU) to cortex-a53.
    * Check Endianness (ARCH_ENDIAN) is set to Little endian

- Toolchain options:
    * Set Tuple's vendor string (TARGET_VENDOR) to [TARGET].
    * Set Tuple's alias (TARGET_ALIAS) to aarch64-linux. This way, we will be able to use
the compiler as aarch64-linux-gcc instead of aarch64-[TARGET]-linux-musl-gcc, which
is much longer to type.

- Operating System:
    * Set Version of linux to the [TARGET KERNEL] version that is proposed. We choose this version because
the kernel we will be using is the 6.4.x kernel. Indeed, the linux kernel is backward
compatible and therefore older linux headers will work fine on a newer running kernel.

- C-library:
    * [TARGET LD VERSION]

- C compiler:
    * [TARGET GCC VERSION]

- Debug facilities:
    * Remove all options here. Some debugging tools can be provided in the toolchain, but they
can also be built by filesystem building tools.

3 - Build toolchain

    $ ./ct-ng build
    
# SYSROOT
## @TARGET

  Install all dependencies needed
    
## QT dependencies (future usage)

    $ sudo apt-get install libboost-all-dev libudev-dev libinput-dev libts-dev libmtdev-dev libjpeg-dev libfontconfig1-dev libssl-dev libdbus-1-dev libglib2.0-dev libxkbcommon-dev libegl1-mesa-dev libgbm-dev libgles2-mesa-dev mesa-common-dev libasound2-dev libpulse-dev gstreamer1.0-omx libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev  gstreamer1.0-alsa libvpx-dev libsrtp2-dev libsnappy-dev libnss3-dev "^libxcb.*" flex bison libxslt-dev ruby gperf libbz2-dev libcups2-dev libatkmm-1.6-dev libxi6 libxcomposite1 libfreetype6-dev libicu-dev libsqlite3-dev libxslt1-dev

    $ sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libx11-dev freetds-dev libsqlite3-dev libpq-dev libiodbc2-dev firebird-dev libgst-dev libxext-dev libxcb1 libxcb1-dev libx11-xcb1 libx11-xcb-dev libxcb-keysyms1 libxcb-keysyms1-dev libxcb-image0 libxcb-image0-dev libxcb-shm0 libxcb-shm0-dev libxcb-icccm4 libxcb-icccm4-dev libxcb-sync1 libxcb-sync-dev libxcb-render-util0 libxcb-render-util0-dev libxcb-xfixes0-dev libxrender-dev libxcb-shape0-dev libxcb-randr0-dev libxcb-glx0-dev libxi-dev libdrm-dev libxcb-xinerama0 libxcb-xinerama0-dev libatspi2.0-dev libxcursor-dev libxcomposite-dev libxdamage-dev libxss-dev libxtst-dev libpci-dev libcap-dev libxrandr-dev libdirectfb-dev libaudio-dev libxkbcommon-x11-dev

## @HOST

1 - RSYNC SYSROOT FROM TARGET

    $ mkdir sysroot sysroot/usr sysroot/opt
    
    $ cd sysroot   
    $ rsync -avzS --rsync-path="rsync" --delete debian@BeaglePlay:/usr/local ./usr
    $ rsync -avzS --rsync-path="rsync" --delete debian@BeaglePlay:/usr/include ./usr
    $ rsync -avzS --rsync-path="rsync" --delete debian@BeaglePlay:/usr/lib ./usr 
    $ rsync -avzS --rsync-path="rsync" --delete debian@BeaglePlay:/lib .
    $ rsync -avzS --rsync-path="rsync" --delete debian@BeaglePlay:/opt .

2 - Fix symbolic links

    $ sudo apt install symlinks
    $ cd ..
    $ symlinks -rc sysroot
