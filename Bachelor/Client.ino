

#include "VirtualWire.h"
#include <Wire.h>
#include "ADXL345.h"
#include "ITG3200.h"

ADXL345 adxl; 
ITG3200 gyro;

void setup() {
    Serial.begin(9600);	
    Serial.println("setup");
    initRadio();
    initAccelerometr();
    gyro.init();
    gyro.zeroCalibrate(1000,10);
}



void loop() {
    const char *msg = "hello";
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    digitalWrite(13, true); 
    
    int x,y,z;  
    adxl.readXYZ(&x, &y, &z);

    sendInfo(x,0);
    sendInfo(y,1);
    sendInfo(z,2);

    Serial.print(x);
    Serial.print(" y ");
    Serial.print(y);
    Serial.print(" ");
    Serial.print(z);
    Serial.println(" ");
    
    gyro.getXYZ(&x,&y,&z);
    sendInfo(x,3);
    sendInfo(y,4);
    sendInfo(z,5);
    
    Serial.print(x);
    Serial.print(" ");
    Serial.print(y);
    Serial.print(" ");
    Serial.print(z);
    Serial.println(" ");
    
    Serial.println("Sent");
    digitalWrite(13, false);
    
    
    if (vw_wait_rx_max(300)) {
      if (vw_get_message(buf, &buflen)) {
  	Serial.print("Got: ");
  	    
  	for (int i = 0; i < buflen; i++) {
  		Serial.print(buf[i], HEX);
  		Serial.print(" ");
  	}
  	Serial.println("");
      }
    } else {
	Serial.println("Timeout");
    }
    delay(4000);
	
}

void sendInfo(int value, char type){
  uint8_t array[3];
  array[0] = value & 0xff;
  array[1] = (value >> 8);
  array[2] = type;
  vw_send((uint8_t *)array, 3);
  vw_wait_tx(); // Wait until the whole message is gone
  delay(100);
}

void initRadio() {
  vw_set_ptt_inverted(true); 
  vw_setup(2000);	 // Bits per sec
  vw_rx_start();       // Start the receiver PLL running
}

void initAccelerometr() {
  adxl.powerOn();

  //set activity/ inactivity thresholds (0-255)
  adxl.setActivityThreshold(75); //62.5mg per increment
  adxl.setInactivityThreshold(75); //62.5mg per increment
  adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?
 
  //look of activity movement on this axes - 1 == on; 0 == off 
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);
 
  //look of inactivity movement on this axes - 1 == on; 0 == off
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);
 
  //look of tap movement on this axes - 1 == on; 0 == off
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(1);
 
  //set values for what is a tap, and what is a double tap (0-255)
  adxl.setTapThreshold(50); //62.5mg per increment
  adxl.setTapDuration(15); //625us per increment
  adxl.setDoubleTapLatency(80); //1.25ms per increment
  adxl.setDoubleTapWindow(200); //1.25ms per increment
 
  //set values for what is considered freefall (0-255)
  adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment
 
  //setting all interrupts to take place on int pin 1
  //I had issues with int pin 2, was unable to reset it
  adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN );
 
  //register interrupt actions - 1 == on; 0 == off  
  adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  1);
  adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   1);
  adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);
}
