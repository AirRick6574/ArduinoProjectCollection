// Define Pins
#define BLUE 3
#define GREEN 5
#define RED 6

void setup() 
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  

}

// define variables
int redValue;
int greenValue;
int blueValue;

void loop() 
{
  redValue = 15; // choose a value between 1 and 255 to change the color.
  greenValue = 166;
  blueValue = 156;

  analogWrite(RED, redValue);
  analogWrite(GREEN, greenValue);
  analogWrite(BLUE, blueValue);

}
