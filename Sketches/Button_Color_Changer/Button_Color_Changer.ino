/// Color Changer with Beeping Feature using buttons and active buzzer 

int buzzer = 12;// pin for active buzzer
int red_led = 5; //pin for red led
int button_br = 9; //pin for button that will make led brighter 
int button_dm = 8;//pin for button that will make led dimmer
int i=0;
int color_settings[] = {50, 100, 150, 200, 250}; //color settings for i to use. 

void setup() 
{
  pinMode(red_led, OUTPUT); //Sets up light as output
  pinMode(buzzer, OUTPUT); //sets up buzzer as output
  pinMode(button_br, INPUT_PULLUP); //intial dimmer button as input to send to arduino (WILL BE AND START AT HIGH UNLESS PRESS WHICH WILL RESULT IN BUTTON BECOMING LOW POWER)
  pinMode(button_dm, INPUT_PULLUP); //intial dimmer button as input to send to arduino (WILL BE AND START AT HIGH UNLESS PRESS WHICH WILL RESULT IN BUTTON BECOMING LOW POWER)
 
}



void loop() 
{
  int sound_duration = 100; //Intialize beeper with minimal buzz
  

  //Button press will increase i by 1 
  if (digitalRead(button_br) == LOW) 
  {
    i=i+1;
    
    if (i==6)//Does check to prevent i from going higher than 5, will beep and then break if statement
    {
      i=5;
      
    }

    analogWrite(red_led,color_settings[i-1]);
    for (int count=0; count<i; count++)
    {
      //Program will make repreated beep based on count of I
      digitalWrite(buzzer,HIGH); //Sets buzzer to ON
      delay(sound_duration);
      digitalWrite(buzzer, LOW);//will deactivate the buzzer by setting power to low
      delay(sound_duration);
    }
    
  }

  //Button press will DECREASE i by 1 
  if (digitalRead(button_dm) == LOW) 
  {
    i=i-1;
    if (i==0)//Does check to prevent i from going higher than 1, will beep and then break if statement
    {
      i=1;
    }
    
    analogWrite(red_led,color_settings[i-1]);
    for (int count=0; count<i; count++)//Program will do a for loop for how long to beep based off of i count. (Will beep based on setting)
    {
      //Program will make repreated beep based on count of I
      digitalWrite(buzzer,HIGH); //Sets buzzer to ON
      delay(sound_duration);
      digitalWrite(buzzer, LOW);//will deactivate the buzzer by setting power to low
      delay(sound_duration);
    }

  }
  
  
  
}
