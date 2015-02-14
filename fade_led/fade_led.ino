
int led = 5;
int interval = 10;
int brightnes = 50;
unsigned long prevMillis = 0;
int difference = 1;

void setup(){
  Serial.begin(9600);
}

void loop(){
 
 unsigned long time = millis();
 
 if(time - prevMillis > interval ){
   prevMillis = time;
   if(brightnes >= 250) { difference = -1;}
   
   if(brightnes <= 0) {difference =  1;}
   
   brightnes = brightnes+difference;
 }
 
 Serial.println(brightnes);
 analogWrite(led , brightnes);

 
  
}


