#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
Servo helm;

void setup() { 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  helm.attach(11);
  helm.write(90);
  Serial.begin(9600);
  
  int v=1586;
  while(v < 2120){
    myservo.writeMicroseconds(v);
    delay(100);
    v+=10;
   
  }
} 

int state = 0, value = 1560;


void loop() {
 
  int s;
  if(Serial.available()){
    s = Serial.read();
    switch(s){
      case 3: 
        helm.write(45);
      break;
      case 4: 
        helm.write(135);
      break;
      case 5:
        helm.write(90);
      break;
      default:
        state = s;
    }
  }
  
  switch(state){
      case 1: 
        value+=20;
        myservo.writeMicroseconds(value);
      break;
      case 2: 
        value-=20;
        myservo.writeMicroseconds(value);
      break;
      default:
        if(value<1450){
          value +=20;
        } else if(value>1500){
          value -=20;
        }
    }
  
//  int v=1586;
//  helm.write(135);
//  while(v < 2120){
//    myservo.writeMicroseconds(v);
//    delay(100);
//    v+=10;
//   
//  }
//  while(v > 875){
//    myservo.writeMicroseconds(v);
//    delay(100);
//    v-=10;
//  }
//  helm.write(45);
//  while(v < 1586){
//    myservo.writeMicroseconds(v);
//    delay(100);
//    v+=10;
//  }

}
