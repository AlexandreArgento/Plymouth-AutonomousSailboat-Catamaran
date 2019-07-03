# Autonomous Sailboat

### Prerequisites

- Raspberry Pi 3 with:
  - Arduino IDE : https://www.arduino.cc/en/Main/Software
  - ROS melodic : 
- Arduino Mega 2560

### Personnal work

Starting from Ulysse Vautier's work:
- IMU : adaptation to an other sensor model
- Controller : simplification
- Sailboat : simplification

### Current state

Publication of IMU heading through a C++ class structure successful.
Steps to follow:
- Arduino librairies completion in the `/libraries` folder in one's personal Arduino workspace
- `AutonomousSailboat.ino` file uploading in the Arduino board
- (terminal1) roscore
- (terminal2) rosrun rosserial_python serial_node.py _baud:=115200 _port:=/dev/ttyACM0
- (terminal3) rqt (message visualization)

## Authors

* **Ulysse VAUTIER** - *Initial work* - [UlysseVautier](https://ulyssevautier.github.io/)
* **Alexandre ARGENTO**

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments
This project uses libraries from :
* [EnableInterrupt](https://github.com/GreyGnome/EnableInterrupt)
