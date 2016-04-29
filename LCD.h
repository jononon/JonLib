#pragma systemFile            	// eliminates warning for "unreferenced" functions
enum { 	LCD_NO_BUTTONS = 0,
				LCD_LEFT_BUTTON = 1,
				LCD_CENTRE_BUTTON = 2, LCD_CENTER_BUTTON = 2,
				LCD_LEFT_CENTRE_BUTTON = 3, LCD_LEFT_CENTER_BUTTON = 3,
				LCD_RIGHT_BUTTON = 4,
				LCD_LEFT_RIGHT_BUTTON = 5,
				LCD_CENTRE_RIGHT_BUTTON = 6, LCD_CENTER_RIGHT_BUTTON = 6,
				LCD_LEFT_CENTRE_RIGHT_BUTTON = 7, LCD_LEFT_CENTER_RIGHT_BUTTON = 7 };

#warning "clearLCD"
void clearLCD () {
	clearLCDLine(0);
	clearLCDLine(1);
}

#warning "waitForRelease"
void waitForRelease () {
	while(nLCDButtons != 0)
		delay(25);
}

#warning "waitForPress"
void waitForPress () {
	while (nLCDButtons == 0)
		delay(25);
}

void centerLine ( int lineNumber, string* contents ) {
	string out;
	sprintf(out,"%s",contents);
	displayLCDCenteredString(lineNumber, out);
}

void line( int lineNumber, string* contents ) {
	string out;
	sprintf(out,"%s",contents);
	displayLCDString(lineNumber,0,out);
}

void centerDisplay (string line0, string* line1) {
	centerLine(0, line0);
	centerLine(1, line1);
}

task LCD ();
