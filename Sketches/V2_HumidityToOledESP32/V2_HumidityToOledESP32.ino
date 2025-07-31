//Tech Trends Shameer
//Temperature and Humidity Display in OLED
//----------------------------------------------------------------------------------------------------------Intilization----------------------------------
#include <Wire.h> // For I2C communication (used by OLED)
#include <Adafruit_GFX.h>  // Core graphics library
#include <Adafruit_SSD1306.h>  
#include <Adafruit_Sensor.h>
#include "DHT.h"

#define DHTPIN 14 // or any available digital GPIO pin //ESP32

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1 // Define the reset pin for OLED (not actually used in this setup, but needed by the library) ESP32
//Adafruit_SH1106 display(OLED_RESET);

int var_num = 0;
char buffer[10];

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);  


#define BLUE 0x001F // Optional color definition (not used, because the OLED is monochrome)

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE); // Create a DHT sensor object

//----------------------------------------------------------------------------------------------------------Setup FUNCTION----------------------------------
void setup() {
  Wire.begin(21, 22); // SDA, SCL for ESP32
  Serial.begin(9600); //ESP32

  dht.begin(); // Initialize the DHT sensor using dht object class                                                                                // display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize the OLED display with I2C address 0x3C 

  delay(2000);

  display.clearDisplay(); // Clear anything that might be on the screen
  display.setTextColor(SSD1306_WHITE); // Set text color to white (since OLED is monochrome) (doesnt really matter but is standard)
 //  display.setTextColor(BLUE);
}

//----------------------------------------------------------------------------------------------------------COUNT FUNCTION----------------------------------
void count_change() {
  if (var_num == 60)
  {
    var_num = 0;
  }
  var_num = var_num + 1; // for itoa (	The number base (10 = decimal, 16 = hex, 2 = binary, etc.) )
  itoa(var_num, buffer, 10);//function included by c++ that converts int to str. converts from int to array (buffer is my array). C++ can only hold one variable (1 or 2 or 3 instead of 123) while arrays holds them all seperatly and combines 
  delay(1000);//delay 1 second
}


//----------------------------------------------------------------------------------------------------------SETUP FUNCTION----------------------------------
void loop() {
  delay(500);

  //read temperature and humidity
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  
  // Check if reading failed (sometimes DHT sensors fail to communicate)
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  
  Serial.println(t);
  Serial.println(h);
  
  display.clearDisplay(); //clear display

  // display intialization
  display.setTextSize(1); // Set text size to small
  display.setCursor(30,7); // Move cursor to (x=0, y=7) pixels

  // display temperature   //display.setTextColor(BLUE);
  display.print("Temperature: ");

  // display intialization (Changed location)
  display.setTextSize(2); // Make temperature reading larger
  display.setCursor(30,16);// Move cursor to (x=0, y=16)
  display.print(t); // Display the temperature value
  display.print(" "); // Add a space

  // display intialization (Changed location)
  display.setTextSize(1);   // Small text size for the degree symbol
  display.cp437(true); // Use extended characters set
  display.write(167);  // Write degree symbol (ASCII code 167)

  // display intialization (Changed location)
  display.setTextSize(2);
  display.print("C");
  
  // display humidity
  display.setTextSize(1);
  display.setCursor(30, 37);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.setCursor(30, 50);
  display.print(h);
  display.print(" %"); 
  

  //Display Counter 
  count_change();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(buffer);

  display.display();   // Actually display all the data on the OLED screen
}