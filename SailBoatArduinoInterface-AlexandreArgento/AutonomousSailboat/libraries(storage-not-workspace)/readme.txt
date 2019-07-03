These librairies should be, when adding them for the first time, copied to the "/librairies" folder in one's personnal Arduino workspace.
Therefore, any modification should be done in the Arduino librairies folder and copied in this folder to share or move the project content.

Personnal work, starting from Ulysse Vautier's work:
=> IMU (adaptation to an other sensor model)
=> Controller (simplification)
=> Sailboat (simplification)

Actual state:
=> publication of IMU heading through the C++ Class structure successfull:
    - Arduino librairies completion
    - "AutonomousSailboat.ino" file uploading in the Arduino board
    - (terminal1) roscore
    - (terminal2) rosrun rosserial_python serial_node.py _baud:=115200 _port:=/dev/ttyACM0
    - (terminal3) rqt (message visualization)
