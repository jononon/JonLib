#pragma systemFile

#warning "drivePID"

pid l;
pid r;

int maxSpeed = 100;

int numberAutons = 10;

string autonomousMenu[10] = {
	"L 3s, c, corn",
	"L 3s, c",
	"L 3s",
	"L corn, c",
	"L corn",
	"R 3s, c, corn",
	"R 3s, c",
	"R 3s",
	"R corn, c",
	"R corn",
};

void setSlew(int left, int right, int slew) {
	if(abs(left-motor[leftWheel1])>slew) {
		if(motor[leftWheel1]>left)
			left = motor[leftWheel1]-slew;
		else
			left = motor[leftWheel1]+slew;
	}

	if(abs(right-motor[leftWheel1])>slew) {
		if(motor[leftWheel1]>right)
			right = motor[leftWheel1]-slew;
		else
			right = motor[leftWheel1]+slew;
	}

	setLeftWheelSpeed(left);
	setRightWheelSpeed(right);

}

task drivebasePID () {

	float kP = 0.1;
	float kI = 0.0015;
	float kD = 0.07;
	float threshold = 150*(4.0/2.75);

	l.threshold = threshold;
	r.threshold = threshold;

	l.kP = kP;
	r.kP = kP;

	l.kI = kI;
	r.kI = kI;

	l.kD = kD;
	r.kD = kD;

	while (true) {
		l.error = l.target - SensorValue[leftDriveEnc]; //add sensor
		r.error = r.target + SensorValue[rightDriveEnc]; //same

		if(abs(l.error)<200)
			l.integral += l.error;
		else
			l.integral = 0;

		if(abs(r.error)<200)
			r.integral += r.error;
		else
			r.integral = 0;

		if(l.error == 0) { l.integral = 0; }
		if(r.error == 0) { r.integral = 0; }

		l.derivative = l.error - l.lastError;
		r.derivative = r.error - r.lastError;

		l.lastError = l.error;
		r.lastError = r.error;

		int leftOut = l.kP*l.error + l.kI*l.integral + l.kD*l.derivative;
		int rightOut = r.kP*r.error + r.kI*r.integral + r.kD*r.derivative;

		leftOut = leftOut>maxSpeed?maxSpeed:leftOut;
		rightOut = rightOut>maxSpeed?maxSpeed:rightOut;

		leftOut = leftOut<-maxSpeed?-maxSpeed:leftOut;
		rightOut = rightOut<-maxSpeed?-maxSpeed:rightOut;

		writeDebugStreamLine("err: %d %d",  l.error, r.error);

		setSlew(leftOut, rightOut, 7);

		delay(25);

	}
}

float gyroP = 0.6;
task drivebaseGyroPID () {

	float kP = 0.1;
	float kI = 0.0015;
	float kD = 0.07;
	float threshold = 150*(4.0/2.75);

	l.threshold = threshold;
	r.threshold = threshold;

	l.kP = kP;
	r.kP = kP;

	l.kI = kI;
	r.kI = kI;

	l.kD = kD;
	r.kD = kD;

	while (true) {
		l.error = l.target - SensorValue[leftDriveEnc]; //add sensor
		r.error = r.target + SensorValue[rightDriveEnc]; //same

		if(abs(l.error)<200)
			l.integral += l.error;
		else
			l.integral = 0;

		if(abs(r.error)<200)
			r.integral += r.error;
		else
			r.integral = 0;

		if(l.error == 0) { l.integral = 0; }
		if(r.error == 0) { r.integral = 0; }

		l.derivative = l.error - l.lastError;
		r.derivative = r.error - r.lastError;

		l.lastError = l.error;
		r.lastError = r.error;

		int leftOut = l.kP*l.error + l.kI*l.integral + l.kD*l.derivative;
		int rightOut = r.kP*r.error + r.kI*r.integral + r.kD*r.derivative;

		leftOut = leftOut>maxSpeed?maxSpeed:leftOut;
		rightOut = rightOut>maxSpeed?maxSpeed:rightOut;

		leftOut = leftOut<-maxSpeed?-maxSpeed:leftOut;
		rightOut = rightOut<-maxSpeed?-maxSpeed:rightOut;

		writeDebugStreamLine("err: %d %d",  l.error, r.error);

		setSlew(leftOut+(SensorValue[gyro]*gyroP), rightOut-SensorValue[gyro]*gyroP, 7);

		delay(25);

	}
}

void addTargetNoIntegral (int leftTarget, int rightTarget, int speed) {
	maxSpeed = speed;
	l.target = nMotorEncoder(leftWheel1) + leftTarget;
	r.target = nMotorEncoder(rightWheel1) + rightTarget;
}

void addTarget (int leftTarget, int rightTarget, int speed) {
	maxSpeed = speed;
	l.integral = 0;
	r.integral = 0;
	l.target = leftTarget - SensorValue[leftDriveEnc];
	r.target = rightTarget - SensorValue[rightDriveEnc];
}

void addTarget (int leftTarget, int rightTarget) {
	addTarget(leftTarget, rightTarget, 100);
}

void addTarget (int target) {
	addTarget(target, target);
}

void addTargetAuto (int leftTarget, int rightTarget) {
	addTarget(leftTarget, rightTarget);
	delay(25);
	while (abs(l.error)>=l.threshold && abs(r.error)>=r.threshold) { delay(5); }
}

void addTargetAuto (int target) {
	addTargetAuto(target, target);
}

void setTarget (int leftTarget, int rightTarget , int speed) {
	maxSpeed = speed;
	l.integral = 0;
	r.integral = 0;
	l.target = leftTarget;
	r.target = rightTarget;
}

void setTarget (int leftTarget, int rightTarget) {
	setTarget(leftTarget, rightTarget, 100);
}

void setTarget (int target) {
	setTarget(target, target);
}

void setTargetAuto (int leftTarget, int rightTarget) {
	setTarget(leftTarget, rightTarget);
	delay(25);
	while (abs(l.error)>=l.threshold && abs(r.error)>=r.threshold) {
		delay(5);
	}
}

void setTargetAuto (int target) {
	setTargetAuto(target, target);
}
