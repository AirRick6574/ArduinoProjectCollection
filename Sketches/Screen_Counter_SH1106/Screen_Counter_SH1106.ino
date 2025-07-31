#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); //Got from u8g2 documentation
int var_num = 0;
char buffer[10];

void setup() {
  u8g2.begin();
  Serial.begin(9600); //Binds seral output to connection 9600 Baud
}

void count_change() {
  var_num = var_num + 1; // for itoa (	The number base (10 = decimal, 16 = hex, 2 = binary, etc.) )
  itoa(var_num, buffer, 10);//function included by c++ that converts int to str. converts from int to array (buffer is my array). C++ can only hold one variable (1 or 2 or 3 instead of 123) while arrays holds them all seperatly and combines 
  delay(1000);//delay 1 second
}

void loop() {
  // put your main code here, to run repeatedly:
  u8g2.firstPage();
    do 
    { 
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(64,32,buffer); //draw string fucntion, x, y, str,
      count_change();
  }while ( u8g2.nextPage() ); //use do while program to refresh screen basically do this then check while is true. like do the shopping, while it is below 5 pm
}

//Do this for cool ass flicking/flashing char* var = '1'; // diference between "" and '' is important. using '' is trying to read in ascII
//char* var = "1"; // diference between "" and '' is important
