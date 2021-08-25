[Back to Top page](../README.md)

# Overview
Here, try to execute publisher node and subscriber node on different Rasp. Pi.
As shown in figure, a led shall be connected to pi1 and a switch shall be connected to pi2.
If pi1 and pi2 are connected with a network, it is easy to execuute nodes on different pi and to control a led by a swith.
Just it is ok to execute subscriber on pi1 and to execute publisher on pi2.
I show how to use component manager as one of a way.
To do so, adding namespace to distinguish component managers on Pi's is needed.
Detailed information to add namespace by option is [here](https://docs.ros.org/en/foxy/Guides/Node-arguments.html).<br>

![Target circuit](figs/led_switch_two_pi.png)

# Way to execute nodes using component managers
Open a terminal on each Rasp. Pi, on pi1 and pi2.
In a terminal on pi1, component manager is added namespace `/pi1` and executed as follows.

```shell
$ ros2 run rclcpp_components component_container --ros-args -r __ns:=/pi1
```

A command on a terminal on pi2 is as follows.

```shell
$ ros2 run rclcpp_components component_container --ros-args -r __ns:=/pi2
```

Open a new terminal on pi1 and execute following command.

```shell
$ . install/local_setup.bash
$ ros2 component load /pi2/ComponentManager gpio_state_recognition_node ros2rasp_lecture::PubGpioStateComponentNode
$ ros2 component load /pi1/ComponentManager gpio_led_control_node ros2rasp_lecture::GpioLedControlComponentNode
```

Comfirm that a led turns on or off when a switch is pushed or released.
