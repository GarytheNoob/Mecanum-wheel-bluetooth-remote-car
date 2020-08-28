// for Mecanum wheel cars to move in multi directions
// with bluetooth from smartphones
#include <SoftwareSerial.h>
#include <FastLED.h>

//initialization of LEDs
SoftwareSerial BTserial(2,3);
CRGB leds[NUM_LEDS];
const int MAX_BRIGHT = 90;
/*
NG use define for const initializations,
better use "const int DATA_PIN = 1;" instead!
*/
#define DATA_PIN  1
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    24

//the state of a wheel, go back, front or stop
enum wheelState{BACK, STOP, FRONT};

//func definations
void RBwheel(wheelState);
void RFwheel(wheelState);
void LBwheel(wheelState);
void LFwheel(wheelState);
void forward();
void backward();
void left();
void right();
void leftFr();
void leftBk();
void rightFr();
void rightBk();
void allStop();
void turnLeft();
void turnRight();
void lift();
void roll();
void stopRoll();

//command got from bluetooth
char cmd;

//arduino setup() func
void setup(){
	//bluetooth channel
	BTserial.begin(9600);

	//set pinmodes
	pinMode(13, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(4, OUTPUT);
	
	//stop everything
	allStop();
	digitalWrite(5, LOW);
	digitalWrite(4, LOW);

	//make a led
	LEDS.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
	FastLED.setBrightness(MAX_BRIGHT);
	//initialization to a color
	fill_solid(leds, 24, CRGB::Tianyi);//CRGB::Tinayi is 0x66ccff
	FastLED.show();
}
//arduino loop() func
void loop(){
	//got a command
	if(BTserial.available()){
		cmd = BTserial.read();
		//if got command, first stop everything
		allStop();
		//choose what to do
		switch(cmd){
			case 'F': forward(); break;
			case 'B': backward(); break;
			case 'L': left(); break;
			case 'R': right(); break;
			case 'C': turnRight(); break;
			case 'A': turnLeft(); break;
			case 'U': lift(); break;
			case 'M': roll(); break;
			case 'N': stopRoll(); break;
		}
	}
}
//control each wheel
void RBwheel(wheelState aS){
	switch(aS){
		//0:back, 1:stop, 2:front
		case 0: digitalWrite(13, LOW);
				digitalWrite(12, HIGH);
				break;
		case 1: digitalWrite(13, LOW);
				digitalWrite(12, LOW);
				break;
		case 2: digitalWrite(13, HIGH);
				digitalWrite(12, LOW);
				break;
	}
}
void RFwheel(wheelState aS){
	switch(aS){
		//0:back, 1:stop, 2:front
		case 0: digitalWrite(11, LOW);
				digitalWrite(10, HIGH);
				break;
		case 1: digitalWrite(11, LOW);
				digitalWrite(10, LOW);
				break;
		case 2: digitalWrite(11, HIGH);
				digitalWrite(10, LOW);
				break;
	}
}
void LBwheel(wheelState aS){
	switch(aS){
		//0:back, 1:stop, 2:front
		case 0: digitalWrite(9, LOW);
				digitalWrite(8, HIGH);
				break;
		case 1: digitalWrite(9, LOW);
				digitalWrite(8, LOW);
				break;
		case 2: digitalWrite(9, HIGH);
				digitalWrite(8, LOW);
				break;
	}
}
void LFwheel(wheelState aS){
	switch(aS){
		//0:back, 1:stop, 2:front
		case 0: digitalWrite(7, LOW);
				digitalWrite(6, HIGH);
				break;
		case 1: digitalWrite(7, LOW);
				digitalWrite(6, LOW);
				break;
		case 2: digitalWrite(7, HIGH);
				digitalWrite(6, LOW);
				break;
	}
}

//move in every directions
//Mecanum wheel cars moving methods
void forward(){
	fill_solid(leds, NUM_LEDS, CRGB::Green);
	FastLED.show();
	RBwheel(FRONT);
	RFwheel(FRONT);
	LBwheel(FRONT);
	LFwheel(FRONT);
}
void backward(){
	fill_solid(leds, NUM_LEDS, CRGB::Blue);
	FastLED.show();
	RBwheel(BACK);
	RFwheel(BACK);
	LBwheel(BACK);
	LFwheel(BACK);
}
void left(){
	fill_solid(leds, 24, CRGB::Red);
    FastLED.show();
	RBwheel(BACK);
	RFwheel(FRONT);
	LBwheel(FRONT);
	LFwheel(BACK);
}
void right(){
	fill_solid(leds, 24, CRGB::Yellow);
    FastLED.show();
	RBwheel(FRONT);
	RFwheel(BACK);
	LBwheel(BACK);
	LFwheel(FRONT);
}
void leftFr(){
	RBwheel(STOP);
	RFwheel(FRONT);
	LBwheel(FRONT);
	LFwheel(STOP);
}
void leftBk(){
	RBwheel(STOP);
	RFwheel(BACK);
	LBwheel(BACK);
	LFwheel(STOP);
}
void rightFr(){
	RBwheel(FRONT);
	RFwheel(STOP);
	LBwheel(STOP);
	LFwheel(FRONT);
}
void rightBk(){
	RBwheel(BACK);
	RFwheel(STOP);
	LBwheel(STOP);
	LFwheel(BACK);
}
//to stop all motors
void allStop(){
	RBwheel(STOP);
	RFwheel(STOP);
	LBwheel(STOP);
	LFwheel(STOP);
	fill_solid(leds, NUM_LEDS, CRGB::Black);
	FastLED.show();
}
//to turn instead of move left and right
void turnLeft(){
	fill_solid(leds, 24, CRGB::Pink);
    FastLED.show();
	RBwheel(FRONT);
	RFwheel(FRONT);
	LBwheel(BACK);
	LFwheel(BACK);
}
void turnRight(){
	fill_solid(leds, 24, CRGB::Purple);
    FastLED.show();
	RBwheel(BACK);
	RFwheel(BACK);
	LBwheel(FRONT);
	LFwheel(FRONT);
}

void lift(){
	fill_solid(leds, 24, CRGB::Orange);
    FastLED.show();
	digitalWrite(5, HIGH);
    delay(300);
    digitalWrite(5, LOW);
}
void roll(){
	fill_solid(leds, 24, CRGB::Aquamarine);
    FastLED.show();
	digitalWrite(4, HIGH);
}
void stopRoll(){
	fill_solid(leds, 24, CRGB::BlanchedAlmond);
    FastLED.show();
	digitalWrite(4, LOW);
}
