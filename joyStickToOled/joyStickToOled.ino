#include <Wire.h> // For I2C communication (used by OLED)
#include <Adafruit_GFX.h>  // Core graphics library
#include <Adafruit_SSD1306.h>  
#include <Adafruit_Sensor.h>

//-----------------------------------IMPORTANT INFO------------------------------------------
/*
Font name: glcdfont.c

Each character is:

5 pixels wide

+ 1 pixel of spacing

= 6 pixels total width per character

8 pixels tall
*/

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET 4 // Define the reset pin for OLED (not actually used in this setup, but needed by the library)
//Adafruit_SH1106 display(OLED_RESET);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);  

#define BLUE 0x001F // Optional color definition (not used, because the OLED is monochrome)

//Analog Intializations
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

//Position_Translate intialization
int current_pos_x = 0;
int current_pos_y = 0;
int in_pos;

//BOX POSITION CALCULATOR
int word_POS_X = 5;
int word_POS_Y = 32;
int characterCount = 7;


void setup() {
 
  Serial.begin(9600);
 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize the OLED display with I2C address 0x3C 

  delay(2000);

  display.clearDisplay(); // Clear anything that might be on the screen
  display.setTextColor(SSD1306_WHITE); // Set text color to white (since OLED is monochrome) (doesnt really matter but is standard)
  //  display.setTextColor(BLUE);
  
  //Sets up sinmode as input
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);


}

void update_Cursor_PosAndCheckForButtonPress() {
  current_pos_x = constrain((analogRead(X_pin) * 128) / 1024, 0, 122);
  current_pos_y = constrain((analogRead(Y_pin) * 64) / 1024, 0, 56);
  delay(25);

  
  display.setTextSize(1); // Set text size to small
  display.setCursor(current_pos_x,current_pos_y); // Move cursor to (x=0, y=7) pixels
  display.print("^");

  checkIfHovering();
  
  newScreen();
  
}

void newScreen() {
  if (digitalRead(SW_pin) == 0 && in_pos == true){
    display.clearDisplay(); //clear display
    display.setTextColor(SSD1306_WHITE); // Set text color to white (since OLED is monochrome) (doesnt really matter but is standard)

    display.setTextSize(1); // Set text size to small
    display.setCursor(40,32); 

    for (int i = 0; i < 3; i++){
      display.print(i+1);
      display.display();   // Actually display all the data on the OLED screen
      delay(1000);
      display.clearDisplay(); //clear display
    } 
  }
}

void checkIfHovering() { //cursor will be in top left corner of word
  int textWidth = characterCount * 6; // 6 pixels per character
  int textHeight = 8; // pixels tall

  if (current_pos_x >= word_POS_X && //curent position is greater than or equal to x(5)
      current_pos_y+5 > word_POS_Y && //current position is greater than 32
      current_pos_x <= (word_POS_X + textWidth) && //current position is greater than or equal to x(5) * character count(7) + spacingPerWord(5)
      current_pos_y < (word_POS_Y + textHeight)) //current position is less than y(32) - 8
      {
    in_pos = true;

    display.fillRect(word_POS_X-5, word_POS_Y-5, (word_POS_X * characterCount + (word_POS_X)) + 5, (word_POS_Y + textHeight) + 2, SSD1306_WHITE);

    display.setTextColor(SSD1306_BLACK); // Invert text
    display.setCursor(word_POS_X, word_POS_Y); 
    display.print("PENIS!!");
  }

}

//display.setCursor(5, 32);

void loop() {
  in_pos = false;
  
  display.clearDisplay(); //clear display
  display.setTextColor(SSD1306_WHITE); // Set text color to white (since OLED is monochrome) (doesnt really matter but is standard)

  display.setTextSize(1); // Set text size to small
  display.setCursor(word_POS_X, word_POS_Y); 
  display.print("PENIS!!");

  update_Cursor_PosAndCheckForButtonPress();
 
  
 
 display.display();   // Actually display all the data on the OLED screen
}
