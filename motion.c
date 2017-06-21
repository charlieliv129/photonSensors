PRODUCT_ID(4351);
PRODUCT_VERSION(1);

// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_ST7735.h>
// This #include statement was automatically added by the Particle IDE.


//SCL to A3
//SDA to A5
//GND to GND
//VCC to VIN

#define cs A2 //chip select for LCD
#define dc D0
#define rst 0


#define inputPin D2  // choose the input pin (for PIR sensor)
#define ledPin D7

int val = LOW;   // variable for reading the pin status
int pirState = LOW;             // we start, assuming no motion detected
String state = "";

Adafruit_ST7735 tft = Adafruit_ST7735(cs,dc,rst);

void setup() {
    Serial.begin(9600);
    pinMode(inputPin, INPUT); //sensor
    pinMode(ledPin, OUTPUT); //led
    tft.initG();
    tft.fillScreen(ST7735_BLACK); //setting up screen
    tft.setTextColor(ST7735_GREEN);
    tft.setTextSize(2);
    tft.setCursor(0,0);
}

void loop() {
    digitalWrite(ledPin, LOW); //led off at start
    bool status = false;
    int i = 0; //start loop over
    int tag = -1;
    state = "0";
    val = LOW; //reset everything to no motion seen
    while (i < 60)
    {
        val = digitalRead(inputPin); //read input value
        if (status == true) //already registered motion in last 30 seconds
        {
            if (val == LOW) //if there is no motion at this time
            {
                digitalWrite(ledPin, LOW); //turn the led off
                if (tag != 2)
                {
                    tag = 2;
                    motionOnCyclePast(); //display that there is no current motion, but there was on the current cycle
                }
            }
            else 
            {
                digitalWrite(ledPin, HIGH); //if motion turn on the led
                if (tag != 1)
                {
                    tag = 1;
                    motionOnCycleCurrent(); //say that there was and is motion
                }
            }   
            i++;
            state = "1"; //motion occurred
            delay(1000);
            continue;
        }
        if (val == HIGH) //if motion for first time
        {
            digitalWrite(ledPin, HIGH); //led on 
            status = true; //has seen motion
            if (tag != 1)
            {
                motionOnCycleCurrent(); //motion occurred in cycle and now
                tag = 1; //to prevent flashing same text repeatedly 
            }
        }
        if (tag == -1)
        {
            noMotionOnCycle(); //no motion yet 
            tag = 0;
        }
        delay(1000);
        i++;
    }
    tft.setTextColor(ST7735_GREEN);
    tft.println("End Cycle"); //when cycle is over 
    
    //Particle.publish("Movement", state, PRIVATE); //publish results of the cycle
    Particle.publish("motion", state, PRIVATE); //azure
}

void noMotionOnCycle() //tag = 0
{
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0,0);
    tft.setTextColor(ST7735_GREEN);
    tft.println("Cycle\nStatus:");
    tft.setTextColor(ST7735_RED);
    tft.println("No Motion");
}
void motionOnCycleCurrent() //tag = 1
{
    tft.setTextColor(ST7735_GREEN);
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0,0);
    tft.println("Cycle\nStatus:");
    tft.setTextColor(ST7735_RED);
    tft.println("Motion\nRegistered");
    tft.setTextColor(ST7735_GREEN);
    tft.println("Current\nStatus:");
    tft.setTextColor(ST7735_RED);
    tft.println("Motion\nDetected");
}
void motionOnCyclePast() //tag = 2
{
    tft.setTextColor(ST7735_GREEN);
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0,0);
    tft.println("Cycle\nStatus:");
    tft.setTextColor(ST7735_RED);
    tft.println("Motion\nRegistered");
    tft.setTextColor(ST7735_GREEN);
    tft.println("Current\nStatus:");
    tft.setTextColor(ST7735_RED);
    tft.println("No Motion\nDetected");
}