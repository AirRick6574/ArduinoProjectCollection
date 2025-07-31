///////////////////////////////////////////
// ULTRASOUND/LEDMATRIX DISTANCE MEASURE //
///////////////////////////////////////////

//03.16.2025
//Erick Ruiz Granados
//Measure Distance and Output to Matrix Led

//Intialize
#include <LedControl.h>
#define TRIG_PIN 3
#define ECHO_PIN 4

LedControl lc = LedControl(11, 13, 10, 1);  // DIN, CLK, CS, 1 device

//Intialize Previous Count Save (Global Scope)
int previous_count = 0;
//Intialize columnstoturnon as global call
int columnsToTurnOn = 0;

/* we always wait a bit between updates of the display */
unsigned long delaytime1=500;
unsigned long delaytime2=50;

//Setup 
void setup() {
    Serial.begin(9600);  // Start Serial Communication

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    
    /*
    The MAX72XX is in power-saving mode on startup,
    we have to do a wakeup call
    */
    lc.shutdown(0, false);
    lc.setIntensity(0, 4); /* Set the brightness to a low values */
    lc.clearDisplay(0); /* and clear the display */

}

//Function Long is used to return a long interger, Will be called upon later
long getDistance() {
    digitalWrite(TRIG_PIN, LOW); //Ensures that the TRIG_PIN (which triggers the ultrasonic pulse) is LOW for 2 microseconds before sending the signal. This is to stabilize the sensor. Low turns off 
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH); //We set the trigger pin to HIGH. The sensor now emits an ultrasonic sound wave.
    delayMicroseconds(10); //We keep the pulse HIGH for 10 microseconds. This ensures the sensor has enough time to send the ultrasonic wave
    digitalWrite(TRIG_PIN, LOW); //After 10 microseconds, we set the TRIG_PIN back to LOW
    return pulseIn(ECHO_PIN, HIGH) * 0.034 / 2;
    //The ECHO_PIN is the pin where the sensor receives the reflected sound wave.
    //pulseIn(ECHO_PIN, HIGH) waits until the echo signal returns and measures how long it was HIGH.
    //That time is then used to calculate the distance:
    //Speed of sound = 0.034 cm/µs
    //We divide by 2 because the sound traveled to the object and back.

}

void turnOnColumns(int columns) //Creates function with conditional that will turn on columns
{

    if(columnsToTurnOn < previous_count) //Will check if new columns count is less than previous and will set more lights off to reach new count 
    {
      for (int col = previous_count - 1; col >= columns; --col)  //Loop thru columns
      {
        delay(50); // Delay for updating each row to create a smoother transition
        for (int row = 0; row < 8; row++)  //Loop thru Rows
        {
            lc.setLed(0, row, col, false); //Turn on LEDs at row and columns
            previous_count = columnsToTurnOn;
        }
      } 
    }

    if(columnsToTurnOn > previous_count) //Will check if new columns count is less than previous and will set more lights on to reach new count 
    {
      for (int col = 0; col < columns; col++)  //Loop thru columns
        {
          delay(50); //Delay between updating distance
          for (int row = 0; row < 8; row++)  //Loop thru Rows
          {
              lc.setLed(0, row, col, true); //Turn on LEDs at row and columns
              previous_count = columnsToTurnOn;
          }
        } 
    }
}

void loop() {
    long distance = getDistance(); //Calls function get distance and creates long interger variable

    if (distance < 5) {  // If object is very near, turn on all LEDs. If object is less than 5 cm, turn on all leds
        turnOnColumns(8); //Calls upon turn on column with condition 8 saying to turn on all 8 columns
    } else {
        columnsToTurnOn = map(distance, 5, 40, 8, 1);  // More columns turn on as object gets closer.... 
        //Converts the distance (5 cm to 40 cm) into a range (8 columns to 1 column).
        //When the object is close (5 cm) → 8 columns ON.
        //When the object is far (40 cm) → 1 column ON.

        columnsToTurnOn = constrain(columnsToTurnOn, 1, 8); //Ensures that the number of columns is always between 1 and 8 (to avoid errors).
        turnOnColumns(columnsToTurnOn); //Calls the function to update the LED display.
    }


}
