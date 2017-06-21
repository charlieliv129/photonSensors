// This #include statement was automatically added by the Particle IDE.
#include <PietteTech_DHT.h>

#include <PietteTech_DHT.h>
//#include <Adafruit_ST7735.h>


#define DHTTYPE DHT22
#define DHTPIN D3

int sampleInt = 60000;
int tempf;
double tempfD;
double tempfD2;
double temperatureD;
int temp;
int humidity;
double humidityD;
int dew;
int blue = D7;
String location = "BTC_CBD_1";

//Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst); //hardware spi
PietteTech_DHT DHT(DHTPIN, DHTTYPE);


void setup() {
    pinMode(blue, OUTPUT);
    //Variable exposed to cloud
    Particle.variable("Temperature", temp);
    Particle.variable("Humidity", humidity);
    Particle.variable("DewPt", dew);
    Particle.variable("Location", location);
    

    Serial.begin(9600);
    
    //Particle.variable("Temp", &tempF, DOUBLE);
    
}

void loop() {
    
    int result = DHT.acquireAndWait(1000); //wait up to 1 sec (default indefinitely)
    
    switch (result){
        case DHTLIB_OK:
            Serial.println("OK");
            break;
        case DHTLIB_ERROR_CHECKSUM:
            Serial.println("Error\n\r\tChecksum error");
            break;
        case DHTLIB_ERROR_ISR_TIMEOUT:
            Serial.println("Error\n\r\tISR time out error");
            break;
        case DHTLIB_ERROR_RESPONSE_TIMEOUT:
            Serial.println("Error\n\r\tResponse time out error");
            break;
        case DHTLIB_ERROR_DATA_TIMEOUT:
            Serial.println("Error\n\r\tData time out error");
            break;
        case DHTLIB_ERROR_ACQUIRING:
            Serial.println("Error\n\r\tAcquiring");
            break;
        case DHTLIB_ERROR_DELTA:
            Serial.println("Error\n\r\tDelta time too small");
            break;
        case DHTLIB_ERROR_NOTSTARTED:
            Serial.println("Error\n\r\tNot started");
            break;        
        default:
            Serial.println("Unkown error");
            break;
    }
    
    Serial.print("Temp:   ");
    Serial.println(DHT.getFahrenheit(), 2);
    Serial.print("Humi:   ");
    Serial.println(DHT.getHumidity(), 2);
    Serial.print("Dew Pt:   ");
    Serial.println(DHT.getDewPoint(), 2);
    Serial.println(Time.timeStr());
    Serial.println();
    
    temp = DHT.getFahrenheit();
    humidity = DHT.getHumidity();
    dew = DHT.getDewPoint();
    Serial.println(humidity);
    humidityD = DHT.getHumidity();
    tempf = DHT.getFahrenheit() * 100;
    tempfD = DHT.getFahrenheit();
    temperatureD = tempfD;
    
    digitalWrite(blue, HIGH);
    Particle.publish("Location", location, PRIVATE); //unit location here
    Particle.publish("Temperature", String(temp), PRIVATE);
    Particle.publish("Humidity", String(humidity), PRIVATE);
    Particle.publish("DewPt", String(dew), PRIVATE);
    delay(500);
    digitalWrite(blue, LOW);
    delay(sampleInt);
}
