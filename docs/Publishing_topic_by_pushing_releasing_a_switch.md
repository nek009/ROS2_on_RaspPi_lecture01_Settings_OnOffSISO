[Back to Top page](../README.md)

# Overview

Here, ROS2 node will be made.
It publishes messages when a switch pushes or releases, that means when a state of GPIO 26 changes.
At first, a message structure will be decided and a ROS2 package for it will be created.
And a ROS2 package about publisher will be made.

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
$ ros2 pkg create gpio_messages --build-type ament_cmake
$ mkdir gpio_messages/msg
```

### Creation of message file
Create a following file for a message.

* target file
  * gpio_messages/msg/[GpioState.msg](../src/gpio_messages/msg/GpioState.msg)

### Modified package.xml and CMakeLists.txt

* target file
  * gpio_messages/[package.xml](../src/gpio_messages/package.xml)
  * gpio_messages/[CMakeLists.txt](../src/gpio_messages/CMakeLists.txt)

## Build & confirmation

```shell
$ colcon_cd
$ colcon build --symlink-install --packages-up-to gpio_messages
$ . install/local_setup.bash
$ ros2 interface list # confirm that difined message is shown
$ ros2 interface show gpio_messages/msg/GpioState
```

# Publisher node
By using the above message, publisher node publishes a state of a GPIO.

* topic name
  * gpio_state

## ROS2 coding
### Preparation of ROS2 package for node

```shell
$ colcon_cd
$ ros2 pkg create gpio_state_recognition_nodes --build-type ament_cmake --dependencies rclcpp gpio_messages
```

### Coding

* target file
  * gpio_state_recognition_nodes/src/[pub_gpio_state_node.hpp](../src/gpio_state_recognition_nodes/src/pub_gpio_state_node.hpp)
  * gpio_state_recognition_nodes/src/[pub_gpio_state_node.cpp](../src/gpio_state_recognition_nodes/src/pub_gpio_state_node.cpp)

### Modified CMakeLists.txt

* target file
  * gpio_state_recognition_nodes/[CMakeLists.txt](../src/gpio_state_recognition_nodes/CMakeLists.txt)
    * Add [below of # For target, lines 24-49](../src/gpio_state_recognition_nodes/CMakeLists.txt#L24-L49)

## Build & confirmation
### Build

```shell
$ colcon_cd
$ colcon build --symlink-install --packages-up-to gpio_state_recognition_nodes
$ . install/local_setup.bash
```

### Confirmation
Open two terminal, named term1 and term2.

In term1, execute the node to observe a state of switch, a state of GPIO26.

```shell
$ . install/local_setup.bash
$ ros2 run gpio_state_recognition_nodes pub_gpio_state_target
```

In term2, show topics by ros2 command and confirm that it publishes messages according to a state of a switch.

```shell
$ . install/local_setup.bash
$ ros2 topic echo /pub_gpio_state
```

# Publisher node as components
The above node is made as target.
It is executable and can be used, but is not extendability and not robust.
A better way is to make a node as a components.
It can be used to make a executable node(target), not only by only itself, but by combining plural nodes.
In this case, message passing between nodes doesn't use network, is realzied by zero-copy.
In addition to this, components can be executed by using ROS2 command `ros2 component standalone` or `ros2 run rclcpp_components component_container` and `ros2 component load`.<br>
Here, how to create a component node in same package based on the above node.

* topic name
  * gpio_state

## ROS2 coding
### Preparation of visibility.h
It is boring to create visibility.h from scratch, so it make by DL [visibility.h in official github](https://github.com/ros2/examples/blob/master/rclcpp/composition/minimal_composition/include/minimal_composition/visibility.h) and customizing it.<br>
A point where custome it is the string `MINIMAL_COMPOSITION`.
Here I change it to `ROS2RASP_LECTURE_PUBGPIOSTATECOMPONENTNODE`, which is made by combining `namespace` and `class name` with `_`.

```shell
$ cd gpio_state_recognition_nodes/include/gpio_state_recognition_nodes
$ curl https://raw.githubusercontent.com/ros2/examples/master/rclcpp/composition/minimal_composition/include/minimal_composition/visibility.h > visibility.h
$ sed -i s/MINIMAL_COMPOSITION/ROS2RASP_LECTURE_PUBGPIOSTATECOMPONENTNODE/g visibility.h
```

### Coding

* target file
  * gpio_state_recognition_nodes/include/gpio_state_recognition_nodes/[pub_gpio_state_component_node.hpp](../src/gpio_state_recognition_nodes/include/gpio_state_recognition_nodes/pub_gpio_state_component_node.hpp)
  * gpio_state_recognition_nodes/src/[pub_gpio_state__component_node.cpp](../src/gpio_state_recognition_nodes/src/pub_gpio_state_component_node.cpp)

### Modified package.xml and CMakeLists.txt

* target file
  * gpio_state_recognition_nodes/[package.xml](../src/gpio_state_recognition_nodes/package.xml)
    * Add \<depend\>rclcpp_components\</depend\>
  * gpio_state_recognition_nodes/[CMakeLists.txt](../src/gpio_state_recognition_nodes/CMakeLists.txt)
    * Add find_package(rclcpp_components REQUIRED)
    * Add [below of # For component, lines 50-100](../src/gpio_state_recognition_nodes/CMakeLists.txt#L50-L100)

## Build & confirmation
### Build

```shell
$ colcon_cd
$ colcon build --symlink-install --packages-up-to gpio_state_recognition_nodes
$ . install/local_setup.bash
```

### Confirmation
Open two terminal, named term1 and term2.

In term1, execute the node to observe a state of switch, a state of GPIO26.

```shell
$ . install/local_setup.bash
$ ros2 component standalone gpio_state_recognition_nodes ros2rasp_lecture::PubGpioStateComponentNode
```

In term2, show topics by ros2 command and confirm that it publishes messages according to a state of a switch.

```shell
$ . install/local_setup.bash
$ ros2 topic echo /pub_gpio_state
```

## For use of component in target
The bellow is a way to use a component(shared library correctly).

### Preparation of target which use component

```shell
$ colcon_cd
$ ros2 pkg create gpio_state_recognition_target  --build-type ament_cmake --dependencies rclcpp gpio_state_recognition_nodes
```

### Coding

* target file
  * gpio_state_recognition_target/src/[pub_gpio_state_recognition_target.cpp](../src/gpio_state_recognition_target/src/pub_gpio_state_recognition_target.cpp)

### Modified package.xml and CMakeLists.txt

* target file
  * gpio_state_recognition_target/[CMakeLists.txt](../src/gpio_state_recognition_nodes/CMakeLists.txt)

### Build

```shell
$ colcon_cd
$ colcon build --symlink-install --packages-up-to gpio_state_recognition_target
$ . install/local_setup.bash
```

### Confirmation
Open two terminal, named term1 and term2.

In term1, execute the node to observe a state of switch, a state of GPIO26.

```shell
$ . install/local_setup.bash
$ ros2 run gpio_state_recognition_target pub_gpio_state_recognition_target
```

In term2, show topics by ros2 command and confirm that it publishes messages according to a state of a switch.

```shell
$ . install/local_setup.bash
$ ros2 topic echo /pub_gpio_state
```
