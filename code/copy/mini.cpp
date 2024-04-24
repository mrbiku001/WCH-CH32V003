#include <XGZP6897D.h>
/*
   K value for XGZP6897D. It depend on the pressure range of the sensor.
   Table found in the data sheet from CFSensor.com
    https://cfsensor.com/product-category/i2c-sensor/https://cfsensor.com/product-category/i2c-sensor/
  pressure_range (kPa)   K value
  131<P≤260               32
  65<P≤131                64
  32<P≤65                 128
  16<P≤32                 256
  8<P≤16                  512
  4<P≤8                   1024
  2≤P≤4                   2048
  1≤P<2                   4096
  P<1                     8192
  the K value is selected according to the positive pressure value only,
  like -100～100kPa,the K value is 64.
*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16
static const unsigned char PROGMEM logo_bmp[] = {0b00000000, 0b11000000,
                                                 0b00000001, 0b11000000,
                                                 0b00000001, 0b11000000,
                                                 0b00000011, 0b11100000,
                                                 0b11110011, 0b11100000,
                                                 0b11111110, 0b11111000,
                                                 0b01111110, 0b11111111,
                                                 0b00110011, 0b10011111,
                                                 0b00011111, 0b11111100,
                                                 0b00001101, 0b01110000,
                                                 0b00011011, 0b10100000,
                                                 0b00111111, 0b11100000,
                                                 0b00111111, 0b11110000,
                                                 0b01111100, 0b11110000,
                                                 0b01110000, 0b01110000,
                                                 0b00000000, 0b00110000};

// K value for a XGZP6897D  -1000-1000Pa
#define K 512 // see table above for the correct value for your sensor, according to the sensitivity.

// create the sensor object, passing the correct K value.
XGZP6897D mysensor(K);
float pressure, temperature, pressure_cmofH2O;
void setup()
{
  if (!mysensor.begin())
  {
    Serial.println("Device not responding.");
    while (true)
      delay(10);
  }
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();
}

void loop()
{
  // read the temperature (in °Celsius), and the pressure (in Pa)
  mysensor.readSensor(temperature, pressure);
  pressure_cmofH2O = pressure / 98.0665;
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Pressure");

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.println(pressure_cmofH2O);
  display.println("cm of H2O");

  display.display();
}
