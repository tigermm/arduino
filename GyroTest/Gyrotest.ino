// gyroTest.ino

#include "ADXL345.h"
#include "ITG3200.h"

ADXL345 adxl;
ITG3200 gyro;

double XYZ[3], sumx=0, sumy=0, sumz=0;
int gX, gY, gZ;
double XX, YY, ZZ;

void setup() {
	initAccelerometr();
	Serial.begin(9600);
  adxl.getAcceleration(XYZ);
  gyro.init();
  gyro.zeroCalibrate(100,10);
  gyro.getXYZ(&gX,&gY,&gZ);
  XX = 0;
  YY = 0;
  ZZ = 0;
}



void loop() {
	double xyz[3], dx, dy, dz;
	adxl.getAcceleration(xyz);
	Serial.print("a/g ");
	Serial.print(dx = XYZ[0]-xyz[0]);
	Serial.print(" ");
	Serial.print(dy = XYZ[1]-xyz[1]);
	Serial.print(" ");
	Serial.print(dz = XYZ[2]-xyz[2]);
  
	sumx += dx;
  sumy += dy;
  sumz += dz;
  for(int i = 0; i < 3; i++){
    XYZ[i]=xyz[i];
  }
	
  
  // Serial.print("sumx: ");
  // Serial.print(sumx );
  // Serial.print(" sumy: ");
  // Serial.print(sumy );
  // Serial.print(" sumz: ");
  // Serial.println(sumz );

  int gx, gy, gz;
  gyro.getXYZ(&gx,&gy,&gz);
  Serial.print(" ");
  Serial.print(gX-gx);
  Serial.print(" ");
  Serial.print(gY-gy);
  Serial.print(" ");
  Serial.println(gZ-gz);
  double vx, vy, vz;
  vx = 0,01*(gX-gx)*3,14/180;
  vy = 0,01*(gY-gy)*3,14/180;
  vz = 0,01*(gZ-gz)*3,14/180;
  XX += vx*0.5 + dx*9.8*0.5*0.5;
  Serial.print("xx: ");
  Serial.println(XX);


  delay(500);
  gX = gx;
  gY = gy;
  gZ = gz;
}



void initAccelerometr() {
  adxl.powerOn();

  //set activity/ inactivity thresholds (0-255)
  adxl.setActivityThreshold
  (75); //62.5mg per increment
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
