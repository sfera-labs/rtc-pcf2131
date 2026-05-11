# NXP PCF2131 RTC driver

Driver for the NXP PCF2131 real time clock used by [Sfera Labs](https://www.sferalabs.cc/) products.

## Compile and Install

Make sure your system is updated:

    sudo apt update
    sudo apt upgrade

If you are using a **32-bit** OS, add to `/boot/firmware/config.txt` (`/boot/config.txt` in older versions) the following line: [[why?](https://github.com/raspberrypi/firmware/issues/1795)]

    arm_64bit=0

Reboot:

    sudo reboot

After reboot, install required tools:

    sudo apt install git device-tree-compiler dkms linux-headers-$(uname -r)

Clone this repo:

    git clone --depth 1 https://github.com/sfera-labs/rtc-pcf2131

    cd rtc-pcf2131

### Recommended installation mode: DKMS

This is the recommended mode. It automatically rebuilds and reinstalls the module when new kernel versions are installed.

Register, build and install with DKMS:

    sudo dkms add .
    sudo dkms build -m rtc-pcf2131 -v $(cat VERSION)
    sudo dkms install -m rtc-pcf2131 -v $(cat VERSION)

### Advanced installation mode: manual make install (running kernel only)

Use this only if you specifically want to install for the current running kernel version only.

    make clean
    make
    sudo make install

Manual mode does not provide automatic rebuild on kernel upgrades.

### Enable overlay at boot

If you are using a Raspberry Pi (CM) **5** you should disable its RTC. To this end, add to `/boot/firmware/config.txt` the following line:

    dtparam=rtc=off

To enable this RTC driver, add to `/boot/firmware/config.txt` the following line:

    dtoverlay=rtc-pcf2131

Reboot:

    sudo reboot

## Usage

The RTC seamlessly integrates with the system's standard date and time functionalities.

When an NTP server is available, the system automatically synchronizes the RTC date and time. Conversely, if no network connection is available or the NTP service is disabled, the system relies on the RTC's stored values.  

You can manage and configure the RTC using the `timedatectl` and `hwclock` utilities.

The device node is available at `/dev/rtc0`.

If you are using a Raspberry Pi (CM) **5** and you didn't disable its RTC, this device will be `/dev/rtc1` instead.

The sysfs interface for the RTC is accessible at `/sys/class/rtc/rtc0` (or `rtc1`). In addition to the standard RTC attributes, it includes the `battery_low` file. Reading this file returns `1` if the RTC backup battery voltage is low and `0` otherwise.

## Advanced usage

The file `pcf2131_example.c` contains a C example to read the RTC date/time and other information using the `ioctl()` system call.

Compile it with:

    gcc -s -Wall pcf2131_example.c -o pcf2131_example

Run it:

    $ sudo ./pcf2131_example 
    Date/time: 2023-1-3 14:04:42
    Voltage low flags: 0x2
    > Backup voltage is low
