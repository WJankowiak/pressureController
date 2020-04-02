# pressureController

This project presents simple application allowing Connection to the device - PressureController.
Project is separated into two directories representing client and "server" side of connection
PressureController is all the "server" side, with model of device and TCP listener implemented based on simple abstract interface.
It also shows possibility of extending connections to other protocols - such as UDP - implementing a mock of deviceConnector factory.

Client is the desktop App, allowing to get and set pressure of the device and get it's version number.

Connection was made using SFML library (reason of choice - I had it lying on hard drive) and to spare user of downloading and linking to project, each folder contains package called "Executable"
Executable (as name suggests) is ready to use, and (should) work after unpacking.

