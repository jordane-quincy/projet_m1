#include <Usb.h>
#include <AndroidAccessory.h>


#define  LED3_RED       2
#define  LED3_GREEN     4
#define  LED3_BLUE      3

AndroidAccessory acc("Google, Inc.",
		     "DemoKit",
		     "DemoKit Arduino Board",
		     "1.0",
		     "http://www.android.com",
		     "0000000012345678");

void setup();
void loop();

void init_pin()
{
	pinMode(BUTTON1, INPUT);
	pinMode(BUTTON2, INPUT);
	pinMode(BUTTON3, INPUT);
	pinMode(JOY_SWITCH, INPUT);

	// enable the internal pullups
	digitalWrite(BUTTON1, HIGH);
	digitalWrite(BUTTON2, HIGH);
	digitalWrite(BUTTON3, HIGH);
	digitalWrite(JOY_SWITCH, HIGH);
}

void setup()
{
        Serial.print("\r\nStart");
        Serial.begin(115200);
	
        Serial.print("\r\nInit pin");
	init_pin();
        Serial.print("\r\nAndroid power on");
	acc.powerOn();
}

void loop()
{
	byte err;
	byte idle;
	static byte count = 0;
	byte msg[4];
	long touchcount;

	if (acc.isConnected()) {
                Serial.print("\r\nAndroid is connected at : ");Serial.print (millis(),DEC);
                msg[0] = 'a';
                msg[1] = 'b';
                msg[2] = 'c';
                msg[3] = '\n';
                acc.write(msg, sizeof(msg));
	} else {
            
                Serial.print("\r\nAndroid is not plugged");
	}

	delay(1000);
}
