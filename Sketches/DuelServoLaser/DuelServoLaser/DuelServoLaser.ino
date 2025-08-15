//www.elegoo.com
//2018.12.19
#include <Servo.h>
Servo Servo1; //X Servo
Servo Servo2; //Y Servo 

void setup(){
  Serial.begin(9600);
  Serial.println("Arduino is receiving input");


  Servo1.attach(9);
  Servo1.write(90);// move servos to center position -> 90°

  Servo2.attach(6);
  Servo2.write(90);// move servos to center position -> 90
  Serial.println("") 
  Serial.println("Servos is at degree 90");
} 

void loop(){
  int X_positionInput;
  int Y_PoisitonInput;

  Serial.println("X and Y Position"); 

  
 
 
  exit(0);
}
