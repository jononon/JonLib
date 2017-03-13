#include "PID.h"
#include "Drivebase.h"
//#include "../MarkIIIPragma.c"

#pragma systemFile

pid gyroscope;

int maxSpeedSwing = 127;

void resetGyro() {
	SensorValue[gyro] = 0;
}

void resetGyroscope () {
	resetGyro();
}

void setTarget ( int target = 0 ) {
	gyroscope.target = target;
}


task orient () {
	int speed;
	string out;
	int lowestMovePower = 21;


	gyroscope.kP = 0.2;
	gyroscope.kI = 0.0025;
	gyroscope.kD = 0.05;//3;
	do {
		//P
		gyroscope.error = gyroscope.target - SensorValue[gyro];

		//I
		if (abs(gyroscope.error)>100)
			gyroscope.integral = 0;
		else
			gyroscope.integral += gyroscope.error;

		//D
		gyroscope.derivative = gyroscope.error - gyroscope.lastError;

		speed = gyroscope.kP*gyroscope.error + gyroscope.kI*gyroscope.integral + gyroscope.kD*gyroscope.derivative;

		//speed = gyroscope.error==0?0:speed;
		//speed = abs(speed)>30?speed/abs(speed)*30:speed; //fancy way of high deadbands
		//speed = abs(speed)<lowestMovePower && abs(speed)>0?speed/abs(speed)*lowestMovePower:speed;

		//spin(speed);
		setSlew(speed, -speed, 5);

	} while(true);
}

task rightSwing () {
	int speed;
	string out;
	int lowestMovePower = 21;

	gyroscope.kP = 0.2;
	gyroscope.kI = 0.0025;
	gyroscope.kD = 0.05;//3;

	do {
		//P
		gyroscope.error = gyroscope.target - SensorValue[gyro];

		//I
		if (abs(gyroscope.error)>100 || gyroscope.error == 0)
			gyroscope.integral = 0;
		else
			gyroscope.integral += gyroscope.error;

		//D
		gyroscope.derivative = gyroscope.error - gyroscope.lastError;

		speed = gyroscope.kP*gyroscope.error + gyroscope.kI*gyroscope.integral + gyroscope.kD*gyroscope.derivative;

		//speed = gyroscope.error==0?0:speed;
		//speed = abs(speed)>30?speed/abs(speed)*30:speed; //fancy way of high deadbands
		//speed = abs(speed)<lowestMovePower && abs(speed)>0?speed/abs(speed)*lowestMovePower:speed;

		setRightWheelSpeed(abs(speed)>maxSpeedSwing?(maxSpeedSwing)*sgn(speed):speed);

	} while(true);
}

task leftSwing () {
	int speed;
	string out;
	int lowestMovePower = 21;

	gyroscope.kP = 0.2;
	gyroscope.kI = 0.0025;
	gyroscope.kD = 0.05;//3;

	do {
		//P
		gyroscope.error = gyroscope.target - SensorValue[gyro];

		//I
		if (abs(gyroscope.error)>100 || gyroscope.error == 0)
			gyroscope.integral = 0;
		else
			gyroscope.integral += gyroscope.error;

		//D
		gyroscope.derivative = gyroscope.error - gyroscope.lastError;

		speed = gyroscope.kP*gyroscope.error + gyroscope.kI*gyroscope.integral + gyroscope.kD*gyroscope.derivative;

		//speed = gyroscope.error==0?0:speed;
		//speed = abs(speed)>30?speed/abs(speed)*30:speed; //fancy way of high deadbands
		//speed = abs(speed)<lowestMovePower && abs(speed)>0?speed/abs(speed)*lowestMovePower:speed;

		setLeftWheelSpeed(abs(speed)>maxSpeedSwing?(maxSpeedSwing)*sgn(-speed):-speed);

	} while(true);
}

void orientStop (int target, int threshold) {
	setWheelSpeed(0,0);
	gyroscope.target = target;
	startTask(orient);
	while(abs(gyroscope.error)>threshold) { delay(5); }
	stopTask(orient);
}

void rightSwingStop (int target, int threshold) {
	setWheelSpeed(0,0);
	gyroscope.target = target;
	startTask(rightSwing);
	while(abs(gyroscope.error)>threshold) { delay(5); }
	stopTask(rightSwing);
}

void leftSwingStop (int target, int threshold) {
	setWheelSpeed(0,0);
	gyroscope.target = target;
	startTask(leftSwing);
	while(abs(gyroscope.error)>threshold) { delay(5); }
	stopTask(leftSwing);
}

void rightSwingWait (int target, int threshold, int time) {
	setWheelSpeed(0,0);
	gyroscope.target = target;
	startTask(rightSwing);
	delay(time);
	stopTask(rightSwing);
}

void leftSwingWait (int target, int threshold, int time) {
	setWheelSpeed(0,0);
	gyroscope.target = target;
	startTask(leftSwing);
	delay(time);
	stopTask(leftSwing);
}
