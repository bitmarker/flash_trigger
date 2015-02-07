#include "flash_timers.h"
#include "math.h"

#define RELAIS_PIN  40
#define EARTH_G 9.80665

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete


void _printf(const char * format, ...)
{
  char buffer[200];
  va_list argptr;
  va_start(argptr, format);
  vsnprintf (buffer, 255, format, argptr);
  va_end(argptr);
  Serial.print(buffer);
}



void trigger_flash()
{
    digitalWrite(RELAIS_PIN, 1);
    delay(1);
    digitalWrite(RELAIS_PIN, 0);
    _printf("x");
}


void setup() {

  pinMode(RELAIS_PIN, OUTPUT);


  pinMode(41, INPUT);


  Serial.begin(9600);
  inputString.reserve(200);

  FlashTimers_Init();
  FlashTimers_SetCallback(trigger_flash);
  FlashTimers_SetDeadTime(200);
}

void loop() {
  bool state = digitalRead(41);

  if (state)
  {
    int height = 100; // cm
    
    int fall_time = (int) (sqrt(2 * height / EARTH_G / 100.0) * 1000);

    FlashTimers_AddTimer(fall_time);
  }
  
  FlashTimers_Idle();
  
  
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString); 
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  

  delay(1);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}
