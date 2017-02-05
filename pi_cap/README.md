Pi Cap
======

The Pi Cap by Bare Conductive is a capacitance-sensing board that plugs in directly to the Raspberry Pi header, and includes out-of-the-box software examples for Node.js, Python and C++.


Installation
------------

The full, explicit tutorial is available [here](https://www.bareconductive.com/make/setting-up-pi-cap-raspberry-pi/).  If you can already SSH into the Pi, the tutorial boils down to the following steps executed from the command line:

    sudo apt-get update
    sudo apt-get install picap
    picap-setup

The picap-setup will prompt for a restart.  Do this.  Following the restart, from the command line, execute the following to validate that the Pi Cap is correctly installed:

    picap-intro


Notes
-----

- don't install Node.js during picap-setup, better to set it up beforehand
- the picap programs might not recognise the installed Node.js version, but the examples will run nonetheless
- polyphony of sounds is __not__ possible with Node.js, only with C++ and Python
