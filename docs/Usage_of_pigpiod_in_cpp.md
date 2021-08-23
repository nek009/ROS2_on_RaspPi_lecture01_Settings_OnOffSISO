[Back to Top page](../README.md)

# Overview
Here, a way to control hardware through pigpiod is introduced briefly.
Target language is c++.<br>
Before show the way, a circuit which is used in this repository is shown in figure below.

![target circuit](figs/led_switch.png)

# Making the circuit
At first, make the circuit.

# Making a program
Detailed information is in [pigpiod C Interface](http://abyz.me.uk/rpi/pigpio/pdif2.html) in Official site.
Important sections are `ESSENTIAL` and `BASIC`.<br>

The rough flow of a program is as follwos.

1. Initialize to use pigpiod(pigpio_start)
1. Set GPIO modes(set_mode)
1. Use GPIOs(gpio_read, gpio_write)
1. End to use pigpiod(pigpio_stop)

pigpio daemon can treat plural Rasp. Pi through network, so commands or functions must be given which Rasp. Pi is targeted.
To do that, a return value of pigpio_start function is used.

## Simple usage

* source file
  * \<repo. directory\>/src/pigpio_library_test/src/[on_off_siso.cpp](../src/pigpio_library_test/src/on_off_siso.cpp)

### build and execute
Prepare the source file by DL or by creating yourself.

```shell
$ g++ -Wall -pthread -o on_off_siso on_off_siso.cpp -lpigpiod_if2
$ ./on_off_siso
```

If pushing a switch, a led will turn off.
If releasing a switch, a led will turn on.

### Explanation

<details><summary>Initialize to use pigpiod</summary><div>

[Line from 7 to 11 in on_off_siso.cpp](../src/pigpio_library_test/src/on_off_siso.cpp#L7-L10) shows an initialization which connect to target Rasp.Pi and return identifier. The arguments which are NULL means it means to connect localhost via 8888 port.
</div></details>
<details><summary>Set GPIO modes</summary><div>

[Line from 13 to 16 in on_off_siso.cpp](../src/pigpio_library_test/src/on_off_siso.cpp#L13-L16) shows the settings of gpio mode.
[Line 14 in on_off_siso.cpp](../src/pigpio_library_test/src/on_off_siso.cpp#L14) shows GPIO21 which is connected to a led is set as OUTPUT, and [Line 16 in on_off_siso.cpp](../src/pigpio_library_test/src/on_off_siso.cpp#L16) shows GPIO26 which is connected to a switch is set as INPUT.
</div></details>
<details><summary>Use GPIOs</summary><div>

[Line from 18 to 22 in on_off_siso.cpp](../src/pigpio_library_test/src/on_off_siso.cpp#L18-L22) controls a led by a state of a switch.<br>
[Line 19 in on_off_siso.cpp](../src/pigpio_library_test/src/on_off_siso.cpp#L19) reads a state of GPIO26 and store it in `input`.
Here, by a pull-down resistor for GPIO26, a state of GPIO26 becomes HIGH and `input` becomes `1` if a switch is pushed and one becomes LOW and `input` becomes `0` if it is released.<br>
[Line 20 in on_off_siso.cpp](../src/pigpio_library_test/src/on_off_siso.cpp#L20) controls an output of GPIO21 by `input` value.
Here, GPIO21 is a sinking digital output, so a led turns on if GPIO21 outputs `0` and it turns off if GPIO21 outputs `1`.
So if a switch is pushed, `input` becomes `1`, and GPIO21 outputs `1` and led turns off.<br>
And [Line 21 in on_off_siso.cpp](../src/pigpio_library_test/src/on_off_siso.cpp#L21) waits one second and keeps a state of led at that time.
</div></details>
<details><summary>End to use pigpiod</summary><div>

[Line 24 in on_off_siso.cpp](../src/pigpio_library_test/src/on_off_siso.cpp#L24) shows the procedure to end to use pigpiod.
</div></details>

## Usage with callback function

* source file
  * \<repo. directory\>/src/pigpio_library_test/src/[on_off_siso_with_callback.cpp](../src/pigpio_library_test/src/on_off_siso_with_callback.cpp)

### build and execute
Prepare the source file by DL or by creating yourself.

```shell
$ g++ -Wall -pthread -o on_off_siso_with_callback on_off_siso_with_callback.cpp -lpigpiod_if2
$ ./on_off_siso_with_callback
```

If pushing a switch, a led will turn off.
If releasing a switch, a led will turn on.

### Explanation
