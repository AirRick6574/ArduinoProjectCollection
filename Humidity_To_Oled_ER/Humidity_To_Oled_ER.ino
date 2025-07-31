#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11 //Kinda acts like a variable, basically replacing any thing with said keyword with its assigned variable 
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE ); //Object being created that used said keyword

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); //Got from u8g2 documentation


void setup() {
  Serial.begin( 9600);
  u8g2.begin();  // <-- Needed to initialize the OLED
}



static bool measure_environment( float *temperature, float *humidity ) //Function which collects humidity and temperature when called
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 2000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}

void loop(void) {
  // put your main code here, to run repeatedly:
  float temperature;
  float humidity;

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */

  u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(10, 25, "Waiting...");
    } while (u8g2.nextPage());
     
  if( measure_environment( &temperature, &humidity ) == true )
  {

    //Combines messages Since drawstr can use only one variable
    char TemperatureMsg[32];  // allocate enough space for your message 
    char HumidityMsg[32];  // allocate enough space for your message

    sprintf(TemperatureMsg, "Temp: %.1f C", temperature);  // format string + variable. Weird Expression is how variable is expressed (%.1f = one decimal place) (%% = prints a literal percent sign)
    sprintf(HumidityMsg, "Humidity:  %.1f %% ", humidity);  // format string + variable


    u8g2.firstPage();
      do 
      { 
        u8g2.setFont(u8g2_font_ncenB14_tr);
        u8g2.drawStr(10,25,TemperatureMsg); //draw string fucntion, x, y, str,
        u8g2.drawStr(10,50,HumidityMsg); //draw string fucntion, x, y, str,

        
      }while ( u8g2.nextPage() ); //use do while program to refresh screen basically do this then check while is true. like do the shopping, while it is below 5 pm
  }

}
