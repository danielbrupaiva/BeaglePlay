[BACK](../README.md)
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

      $ ssh debian@BeaglePlay.local

  [TARGET]

      $ sudo apt install openssh-server

  [HOST]

      $ ssh-keygen -> configure as you want. 
      $ ssh-copy-id -i [/home/daniel/.ssh/beagle.pub] [username]@[IP]

## [DEPENDENCIES](dependencies.md)
## [PREEMPT_RT](preempt_rt.md)

## Enable zRAM

    $ sudo apt install zram-tools
    $ echo -e "ALGO=zstd\nPERCENT=60" | sudo tee -a /etc/default/zramswap
    $ sudo service zramswap reload

https://wiki.debian.org/ZRam
https://wiki.archlinux.org/title/Zram

 