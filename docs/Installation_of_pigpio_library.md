[Back to Top page](../README.md)

# Overview
This pape provides information related to pigpio library.
Main target language is C/C++.

# Installation of pigpio library

See [Download & Install page](http://abyz.me.uk/rpi/pigpio/download.html) in [Official page](http://abyz.me.uk/rpi/pigpio/index.html).

# Information for programming
This repository uses pigpio Daemon to control GPIO pin, not use pigpio directory because I assume that some learners share one Rasp. Pi and I want not to need a root privilege.

## Preparation of pigpio Daemon

Prepare the following file.

* /etc/systemd/system/[pigpiod.service](../system_settings/pigpiod.service)

The detailed options which pigpio daemon can use is [here](http://abyz.me.uk/rpi/pigpio/pigpiod.html).<br>
And execute following to activate pigpio daemon.

```shell
$ sudo systemctl enable pigpiod
$ sudo systemctl start pigpiod
$ sudo systemctl status pigpiod
```

## Basic usage of pigpio

[pigpiod C I/F](http://abyz.me.uk/rpi/pigpio/pdif2.html) page is useful to make programs.
Basic information is as follows.

* header information
  * #include <pigpiod_if2.h>
* build/compile information
  * options
    * `-Wall -pthread`
  * linker
    * `-lpigpiod_if2`
    * `-lrt`
      * This linker is shown as necessary thing in [pigpiod C I/F](http://abyz.me.uk/rpi/pigpio/pdif2.html) page, but it seems not to be because it is included in libgcc.

## Usage on ROS2
When pigpio is used in ROS2 packages, CMakeLists.txt must be written as follows(only related parts.)

```CMakeLists
target_compile_options(<target name>
  PUBLIC -Wall -pthread
)
target_link_libraries(<target name>
  pigpiod_if2
)
```

# GPIO pin assign
There are two ways of pin assign, one is based on chips and another is based on layout.
pigpio uses Broadcom number, which means number based on chips.
If use right-buttom pin of the figure below in a program, number to indicate the pin is 21, is not 40.

![gpio_assin](./figs/gpio_pin.png)

Information aroud p.12 is useful for settings of pins on chip.

- [BCM2835](https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf)

# Tips
## Pull up and Pull down

It is important to know Pull up and Pull down.
I recommend to search them by google, etc. and understand it.

## References

- [gpio official pages](http://abyz.me.uk/rpi/pigpio/index.html)
- [gpio.h on github](https://github.com/joan2937/pigpio/blob/master/pigpio.h)
