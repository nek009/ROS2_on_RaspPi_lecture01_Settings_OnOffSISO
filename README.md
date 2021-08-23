[for Japanese:日本語](docs/README_JP.md)

# Overview

This is not repository for program sources, is lecture series to use ROS2 on Raspberry Pi or similar Single Board Computer installed Ubuntu.

## Final goal
Final goal of learning in this repository is to learn a way to treat hard wares by ROS2.
Target circuit is shown in figure below.
Rasp. Pi named `pi1` controls a led and Rasp. Pi named `pi2` senses a state of a switch.
Both Rasp. Pi are connected each by network.
The examination is to control a led by a state of a switch on ROS2 system.<br>
If you have only one Rasp. Pi, it is no problem.
Please replace `pi2` with `pi1` read this repository with only one Rasp. Pi.

<img src="docs/figs/led_switch.png" width="500">

# Table of Contents
## For administrator

1. [Installation of Ubuntu Server on Raspberry Pi](docs/Installation_of_UbuntuServer_on_RaspberryPi.md)
1. [Installation of ROS2 on Raspberry Pi](docs/Installation_of_ROS2_on_RaspberryPi.md)
1. [Installation of pigpio library](docs/Installation_of_pigpio_library.md)
1. [Addition of general users](docs/Addition_of_general_users.md)

## For general user

1. [Initial settings](docs/Initial_settings_of_general_users.md)
1. [Usage of pigpiod in C++](docs/Usage_of_pigpiod_in_cpp.md)
