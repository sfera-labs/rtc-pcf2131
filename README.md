# NXP PCF2131 RTC driver

Driver for the NXP PCF2131 real time clock used by [Sfera Labs](https://www.sferalabs.cc/) products.

## Compile and Install

*For installation on Ubuntu [read this](https://github.com/sfera-labs/knowledge-base/blob/main/raspberrypi/kernel-modules-ubuntu.md).*

Make sure your system is updated:

    sudo apt update
    sudo apt upgrade

If you are using a Raspberry Pi (CM) **4** and a **32-bit** OS, add to `/boot/config.txt` the following line: [[why?](https://github.com/raspberrypi/firmware/issues/1795)]

    arm_64bit=0
    
Reboot:

    sudo reboot

After reboot, install git and the Raspberry Pi kernel headers:

    sudo apt install git raspberrypi-kernel-headers

Clone this repo:

    git clone --depth 1 https://github.com/sfera-labs/rtc-pcf2131

Make and install:

    cd rtc-pcf2131
    make clean
    make
    sudo make install
    
Compile the Device Tree and install it:

    dtc -@ -Hepapr -I dts -O dtb -o rtc-pcf2131.dtbo rtc-pcf2131.dts
    sudo cp rtc-pcf2131.dtbo /boot/overlays/

Add to `/boot/config.txt` the following line:

    dtoverlay=rtc-pcf2131

Reboot:

    sudo reboot

After reboot, test the installation by checking that no error is returnd when running:

    sudo hwclock -w
    sudo hwclock -r

The system will automatically syncronize the RTC date/time when able to connect to an NTP server and, vice versa, the RTC stored values will be used when connection is not available.

## Advanced usage

The device corresponding to the rtc will be available at `/dev/rtc0` and its sysfs interface under `/sys/class/rtc/rtc0/`.

The file `pcf2131_example.c` contains a C example to read the RTC date/time and other information (such as low backup battery voltage) using the `ioctl()` system call.

Compile it with:

    gcc -s -Wall pcf2131_example.c -o pcf2131_example

Run it:

    $ sudo ./pcf2131_example 
    Date/time: 2023-1-3 14:04:42
    Voltage low flags: 0x2
    > Backup voltage is low
