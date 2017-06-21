
// The on-board LED
#define door A0  // choose the input pin (for PIR sensor)
#define ledPin D7


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(door, INPUT);
}
void loop() {
    int rawAnalogStrength = 0;
    rawAnalogStrength = analogRead(door); // Get a reading
    if (rawAnalogStrength < 400) {
        digitalWrite(ledPin, LOW);    // Turn OFF the LED pins
        delay(100); 
    }
    else {
        digitalWrite(ledPin, HIGH);   // Turn ON the LED pins
        delay(100); 
    }
}