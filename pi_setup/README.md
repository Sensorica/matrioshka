Official Raspberry Pi Setup Procedure for Matrioshka
====================================================

This is the official procedure to setup a Raspberry Pi from scratch.  We use Raspbian Jessie Lite as the operating system.


Installing Jessie Lite on SD Card
---------------------------------

First we'll prepare a micro SD card of at least 4GB (8GB+ strongly recommended) with the Raspbian Jessie Lite operating system.
 
Download the latest Raspbian Jessie Lite image from [www.raspberrypi.org/downloads/raspbian/](https://www.raspberrypi.org/downloads/raspbian/).

Follow the instructions ([Linux](https://www.raspberrypi.org/documentation/installation/installing-images/linux.md), [Mac](https://www.raspberrypi.org/documentation/installation/installing-images/mac.md) or [Windows](https://www.raspberrypi.org/documentation/installation/installing-images/windows.md)) to transfer the image to the SD card.


Configuration of basic settings on SD Card
------------------------------------------

Mount the SD card on your PC (if it is not already).

### SSH

From the command line, browse to the root of the /boot folder of the SD card and run:

    sudo touch ./ssh

This will enable ssh on boot (it is disabled by default).


### Ethernet static fallback

From the command line, browse to the root of the / folder of the SD card and edit the dhcpcd.conf file.  If you're a fan of the vi text editor, run:

    sudo vi /etc/dhcpcd.conf

Paste the following lines at the bottom of the file and save:

    # Define static profile
    profile static_eth0
    static ip_address=10.0.50.100/24
    static routers=10.0.50.1
    static domain_name_servers=10.0.50.1

    # Fallback to static profile on eth0
    interface eth0
    fallback static_eth0

This will configure the Pi to use IP address __10.0.50.100__ when it is connected to Ethernet without DHCP.  This provides a sure-fire means of connecting to the Pi from a PC to make changes/updates.

The SD card is ready!


First connection
----------------

Complete the following in order:
- Insert the SD card in the Pi.
- Connect the Pi to your PC via a network cable.
- Apply power to the Pi.
- Configure your PC's Ethernet adapter to use an address in the same subnet as the Pi (ex: 10.0.50.101).

From the command line, ssh into the Pi as follows:

    ssh pi@10.0.50.100

The default password will be _raspberry_.

The connection to the Pi is now established.


raspi-config
------------

Configure the Pi by running the following from the command line:

    sudo raspi-config

This should open a text-based menu.

### Change User Password

Select the option to change the user password.  Choose a password that cannot be easily guessed, but is nonetheless straightforward to enter from the command line next time you'll ssh in.

### Change Hostname

Select _Advanced Options_, then _Hostname_.  Change the hostname to __matrioshka-pi__.

Select _Finish_, then select _Yes_ when asked to reboot.


Connect to WiFi
---------------

SSH back into the Pi once the reboot is complete (using the new password).  Open the wpa_supplicant.conf file for editing:

    sudo vi /etc/wpa_supplicant/wpa_supplicant.conf 

For each WiFi network that the Pi will connect to, add the following to the bottom of the file:

    network={
      ssid="ENTER_SSID_HERE"
      psk="ENTER_PASSWORD_HERE"
      key_mgmt=WPA-PSK
    }

Ensure that the list includes an Internet-connected WiFi network in range.  Save the file and exit.  If your PC and the Pi are now configured to connect to the same WiFi network, the Ethernet link between them will no longer be required.  Enter the following from the command line to shut down the Pi:

    sudo shutdown now

If desired, disconnect the network cable from the Pi.  Cycle power.  SSH back into the Pi (which will have a different IP address if you're connecting over WiFi!).












