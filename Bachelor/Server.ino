
#include "VirtualWire.h"
#include <math.h> 

int  x = 0;
int y = 0;
double gains[3];

void setup() {
    gains[0] = 0.00376390;
    gains[1] = 0.00376009;
    gains[2] = 0.00349265;
    Serial.begin(9600);	// Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec
    vw_rx_start();       // Start the receiver PLL running
}

void loop() {
    const char *msg = "hello";
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    // Wait for a message
    vw_wait_rx();
    if (vw_get_message(buf, &buflen)) {
      int i;
      const char *msg = "recived";

      digitalWrite(13, true); // Flash a light to show received good message
	                           // Message with a good checksum received, dump it.
      int value;
      value = buf[1]<<8;
      value += buf[0];

      switch(buf[2]){
        case 0:
          Serial.print("x: ");
          x = value;
        break;
        case 1:
          Serial.print("y: ");
          y = value;
        break;
        case 2:
          
          double xyz[3];
          xyz[0] = x;
          xyz[1] = y;
          xyz[2] = value;
          Serial.print("a: ");
          Serial.print(atan(xyz[0]/sqrt(xyz[1]*xyz[1]+xyz[2]*xyz[2])));
          Serial.print(" b: ");
          Serial.print(atan(xyz[1]/sqrt(xyz[0]*xyz[0]+xyz[2]*xyz[2])));
          Serial.print(" c: ");
          Serial.println(atan(xyz[2]/sqrt(xyz[1]*xyz[1]+xyz[2]*xyz[2])));
          Serial.print("z: ");
        break;
        case 3:
          Serial.print("gx: ");
        break;
        case 4:
          Serial.print("gy: ");
        break;
        case 5:
          Serial.print("gz: ");
        break;
      }
	
	
	    if(buf[2]>2) {
        Serial.println((value/14.375)*2);
      } else {
        Serial.println(value);
      }
	

	// Send a reply
	vw_send((uint8_t *)msg, strlen(msg));
        vw_wait_tx(); // Wait until the whole message is gone
    
        digitalWrite(13, false);
    }
}
