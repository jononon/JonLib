#pragma systemFile

#warning "drivePID"

pid l;
pid r;

int maxSpeed = 100;

int numberAutons = 7;

string autonomousMenu[7] = {
	"fourBalls",
	"rSCurveAuto",
	"rAngleShotAuto",
	"rFourCross",
	"lSCurveAuto",
	"lAngleShotAuto",
	"lFourCross"
};

task drivebasePID () {

	double kP = 0.1;
	double kI = 0.001;
	double kD = 0.8;
	double threshold = 50;

	l.threshold = threshold;
	r.threshold = threshold;

	l.kP = kP;
	r.kP = kP;

	l.kI = kI;
	r.kI = kI;

	l.kD = kD;
	r.kD = kD;

	while (true) {
		l.error = l.target - nMotorEncoder[leftWheel13]; //add sensor
		r.error = r.target - nMotorEncoder[rightWheel13]; //same

		l.integral += l.error;
		r.integral += r.error;

		if(l.error == 0) { l.integral = 0; }
		if(r.error == 0) { r.integral = 0; }

		l.derivative = l.error - l.lastError;
		r.derivative = l.error - l.lastError;

		l.lastError = l.error;
		r.lastError = r.error;

		int leftOut = l.kP*l.error + l.kI*l.integral + l.kD*l.derivative;
		int rightOut = r.kP*r.error + r.kI*r.integral + r.kD*r.derivative;

		leftOut = leftOut>maxSpeed?maxSpeed:leftOut;
		rightOut = rightOut>maxSpeed?maxSpeed:rightOut;

		leftOut = leftOut<-maxSpeed?-maxSpeed:leftOut;
		rightOut = rightOut<-maxSpeed?-maxSpeed:rightOut;

		setLeftWheelSpeed(leftOut);
		setRightWheelSpeed(rightOut);

		delay(25);

	}
}

void addTargetNoIntegral (int leftTarget, int rightTarget, int speed) {
	maxSpeed = speed;
	l.target = nMotorEncoder(leftWheel13) + leftTarget;
	r.target = nMotorEncoder(rightWheel13) + rightTarget;
}

void addTarget (int leftTarget, int rightTarget, int speed) {
	maxSpeed = speed;
	l.integral = 0;
	r.integral = 0;
	l.target = nMotorEncoder(leftWheel13) + leftTarget;
	r.target = nMotorEncoder(rightWheel13) + rightTarget;
}

void addTarget (int leftTarget, int rightTarget) {
	addTarget(leftTarget, rightTarget, 100);
}

void addTarget (int target) {
	addTarget(target, target);
}

void addTargetAuto (int leftTarget, int rightTarget) {
	addTarget(leftTarget, rightTarget);
	while (l.error<=l.threshold && r.error<=r.threshold) { delay(25); }
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
	while (l.error<=l.threshold && r.error<=r.threshold) { delay(25); }
}

void setTargetAuto (int target) {
	setTargetAuto(target, target);
}
