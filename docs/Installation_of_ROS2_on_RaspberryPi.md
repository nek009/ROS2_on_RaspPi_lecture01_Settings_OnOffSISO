[Back to Top page](../README.md)

# Overview
Basically refer to official pages.

# Installation
Install ROS2 following the instructions of official page.

* [Installation guide of Official page for foxy](https://docs.ros.org/en/foxy/Installation/Ubuntu-Install-Debians.html)
* [Installation guide of Official page for galactic](https://docs.ros.org/en/galactic/Installation/Ubuntu-Install-Debians.html)

## Special notes
### ROS2 packages

In general, several distributions can be installed, ex. foxy or galactic.
The better way is to install all distributions, because we can select a distribution at any time easily.<br>
And the following packages of each distribution can be installed.
The better way is to install recommended package.

* ros-\<distro\>-desktop
  * Recommended
* ros-\<distro\>-base
  * Bare Bones

### Installation of others

```shell
$ sudo sh -c 'echo "deb [arch=$(dpkg --print-architecture)] http://repo.ros2.org/ubuntu/main `lsb_release -cs` main" > /etc/apt/sources.list.d/ros2-latest.list'
$ curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
$ sudo apt update
$ sudo apt install python3-colcon-common-extensions
$ sudo apt install python3-pip
$ sudo apt install ~nros-<distro>-rqt*
```

Information of python3-colcon-common-extensions is [here](https://colcon.readthedocs.io/en/released/user/installation.html).<br>
`~nros-<distro>-rqt*` is useful packages but is not essential.

# Tips
## Tutorial after the installation

The most important thing is to read and do tutorial in official page.
Almost all basic information is in it.

* [tutorial in official page for foxy](https://docs.ros.org/en/foxy/Tutorials.html)
