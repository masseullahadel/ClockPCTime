#include <Time.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int switchState = 0;
boolean turnOffAlarm = false;

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(10, OUTPUT);
  pinMode(8, OUTPUT);
}

void  loop(){
  getPCTime();
  digitalClockDisplay();
  switchState = digitalRead(9);


  if(second() >= 20 && switchState == LOW && turnOffAlarm == false){
    tone(13,262);
    digitalWrite(10, HIGH);
  }
  else if(switchState == HIGH){
    noTone(13);
    digitalWrite(10, LOW);
    turnOffAlarm = true;
  }
}
void getPCTime() {
  
  while(Serial.available()){  // time message consists of a header and ten ascii digits 
    unsigned long pctime;  
    if(Serial.read() == 'T') {  
      pctime = Serial.parseInt();
    }
    setTime(pctime);
  }
}
void digitalClockDisplay(){
  // digital clock display of the time
  long hours;
  if(hour() > 12)
    hours = hour() - 12;
  else
    hours = hour();
  lcd.setCursor(0,0);
  lcd.print(dayShortStr(weekday()));
  lcd.print(" ");
  lcd.print(monthShortStr(month()));
  lcd.print(" ");
  lcd.print(day());
  lcd.print(" ");
  lcd.print(year());
  lcd.setCursor(0,1);
  lcd.print(hours);
  printDigits(minute());
  printDigits(second());
  lcd.print(" ");
  if(isAM())
    lcd.print("AM");
  else
    lcd.print("PM");
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  lcd.print(":");
  if(digits < 10)
    lcd.print('0');
  lcd.print(digits);
}

