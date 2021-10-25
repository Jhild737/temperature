#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6

#define DHTPIN 2 
#define LED_PIN     6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  16

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50 // Digital pin connected to the DHT sensor 

#define DHTTYPE    DHT11     
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

DHT dht(DHTPIN, DHTTYPE);

uint32_t delayMS = 2000;

float temperature, humidity;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  dht.begin();
  

  

}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void loop() {
  colorWipe(strip.Color(255,   0,   0, 50)     , 50); // Red
  delay(delayMS);

  temperature = dht.readTemperature(true);
  float h = dht.readHumidity();
  humidity = h;
  // Get temperature event and print its value.

  if (isnan(h) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  else {
    Serial.print(F("Temperature: "));
    lcd.clear();
    lcd.print(F("Temp: "));
    lcd.print(temperature);
    lcd.print(F("F"));
    lcd.setCursor(0,1);
    
    Serial.print(temperature);
    Serial.println(F("°F"));
    Serial.print(F("Humidity: "));
    Serial.print(humidity);
    Serial.println("%");
    lcd.print(F("Humidity: "));
    lcd.print(humidity);
    lcd.print(F("%"));

  }

  

}
