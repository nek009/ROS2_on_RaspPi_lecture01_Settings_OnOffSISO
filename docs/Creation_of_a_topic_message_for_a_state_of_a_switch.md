[Back to Top page](../README.md)

# Overview

ROS2 publisher node publish topic messages.
Here, a message of a state of a switch, which means a message of a state of GPIO26, is created.

# Message
## Definition of structure

GPIO26 was connected to a switch, but it will changes depending on a way to use.
So following information is used as a published message.

* unsigned GPIO number
  * A GPIO number which changes a state.
* bool level
  * A GPIO level which takes HIGH(true) or LOW(false).

## ROS2 coding
### Preparation of ROS2 package for message

```shell
$ colcon_cd
$ ros2 pkg create gpio_msgs --build-type ament_cmake
$ mkdir gpio_msgs/msg
```

### Creation of message file
Create a following file for a message.

* target file
  * gpio_msgs/msg/[GpioState.msg](../src/gpio_msgs/msg/GpioState.msg)

### Modified package.xml and CMakeLists.txt

* target file
  * gpio_msgs/[package.xml](../src/gpio_msgs/package.xml)
  * gpio_msgs/[CMakeLists.txt](../src/gpio_msgs/CMakeLists.txt)

## Build & confirmation

```shell
$ colcon_cd
$ colcon build --symlink-install --packages-up-to gpio_msgs
$ . install/local_setup.bash
$ ros2 interface list # confirm that difined message is shown
$ ros2 interface show gpio_msgs/msg/GpioState
```
