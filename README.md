# NXP PCF2131 RTC driver

Debian-based Linux kernel module for the NXP PCF2131 real-time clock used by [Sfera Labs](https://www.sferalabs.cc/) products.

[![Build tests [stable oldstable]](https://github.com/sfera-labs/rtc-pcf2131/actions/workflows/build-apt.yml/badge.svg)](https://github.com/sfera-labs/rtc-pcf2131/actions/workflows/build-apt.yml)
[![Build tests [firmware]](https://github.com/sfera-labs/rtc-pcf2131/actions/workflows/build-fw.yml/badge.svg)](https://github.com/sfera-labs/rtc-pcf2131/actions/workflows/build-fw.yml)

## Installation

For source-based installation, see this [installation guide](https://github.com/sfera-labs/sl-kmod-commons/blob/main/INSTALLATION.md).

If the Sfera Labs APT repository is not configured yet, [add the repository and install its keyring](https://github.com/sfera-labs/apt#install).

Install the package:

    sudo apt update
    sudo apt install rtc-pcf2131-dkms

The package registers the module with DKMS, which builds it for kernels with matching headers and rebuilds it when new kernel headers are installed. It also installs the device-tree overlay.

If using a Raspberry Pi 5 or Compute Module 5, disable its built-in RTC by adding this to `/boot/firmware/config.txt`:

    dtparam=rtc=off

Enable the RTC overlay by adding this line to the same file:

    dtoverlay=rtc-pcf2131

Finally, reboot to apply the configuration:

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
