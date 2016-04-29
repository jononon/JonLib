#include "PID.h"
#include "Drivebase.h"
#include "BNSBluetooth/BNSlib_HC05.h"
//#include "../MarkIIIPragma.c"

#pragma systemFile

pid gyroscope;

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

	gyroscope.kP = 0.1;
	gyroscope.kI = 0.00025;
	gyroscope.kD = 0.3;

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

		speed = gyroscope.error==0?0:speed;
		speed = abs(speed)>30?speed/abs(speed)*30:speed; //fancy way of high deadbands
		//speed = abs(speed)<lowestMovePower && abs(speed)>0?speed/abs(speed)*lowestMovePower:speed;

		spin(speed);
		sprintf(out, "%d",SensorValue[gyro]);
		bnsSerialSend(UART1, out);

	} while(true);
}
