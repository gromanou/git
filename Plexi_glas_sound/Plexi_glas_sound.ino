#define sampleWindow  10
#define micPin        A0
#define GREEN         11
#define RED           9
#define BLUE          10


float gain =0;


void setup(){
 Serial.begin(9600); 
  
}

void loop(){
  
  unsigned long beginMillis = millis();
  float peakToPeak = 0;  
  unsigned int signalMin = 1023;
  unsigned int signalMax = 0;
  
  
  
  
  
  // read sample range from Mic  (Min and Max)
  while( millis() - beginMillis < sampleWindow){   
   double sample = analogRead(micPin);// read mic input    
   if(sample >signalMax){// get Max peak from Mic 
    signalMax = sample; 
   }else if(sample < signalMin){// get Min peak from Mic 
    signalMin = sample; 
   }   
  }
  
  // read gain 
  gain = analogRead(A1);
  gain = map(gain , 0 , 1024, 20 , 140);
  gain += 0.33;
  
  // calculate LVL
  peakToPeak = signalMax - signalMin;
  float lvl = (peakToPeak * gain) / 1023;
  if(lvl > 1.00){ // make sure that value does not jump more  over 1 
     lvl = 1.00; 
  }
 
  int Green = 0, Red = 0, Blue = 0;
  
  int temp = lvl * 100;
  Red = map(temp, 0 , 100 , 0 , 254);
  Red = Red +  50;
  if (temp <= 80){
    Red -= 180; 
  }
  
  if( lvl > 0.20){
    float temp = lvl;
    temp = temp*100;
    Blue = map(temp, 20 , 100 , 0 , 204); 
  }
  if( lvl > 0.40){
    float temp = lvl;
    temp = temp*100;
    Green = map(temp, 40 , 100 , 0  , 254); 
  }
  
  analogWrite(RED,Red);
  analogWrite(BLUE,Blue);
  analogWrite(GREEN,Green);
  
  Serial.println(Red);
  //Serial.println(peakToPeak);  
  
}
