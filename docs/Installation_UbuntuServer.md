[Back to Top page](../README.md)

# Overview

Raspbian OS is known as standard OS for Raspberry Pi, which is based on Debian Buster.
But it is hard to install ROS2 on Debian, and is easy to do on Ubuntu.<br>
Here, we introduce the installation of Ubuntu to Raspberry Pi briefly.

## For use under variable network environment

The situation of the use of Rasp. Pi is variety, where is designed with care like corp. or lab., or is opposite like outdoor.
That means it is unknown whether DNS, DHCP or like other systems can be used or not.
By considering a use under unknown network environment, a basic approach to set up LAN will be shown.<br>
If can know a network environment before settings, of course proper settings according to your network must be done.


### Wireless LAN
In this page, we only assume IP are assigned by DHCP server automatically.
If not, we consider that there is no useful internet service.<br>

* Settings
  * Assign IP address by DHCP server.
  * Resolve name by avahi-daemon considering a situation which there is no DNS server.
    * If DNS server can be used, of course use it.
