#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

int Voltage;
int Switch;
int SwitchState = 0;
bool SwitchBool = true;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT); 
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
}

void loop() {
Switch = digitalRead(2);

if(Switch == LOW && SwitchState == 0 && SwitchBool == true) {
SwitchState = 1;
SwitchBool = false;

digitalWrite(3, HIGH);
digitalWrite(5, LOW);
digitalWrite(6, LOW);

} else if(Switch == LOW && SwitchState == 1 && SwitchBool == true) {
SwitchState = 2;
SwitchBool = false;

digitalWrite(3, HIGH);
digitalWrite(5, HIGH);
digitalWrite(6, HIGH);
} else if(Switch == LOW && SwitchState == 2 && SwitchBool == true) {
SwitchState = 0;
SwitchBool = false;

digitalWrite(3, LOW);
digitalWrite(5, LOW);
digitalWrite(6, LOW);
} else if(Switch == HIGH) {
  SwitchBool = true;
  analogWrite(9, 0);
  
digitalWrite(3, LOW);
digitalWrite(5, LOW);
digitalWrite(6, LOW);
}
if(Switch == LOW) {
  Clock();
}
}

void Clock() {
  tmElements_t tm;
  
  if (RTC.read(tm)) {
  int Minutes = (tm.Hour * 60) + tm.Minute;
    
  int AM = map(Minutes, 0, 719, 0, 255);
  int PM = map(Minutes, 720, 1439, 0, 255);

if(tm.Hour > 0 && tm.Hour < 13) {
  Voltage = AM;
} else {
  Voltage = PM;
}
  analogWrite(9, Voltage);
}
}
