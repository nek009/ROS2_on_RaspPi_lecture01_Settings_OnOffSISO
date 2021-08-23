[Back to Top page](../README.md)

# Overview
I show a way to add users, it is not a special way for Rasp. Pi, is a usual way of Linux.
To avoid the need of root privilege or the use of sudo command, pigipo daemon is used in this repository and general users can control hardware through pigpio daemon.

# Addition of users
The following is an example which user name is `nek`.

```shell
$ sudo adduser nek
New password:  # <- Set a password for nek.
Retype new password: # <-Retype the password to check it.
... # There are some messages
  Full Name []: # It is no problem to be set empty values at following sections.
  Room Number []:
  ...
```
