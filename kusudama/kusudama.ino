#include "Arduino.h"
///////////////////LED CLASS////////////////////////////////////////
class Led
{
	public:
		Led(int pin);
		~Led();
	    void ON();
	    void OFF();
	    void fading();
	    void brightness(int brtns);
	    void toggle();
	private:
		int _pin;
		int _brightness;
		int _incriment;
};

// -------LED Class definition -----------//

Led::Led(int pin){
	_pin = pin;
	_brightness = 0;
	_incriment = 1;
	analogWrite( _pin, 200);
	analogWrite( _pin, _brightness); // make sure that LED is off 
}
Led::~Led(){}

void Led::brightness(int brtns){
	_brightness = brtns;
	analogWrite(_pin, brtns);
}

void Led::ON(){
	brightness(200);
}

void Led::OFF(){
	brightness(0);
}

void Led::toggle(){
	if(_brightness >= 200){
	    brightness(0);
	}else{
		brightness(200);
	}
}

void Led::fading(){	
	if(_brightness > 254){
		_incriment = -1;
	}else if(_brightness <= 10 ){
		_incriment = 1;
	}
	int temp = _brightness + _incriment;
	brightness(temp);
	Serial.println(_brightness);
}
////////////////////////////////LED Class END//////////////////////////////////////

Led led1(3);
Led led2(5);
Led led3(6);
Led UVled1(10);
Led UVled(12);


int button = 4;
int mode = 0;
bool set = true;
unsigned long prevMillis = 0;
unsigned long currentMillis;
long interval = 100;
int curLED = 0;
int roundDelay = 100;
bool triger = false;


void OFF(){
	set = true;
	led1.OFF();
	led2.OFF();
	led3.OFF();
	UVled.OFF();
	UVled1.OFF();
}
void ON(){
	set = true;
	OFF();
	led1.ON();
	led2.ON();
	led3.ON();
	UVled.ON();
	UVled1.ON();
}
void UV(){
	set = true;
	OFF();
	UVled.ON();
	UVled1.ON();
}

void Randome(){
	set = true;
	int temp = random(0, 2);
	if(currentMillis - prevMillis >= temp){
		int randVal = 0;
		randomSeed(analogRead(A5));
		randVal = random(1, 5);
		switch (randVal) {
		    case 1:
		      led1.fading();
		      break;
		    case 2:
		      led2.fading();
		      break;
		    case 3:
		      led3.fading();
		      break;
		    case 4:
		      UVled.fading();
		      break;
		    case 5:
		      UVled1.fading();
		      break;
		}
		prevMillis = currentMillis;
	}	
}
void RoundGlow(){
	curLED += 1;
	if(curLED >= 5){curLED = 0;}
	if(currentMillis - prevMillis >= roundDelay){
		OFF();
		switch (curLED) {
		    case 0:
		      led1.ON();
		      break;
		    case 1:
		      led2.ON();
		      break;
		    case 2:
		      led3.ON();
		      break;
		    case 3:
		      UVled1.ON();
		      break;
		    case 4:
		      UVled.ON();
		      roundDelay = random(50, 500);
		      break;
		}
		prevMillis = currentMillis;
	}
}
void setup(){
	pinMode(button , INPUT);
	Serial.begin(9600);
}


// ************* MAIN LOOP *********** //
void loop(){
	currentMillis = millis();
	// read button input 
	if(digitalRead(button)== HIGH){
		set = false;
        delay(500);        
		if(mode == 4 ){	mode = 0;}
		else{ mode += 1; }		
	}
	switch (mode) {
		    case 0 :
		      // OFF mode 
		      OFF();
		      break;
		    case 1 :
		      // statick ON mode 
		      ON();
		      break;
		    case 2 :
		      // UV mode
		      UV();
		      break;
		     case 3 :
		      // randome fade
		      Randome();
		      break;
		     case 4 :
		      // randome circular glow
		      RoundGlow();
		      break;
	}
    //Serial.println(mode);
}