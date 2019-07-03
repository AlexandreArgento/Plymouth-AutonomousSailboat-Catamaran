# Autonomous Sailboat

### Prerequisites

- Raspberry Pi 3 with:
  - Arduino IDE : https://www.arduino.cc/en/Main/Software
  - ROS melodic : 
- Arduino Mega 2560

### Building and Uploading

First copy the folder `libraries` and put it in `~/Documents/Arduino/` on your PC.

You should now be able to launch the *.ino* sketch, compile and upload to the arduino using the [Arduino IDE](https://www.arduino.cc/en/Guide/ArduinoMega2560).
This will launch the Arduino into Stanby Mode, just receiving data from the sensors and sending them to the PC. It will put the rudder at angle 0 and the sail fully opened. After that it won't and shouldn't move the rudder or the sail.

## Authors

* **Ulysse VAUTIER** - *Initial work* - [UlysseVautier](https://ulyssevautier.github.io/)
* **Alexandre ARGENTO**

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments
This project uses libraries from :
* [EnableInterrupt](https://github.com/GreyGnome/EnableInterrupt)
