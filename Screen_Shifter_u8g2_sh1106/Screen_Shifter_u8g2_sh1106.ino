#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); //Got from u8g2 documentation

int var = 15;
int v704 = 0; //checker to see whether or not program must go down or up. using travis line :p used as t or f. could have also used boolan but this is fun

void setup(void) 
{
  u8g2.begin();
  Serial.begin(9600); //Binds seral output to connection 9600 Baud
}

void loop(void)
{
  u8g2.firstPage();
  do 
  { 
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(10,var,"I like Penis"); //draw string fucntion, x, y, str,
    
    if (var == 14)
    {v704 = 0; }//Go reverse
    else if (var == 64)
    { v704 = 1;}

    if (v704 == 0)
    { var = var + 1;}
    else if (v704 == 1)
    {var = var - 1;}
    
    delay(25);
    Serial.println(var); //Print function
  }while ( u8g2.nextPage() ); //use do while program to refresh screen basically do this then check while is true. like do the shopping, while it is below 5 pm

}