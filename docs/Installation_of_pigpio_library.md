[Back to Top page](../README.md)

# Overview
This pape provides information related to pigpio library.
Main target language is C/C++.

# Installation of pigpio library

See [Download & Install page](http://abyz.me.uk/rpi/pigpio/download.html) in [Official page](http://abyz.me.uk/rpi/pigpio/index.html).

# Information for programming
## Basic usage of pigpio

[pigpio C I/F](http://abyz.me.uk/rpi/pigpio/cif.html) page is useful to make programs.
Basic information is as follows.

* header information
  * #include <pigpio.h>
* build/compile information
  * options
    * `-Wall -pthread`
  * linker
    * `-lpigpio`
    * `-lrt`
      * This linker is shown as necessary thing in [pigpio C I/F](http://abyz.me.uk/rpi/pigpio/cif.html) page, but it seems not to be because it is included in libgcc.

## Usage on ROS2
When pigpio is used in ROS2 packages, CMakeLists.txt must be written as follows(only related parts.)

```CMakeLists
target_compile_options([ターゲット名]
  PUBLIC -Wall -pthread
)
target_link_libraries([ターゲット名]
  pigpio
)
```

## GPIO pin assign
There are two ways of pin assign, one is based on chips and another is based on layout.
pigpio uses Broadcom number, which means number based on chips.
If use right-buttom pin of the figure below in a program, number to indicate the pin is 21, is not 40.

![gpio_assin](./figs/gpio_pin.png)
