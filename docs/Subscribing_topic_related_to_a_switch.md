[Back to Top page](../README.md)

# Overview

Here, ROS2 subscriber node which subscribes a topic message of a state of a switch will be made.
And this node controls a led with a message, it turns on led when a switch pushes, and the opposite.
The topic message created in [here](Creation_of_a_topic_message_for_a_state_of_a_switch.md) is used.

# Subscriber node
Target node subscribes the above message through topic named below.

* topic name
  * pub_gpio_state

## ROS2 coding as component
Here, a node is created as library by the option `--library-name`, so some parts are prepared, ex. visibility_control.h is prepared.

### Preparation of ROS2 package for node

```shell
$ colcon_cd
$ ros2 pkg create gpio_led_control_node --build-type ament_cmake --dependencies rclcpp rclcpp_components gpio_msgs --library-name gpio_led_control_component_node
```

Following files are created.

- gpio_led_control_node/
  - include/gpio_led_control_node/visibility_control.h
  - include/gpio_led_control_node/gpio_led_control_component_node.hpp
  - src/gpio_led_control_component_node.cpp
  - CMakeLists.txt
  - package.xml

And some names are desiced as follows.

- package name
  - gpio_led_control_node
- namespace
  - gpio_led_control_node
- macros for all symbols you need to export, used in header files
  - GPIO_LED_CONTROL_NODE_PUBLIC
- library name
  - gpio_led_control_component_node
- class name
  - GpioLedControlComponentNode

### Coding

* target file
  * gpio_led_control_node/include/gpio_led_control_node/[gpio_led_control_component_node.hpp](../src/gpio_led_control_node/include/gpio_led_control_node/gpio_led_control_component_node.hpp)
  * gpio_led_control_node/src/[gpio_led_control_component_node.cpp](../src/gpio_led_control_node/src/gpio_led_control_component_node.cpp)

### Modified  CMakeLists.txt

* target file
  * gpio_led_control_node/[CMakeLists.txt](../src/gpio_led_control_node/CMakeLists.txt)

## Build & confirmation
### Build

```shell
$ colcon_cd
$ colcon build --symlink-install --packages-up-to gpio_led_control_node
$ . install/local_setup.bash
```

### Confirmation1
Open two terminal, named term1 and term2.
In term1, execute publisher related to a switch.

```shell
$ . install/local_setup.bash
$ ros2 component standalone gpio_state_recognition_node ros2rasp_lecture::PubGpioStateComponentNode
```

In term2, execute this subscriber

```shell
$ . install/local_setup.bash
$ ros2 component standalone gpio_led_control_node ros2rasp_lecture::GpioLedControlComponentNode
```

Comfirm that a led turns on or off when a switch is pushed or released.

### Confirmation2
Other way to execute nodes is to use `ros2 component load` command.
Detailed information is [here](PubGpioStateComponentNode).<br>
Open two terminal, named term1 and term2.
In term1, execute component manager to treat plural nodes, publisher related to a switch and this subscriber.

```shell
$ . install/local_setup.bash
$ ros2 run rclcpp_components component_container
```

In term2, load nodes to component manager.

```shell
$ . install/local_setup.bash
$ ros2 component load /ComponentManager gpio_state_recognition_node ros2rasp_lecture::PubGpioStateComponentNode
$ ros2 component load /ComponentManager gpio_led_control_node ros2rasp_lecture::GpioLedControlComponentNode
```

Comfirm that a led turns on or off when a switch is pushed or released.
