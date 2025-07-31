//This is for active buzzer, not using PWM 

int buzzer = 12;//the pin of the active buzzer

void setup() 
{
  pinMode(buzzer, OUTPUT); //initialize the buzzer pin as an output
}

void loop() 
{
  // put your main code here, to run repeatedly:
  int sound_duration = 500; //Sound duration 

  //activate the active buzzer
  digitalWrite(buzzer, HIGH);
  delay(sound_duration);//uses sound_duration as variable to set time limit delay in ms

  digitalWrite(buzzer, LOW);//will deactivate the buzzer by setting power to low
  delay(sound_duration);//wait for sound_duration ms
}
