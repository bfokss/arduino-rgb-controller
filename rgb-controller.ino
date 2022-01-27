//Include section
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <IRremote.h>
//Include section

//Define section
#define PIN 8
#define NUMPIXELS 12
#define DELAYVAL 100
//Define section

//Neo pixel LED strip initialization
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//COLORS
uint32_t RED = pixels.Color(255, 0, 0);
uint32_t ORANGE = pixels.Color(255,69,0);
uint32_t YELLOW = pixels.Color(255,165,0);
uint32_t GREEN = pixels.Color(0, 255, 0);
uint32_t AQUAMARINE = pixels.Color(127, 255, 212);
uint32_t DARKGREEN = pixels.Color(0,100,0);
uint32_t BLUE = pixels.Color(0, 0, 255);
uint32_t PURPLE = pixels.Color(128,0,128);
uint32_t PINK = pixels.Color(255,192,203);
//COLORS

//MODES
#define volup 0xFD807F
#define voldown 0xFD906F
#define rnd 0xFD30CF
#define mode1 0xFD08F7
#define mode2 0xFD8877
#define mode3 0xFD48B7
#define mode4 0xFD28D7
#define mode5 0xFDA857
#define mode6 0xFD6897
#define mode7 0xFD18E7
#define mode8 0xFD9867
#define mode9 0xFD58A7
//MODES

//VARIABLES
uint32_t lastColor = pixels.Color(255, 0, 0);
bool isOn = false;
int redColor = 0;
int greenColor = 0;
int blueColor = 0;
//VARIABLES

//BRIGHTNESS
uint8_t brightness = 128;
#define BRIGHTNESS_INCR 16
//BRIGHTNESS

//IR config
int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
//IR config

//Setup function
void setup()
{
  	//IR config
	#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  		clock_prescale_set(clock_div_1);
	#endif
  	//IR config

  	Serial.begin(9600);
  
  	irrecv.enableIRIn(); // Start the receiver
  
  	pixels.begin();
}
//Setup function

//Main loop function
void loop() {
  	//Check remote button
    if (irrecv.decode(&results)) {
      
        Serial.print("Button code: ");
      	Serial.println(results.value, HEX);
      
      	//Serial.println(isOn);
      
        irrecv.resume(); // Receive the next value

      //Turn ON LED strip
		if((results.value==0xFD00FF)&&(isOn==false)){
            isOn=true;
            Serial.println("ON");
            pixels.fill(lastColor,0, NUMPIXELS);
            pixels.show();
        
      	}
      //Turn OFF LED strip
      	else if((results.value==0xFD00FF)&&(isOn==true)){
            isOn=false;
            pixels.clear();
            pixels.show();
            Serial.println("OFF");
      	}
      //Increase LED strip brightness
      	else if(results.value==volup){
            Serial.println("Button type: VOL+"); 
            if (255 - brightness < BRIGHTNESS_INCR) {
            		brightness = 255;
            } else {
                  	brightness += BRIGHTNESS_INCR;
                	pixels.setBrightness( brightness );
                  	pixels.show();
            }
            Serial.println((String)"Brightness: "+brightness);
      	}
      //Decrease LED strip brightnexx
      	else if(results.value==voldown){ 
        	Serial.println("Button type: VOL-");
            if (brightness <= BRIGHTNESS_INCR) {
            		brightness = 16;
            } else {
                    brightness -= BRIGHTNESS_INCR;
                    pixels.setBrightness( brightness );
                    pixels.show();
            }
            Serial.println((String)"Brightness: "+brightness); 
      	}
      //Act if LED strip is ON
      	if(isOn){
      		translateIR();
  		}//End of LED strip action
    }//End of checking remote button
}//End of main loop function


//Random color generator function
void setColor(){
  redColor = random(0, 255);
  greenColor = random(0,255);
  blueColor = random(0, 255);
}


//IR signal translation function
void translateIR(){
  	switch(results.value){
      	case rnd:
      		setColor();
            for(int i=0;i<=NUMPIXELS;i++){

                // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
                pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
              
                pixels.show();

                delay(DELAYVAL);

                Serial.println(i);

                if (i == NUMPIXELS){
                    i = -1; // start all over again!
                  	Serial.println(i);
                    setColor();
                }
              if (isButtonPressed()) { break; }
            }
        case mode1:
            //RED COLOR
      		Serial.println("Button type: 1. RED");
            pixels.fill(RED,0, NUMPIXELS);
            lastColor = pixels.getPixelColor(0);
            pixels.show();
            break;
        case mode2:
            //GREEN COLOR
        	Serial.println("Button type: 2. GREEN");
            pixels.fill(GREEN,0, NUMPIXELS);
      		lastColor = pixels.getPixelColor(0);
            pixels.show();
            break;
        case mode3:
            //BLUE COLOR
        	Serial.println("Button type: 3. BLUE");
            pixels.fill(BLUE,0, NUMPIXELS);
      		lastColor = pixels.getPixelColor(0);
            pixels.show();
            break;
        case mode4:
            //ORANGE COLOR
        	Serial.println("Button type: 4. ORANGE");
            pixels.fill(ORANGE,0, NUMPIXELS);
      		lastColor = pixels.getPixelColor(0);
            pixels.show();
            break;
        case mode5:
            //DARKGREEN COLOR
        	Serial.println("Button type: 5. DARKGREEN");
            pixels.fill(DARKGREEN,0, NUMPIXELS);
      		lastColor = pixels.getPixelColor(0);
            pixels.show();
            break;
        case mode6:
            //PURPLE COLOR
        	Serial.println("Button type: 6. PURPLE");
            pixels.fill(PURPLE,0, NUMPIXELS);
      		lastColor = pixels.getPixelColor(0);
            pixels.show();
            break;
        case mode7:
            //YELLOW COLOR
        	Serial.println("Button type: 7. YELLOW");
            pixels.fill(YELLOW,0, NUMPIXELS);
      		lastColor = pixels.getPixelColor(0);
            pixels.show();
            break;
        case mode8:
        //AQUAMARINE COLOR
        	Serial.println("Button type: 8. AQUAMARINE");
            pixels.fill(AQUAMARINE,0, NUMPIXELS);
      		lastColor = pixels.getPixelColor(0);
            pixels.show();
            break;
        case mode9:
            //PINK COLOR
        	Serial.println("Button type: 9. PINK");
            pixels.fill(PINK,0, NUMPIXELS);
      		lastColor = pixels.getPixelColor(0);
            pixels.show();
            break;
      }
  }

//Function checking if any button was pressed
bool isButtonPressed() {
  if (irrecv.decode(&results)) {
    return true;
  }
  else return false;
}
