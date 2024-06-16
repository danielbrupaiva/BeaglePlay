[BACK](../README.md)
# TOOLCHAIN

[REFERENCE] 

[BOOTLIN](https://toolchains.bootlin.com/releases_aarch64.html)

[Link] https://wiki.qt.io/Cross-Compile_Qt_6_for_Raspberry_Pi

[Link] https://github.com/MuyePan/CrossCompileQtForRpi/tree/master

# TARGET

Check system versions:

    $ uname -a (all)
    $ uname -r (kernel only)
    $ gcc --version
    $ ld --version
    $ ldd --version

 NOTES: Make sure you have install all [dependencies](dependencies.md).

# HOST

## SYSROOT

    $ cd
    $ mkdir project_folder
    $ cd !$
    $ mkdir sysroot_folder sysroot_folder/usr sysroot_folder/opt
    $ cd sysroot_folder
    
    $ rsync -avzS --rsync-path="rsync" --delete $USER@$IP:/usr/local ./usr
    $ rsync -avzS --rsync-path="rsync" --delete $USER@$IP:/usr/include ./usr
    $ rsync -avzS --rsync-path="rsync" --delete $USER@$IP:/usr/lib ./usr
    $ rsync -avzS --rsync-path="rsync" --delete $USER@$IP:/lib .
    $ rsync -avzS --rsync-path="rsync" --delete $USER@$IP:/opt .

Fix symbolic links

    $ sudo apt install symlinks
    $ cd ..
    $ symlinks -rc sysroot_folder

## TOOLCHAIN

1 - Environment setup

    $ sudo apt install -y  gcc gdb gdb-multiarch build-essential autoconf bison flex cmake make ninja-build\
                            gawk wget git diffstat unzip texinfo help2man libtool-bin libncurses5-dev \
                            chrpath socat cpio python3 python3-pip python3-pexpect xz-utils debianutils \
                            iputils-ping python3-git python3-jinja2 python3-subunit zstd liblz4-tool file \
                            locales libacl1 rsync symlinks

    $ git clone -b crosstool-ng-1.26.0 https://github.com/crosstool-ng/crosstool-ng
    $ cd crosstool-ng
    $ ./bootstrap
    $ ./configure --enable-local
    $ make
    $ ./ct-ng help
    $ ./ct-ng menuconfig

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