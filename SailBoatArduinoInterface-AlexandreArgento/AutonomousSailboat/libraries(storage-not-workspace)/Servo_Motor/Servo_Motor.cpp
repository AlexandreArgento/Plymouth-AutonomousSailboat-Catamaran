#include <Servo_Motor.h>
#include <Wire.h>

void Servo_Motor::init(ros::NodeHandle* n)
{
    // 0x40 is default address
    motor = Adafruit_PWMServoDriver(&Wire, 0x40);
    motor.begin();
    motor.setPWMFreq(500);
	delay(10);
    
	// Set the rudder at the Neutral position
	motor.setPWM(pin, 0, pwmNeutral);
	
	ActuatorROS::init(n);
}

void Servo_Motor::applyCommand(double command)
{
    // Safety filter
	unsigned int commandExact = pwmNeutral;
    if(command > anglemax)
        command = anglemax;
    if(command < anglemin)
        command = anglemin;
    
	// Generates the exact command:
	commandExact = mapf(command, anglemin, anglemax, pwmMin, pwmMax);
//	Logger::Log(0, F("MotorCommandExact"), String(commandExact));

	// Set the servo at the wanted position:
	motor.setPWM(pin, 0, commandExact);
}

void Servo_Motor::RCCommand(uint16_t command)
{
    Serial.println("motor:");
    Serial.println(command);
	// Set the servo at the wanted position:
	//motor.setPWM(pin, 0, command);
    motor.setPWM(0, 0, command);
}

void Servo_Motor::communicateData()
{
    /*  /!\ ???motor.read()??? /!\
	msg.data = mapf(motor.read(), pwmMin, pwmMax, anglemin, anglemax);
	pub.publish(&msg);
    */
}
