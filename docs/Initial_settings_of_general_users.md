[Back to Top page](../README.md)

# Overview
The following shows a settings to use ROS2, and example is a case that ROS2 top directory is `~/ros2_install`.
Change it as you want.

# Settings in .bashrc
Here, \<distro\> is a name of distribution, like `foxy` or `galactic`.

## Simple version
Set up .bashrc by executing following commands.
If only you are ROS2 user, it is ok to set `ROS_DOMAIN_ID` `0` or `1`.
If you use ROS2 with others, control its number.
Detailed information is [here](https://docs.ros.org/en/foxy/Tutorials/Configuring-ROS2-Environment.html#the-ros-domain-id-variable).

```shell
$ echo "source /usr/share/colcon_cd/function/colcon_cd.sh" >> ~/.bashrc
$ echo "export _colcon_cd_root=~/ros2_install" >> ~/.bashrc
$ echo "source /opt/ros/<distro>/setup.bash" >> ~/.bashrc
$ echo "export ROS_DOMAIN_ID=<unique number for you>" >> ~/.bashrc
```

## Setting by editing .bashrc
Set up .bashrc by editing .bashrc, ex by using vim or nano.
Following is a excerpt of related parts from .bashrc.

```bashrc

if [ -f /usr/share/colcon_cd/function/colcon_cd.sh ]; then
    source /usr/share/colcon_cd/function/colcon_cd.sh
    export _colcon_cd_root=~/ros2_install
fi

# comment disuse DISTRO out
DISTRO="foxy"
# DISTRO="galactic"
if [ -f /opt/ros/$DISTRO/setup.bash ]; then
    echo "ROS2 $DISTRO is activated."
    source /opt/ros/$DISTRO/setup.bash
fi

export ROS_DOMAIN_ID=<unique number for you>
```
