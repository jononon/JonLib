#pragma systemFile

int min(int num1, int num2) {
	if(num1>num2)
		return num2;
	else
		return num1;
}

int max(int num1, int num2) {
	if(num1>num2)
		return num1;
	else
		return num2;
}

int limit (int num, int limit) {
	return sgn(num)*(abs(num)>limit?limit:abs(num));
}