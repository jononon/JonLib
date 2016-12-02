#pragma systemFile

void setLeftWheelSpeed ( int speed = 127 );
void setRightWheelSpeed ( int speed = 127 );

//Sets both sides of the drivebase to differient speeds
#warning "JonLib: Drivebase"
void setWheelSpeed ( int leftWheelSpeed = 127, int rightWheelSpeed = 127 ) {
	setLeftWheelSpeed(leftWheelSpeed);
	setRightWheelSpeed(rightWheelSpeed);
}

//Overloaded - lets both sides of the drivebase to the same speed
void setWheelSpeed ( int wheelSpeed = 127 ) {
	setWheelSpeed(wheelSpeed,wheelSpeed);
}

void spin ( int wheelSpeed = 127 ) {
	setWheelSpeed(-wheelSpeed, wheelSpeed);
}

void timeDrive(int speed, int time) {
	setWheelSpeed(speed);
	wait1Msec(time);
}

void timeDrive(int speed, int time, bool stop) {
	timeDrive(speed, time);
	if(stop)
		setWheelSpeed(0);
}

void tankDrive(int leftPower, int rightPower, int deadbands) {
	setWheelSpeed(abs(leftPower)<deadbands?0:leftPower,abs(rightPower)<deadbands?0:rightPower);
}
