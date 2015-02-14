
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"



#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin


Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 


// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *Motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *Motor2 = AFMS.getMotor(2);


int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  AFMS.begin();  // create with the default frequency 1.6KHz
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


}



void stopMotors(){
  Motor1->run(RELEASE);
  Motor2->run(RELEASE);
}

void turnLeft(int timer = 500){
  Motor1->run(FORWARD);
  Motor2->run(BACKWARD);
  Motor1->setSpeed(100);
  Motor2->setSpeed(100);
  delay(timer);
  stopMotors();
}

void forward(){
  Motor1->run(FORWARD);
  Motor2->run(FORWARD);
  Motor1->setSpeed(200);
  Motor2->setSpeed(200); 
}

void backwords(){
  Motor1->run(BACKWARD);
  Motor2->run(BACKWARD);
  Motor1->setSpeed(150);
  Motor2->setSpeed(150); 
}


void loop(){  
  int temp = getDistance();
  if(temp >= 15){
     forward();
  }else{
      stopMotors(); 
      backwords();
      delay(200);
      stopMotors(); 
      while(temp >=15){
         temp = getDistance();
         turnLeft(10);
      }
  }

}

int getDistance(){
 distance = 0;
 
 for( int i = 0; i < 4 ; i++){
   long temp = 0;
   /* The following trigPin/echoPin cycle is used to determine the
   distance of the nearest object by bouncing soundwaves off of it. */ 
   digitalWrite(trigPin, LOW); 
   delayMicroseconds(2); 
  
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10); 
   
   digitalWrite(trigPin, LOW);
   temp = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
   temp = temp/58.2;   
   distance += temp;
 }
 
 int out = distance/4;
 return out;
}





