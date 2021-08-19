[Back to Top page](../README.md)

# Overview

Raspbian OS is known as standard OS for Raspberry Pi, which is based on Debian Buster.
But it is hard to install ROS2 on Debian, and is easy to do on Ubuntu.<br>
Here, I introduce the installation of Ubuntu to Raspberry Pi briefly.

## For use under variable network environment

The situation of the use of Rasp. Pi is variety, where is designed with care like corp. or lab., or is opposite like outdoor.
That means it is unknown whether DNS, DHCP or like other systems can be used or not.
By considering a use under unknown network environment, a basic approach to set up LAN will be shown.<br>
If can know a network environment before settings, of course proper settings according to your network must be done.


### Wireless LAN
In this page, I only assume IP are assigned by DHCP server automatically.
If not, I consider that there is no useful internet service.<br>

* Settings
  * Assign IP address by DHCP server.
  * Resolve name by avahi-daemon considering a situation which there is no DNS server.
    * If DNS server can be used, of course use it.

### Wired LAN

I assume the following case for wired lan.

1. Disconnected LAN cable.
1. Connected to network without DHCP server.
1. Connected to network with DHCP server.
1. Connected to network where fixed IP address must be set up.

Here, I target situations from 1st to 3rd.
If a Rasp. Pi will be carried somewhere, a situation will changes, ex from 3rd to 2nd situation.
If possible, a Rasp. Pi can be used under such a situation.<br>
For 4-th, you must set up properly by usual procedure.

* settings
  * Assign private IP address(169.254.0.0/16) by using link-local.
  * Resolve name by avahi-daemon considering a situation which there is no DNS server.
    * If DNS server can be used, of course use it.

# Installation and setting of Ubuntu Server
## Install on microSD card

I recommend to install by referring [this page](https://ubuntu.com/download/raspberry-pi), especially by clicking [server](https://ubuntu.com/tutorials/how-to-install-ubuntu-on-your-raspberry-pi#1-overview) in "Follow our desktop or server tutorials."<br>
Following is a point to notice when installing by using Raspberry Pi Imager.

* CHOOSE OS
  * Select "Other general purpose OS"
    * Select "Ubuntu Server 20.04.2 LTS(RPi 3/4/400) 64bit"

## Boot up Ubuntu Server
After inserting microSD on Rasp. Pi and connecting HDMI, Keyboard and Mouse to it, booting up Rasp. Pi by inserting power cable.
Installation and basic setting of Ubuntu Server will be started, so wait a couple of minutes.<br>
First login can be done by ID: ubuntu and password: ubuntu.
A system will request to change a password, so set new password.

## Set up network

* target file
  * /etc/netplan/[50-cloud-init.yaml](../yaml/50-cloud-init.yaml)
* a brief explanation
  * [renderer: networkd](../yaml/50-cloud-init.yaml#L3) is used.
    * netplan can use networkd and NetworkManager as renderer. But link-local option will be inefficient if renderer is NetworkManager and dhcp4 option is true(see [link-local option in netplan reference](https://netplan.io/reference/#common-properties-for-all-device-types).) So if use link-local option, renderer must be networkd.

after setting up, enable it by following command.

```shell
$ sudo netplan apply
```

## Install avahi-daemon, and misc

```shell
$ sudo apt install avahi-daemon ssh git
$ sudo systemctl enable avahi-daemon
$ sudo systemctl start avahi-daemon
```

Now you can connect Rasp. Pi by a name of /etc/hostname + ".local".
First check Rasp. Pi name by following command.

```shell
$ cat /etc/hostname
raspberry pi
```

In this example, hostname is `raspberrypi`.
So you can connect this Rasp. Pi by following command.

```shell
$ ssh ubuntu@raspberrypi.local
```

Here, `.`(period, dot) cannot be used as a part of hostname, ex. `rapberry.pi` cannot be used so cannot connect it by `raspberry.pi.local`.

### Set hostname as you want
If hostname changes, use following commands.

For a change of hostname temporary.

```shell
$ hostname <new hostname>
```

For a change of hostname permanently, it means a name keeps changing after reboot.

```shell
$ sudo hostnamectl set-hostname <new hostname>
```

If back to an original hostname after reboot, a cloud-init module prevent a hostname from changing.
In this case, modify a setting to change a hostname to new name as follows.

* target file
  * /etc/cloud/cloud.cfg
* edit and modify as follows
  * from
    * preserve_hostname: false
  * to
    * preserve_hostname: true

## Set ntp and time-zone

1. Find ntp server, ex by using google search.
1. Modify /etc/systemd/timesyncd.conf
  * Especially set `NTP=`, `FallbackNTP=` is additional option.
1. Confirm time zone where you live by following command
  * `$ timedatectl list-timezones`

And set up net and time-zone by following commands.

```shell
$ timedatectl set-ntp true # set up ntp based on timesyncd.conf
$ sudo systemctl enable systemd-timesyncd.service
$ sudo timedatectl set-timezone <your time zone>
$ sudo systemctl restart systemd-timesyncd.service
```

## Update a system

```shell
$ sudo apt update && sudo apt upgrade -y
```
