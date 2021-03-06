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

[Line 7-11 in on_off_siso.cpp](../src/pigpio_library_test/src/on_off_siso.cpp#L7-L10) shows an initialization which connect to target Rasp.Pi and return identifier. The arguments which are NULL means it means to connect localhost via 8888 port.
</div></details>
<details><summary>Set GPIO modes</summary><div>

[Line 13-16 in on_off_siso.cpp](../src/pigpio_library_test/src/on_off_siso.cpp#L13-L16) shows the settings of gpio mode.
[Line 14 in on_off_siso.cpp](../src/pigpio_library_test/src/on_off_siso.cpp#L14) shows GPIO21 which is connected to a led is set as OUTPUT, and [Line 16 in on_off_siso.cpp](../src/pigpio_library_test/src/on_off_siso.cpp#L16) shows GPIO26 which is connected to a switch is set as INPUT.
</div></details>
<details><summary>Use GPIOs</summary><div>

[Line 18-22 in on_off_siso.cpp](../src/pigpio_library_test/src/on_off_siso.cpp#L18-L22) controls a led by a state of a switch.<br>
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

In the Simple usage, a loop and a sleep function are used to check a state of a switch, a state of GPIO26.
If sleeping 10 seconds in a loop, delay to sense a switch be pushed is about 10 sec. at most.<br>
In this section, a way to sense a state of a GPIO by callback function to reduce this delay is introduced.
This way doesn't process a command line by line.
It observes a state of a GPIO in the background and call a callback function dynamically when a state of a GPIO changes.
The flow of the way is 1) to make a callback function which codes a procedure when a state of a GPIO changes, and 2) to register it, that means to connect it with a GPIO which must be observed and with a way to change which a signal is rising, falling or both.<br>
[Line 5 in on_off_siso_with_callback.cpp](../src/pigpio_library_test/src/on_off_siso_with_callback.cpp#L5) declares a callback function and [Line 29-32 in on_off_siso_with_callback.cpp](../src/pigpio_library_test/src/on_off_siso_with_callback.cpp#L29-L32) are implementation of it.
And [Line 20 in on_off_siso_with_callback.cpp](../src/pigpio_library_test/src/on_off_siso_with_callback.cpp#L20) registers a callback function.
By this line, GPIO26 will be observed and a callback function named callback_push_switch will be executed when GPIO26 changes.
[Line 23 in on_off_siso_with_callback.cpp](../src/pigpio_library_test/src/on_off_siso_with_callback.cpp#L20) makes a procedure sleep 10 sec. to observe GPIO26 and execute callback_push_switch when it changes.
