#include <Usb.h>
#include <AndroidAccessory.h>


#define LED0_INTEGRATED 13

AndroidAccessory acc("Google, Inc.",
		     "DemoKit",
		     "DemoKit Arduino Board",
		     "1.0",
		     "http://www.android.com",
		     "0000000012345678");

void setup();
void loop();

void init_pin(){
  pinMode(LED0_INTEGRATED, OUTPUT);
}

void setup() {
  Serial.print("\r\nStart");
  Serial.begin(115200);
  
  Serial.print("\r\nInit pin");
  init_pin();
  
  Serial.print("\r\nAndroid power on");
  acc.powerOn();
}

void blinkLedIntegratedXtimes(int x){
  for (int i=0; i < x; i++){
    digitalWrite(LED0_INTEGRATED, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);              // wait for a second
    digitalWrite(LED0_INTEGRATED, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);              // wait for a second
  }
}

void loop() {
	byte err;
	byte idle;
	static byte count = 0;
	byte msg[4];
	long touchcount;
  int nbBlink = 0;

	if (acc.isConnected()) {
    Serial.print("\r\nAndroid is connected at : ");Serial.print (millis(),DEC);
    int len = acc.read(msg, sizeof(msg), 1);
    if(len > 0){
      //if some data received from the android
      nbBlink = atoi((char*)msg[0]); //FIXME : comment récupérer l'entier au lieu du code ascii (si saisi "2" sur l'android, ne pas récuperer 50 dans nbBlink)
      String log = String("\r\nIntegrated led will blink : ");
      log.concat(nbBlink);
      Serial.print(log);
      blinkLedIntegratedXtimes(nbBlink);
    }
    
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
