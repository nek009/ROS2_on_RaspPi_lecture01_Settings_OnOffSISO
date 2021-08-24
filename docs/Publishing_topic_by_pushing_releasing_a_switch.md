[Back to Top page](../README.md)

# Overview

Here, ROS2 node will be made.
It publishes messages when a switch pushes or releases, that means when a state of GPIO 26 changes.
At first, a message structure will be decided and a ROS2 package for it will be created.
And a ROS2 package about publisher will be made.

# Message package
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
$ ros2 pkg create gpio_messages --build-type ament_cmake
$ mkdir gpio_messages/msg
```

### Creation of message file
Create a following file for a message.

* target file
  * gpio_messages/msg/GpioState.msg

Contents is as follow.

```text
uint16 gpio
bool level
```

### Modified package.xml and CMakeLists.txt
Followings are excerpts of related parts from them.

**package.xml**
```xml
<package format="3">
  <build_depend>rosidl_default_generators</build_depend>
  <exec_depend>rosidl_default_runtime</exec_depend>
  <member_of_group>rosidl_interface_packages</member_of_group>
```

**CMakeLists.txt**
```text
find_package(rosidl_default_generators REQUIRED)

set(msg_files
  "msg/GpioState.msg"
)
rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
)
ament_export_dependencies(rosidl_default_runtime)
```

## Build & confirmation

```shell
$ colcon_cd
$ colcon build --symlink-install --packages-up-to gpio_messages
$ . install/local_setup.bash
$ ros2 interface list # confirm that difined message is shown
$ ros2 interface show gpio_messages/msg/GpioState
```
