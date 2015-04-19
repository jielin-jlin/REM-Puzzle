#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);
int currenthour,currentminute,seconds,alarmhour,alarmminute,temphour,tempminute;
boolean time;
char *input="Current Time:";
int remcounter;
int state=1;
boolean alarm;
void setup()
{
  time=false;
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(13,OUTPUT);
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Current Time:");
  lcd.setCursor(0,1);
  lcd.print(currenthour);
  lcd.print(":");
  lcd.print(currentminute);
  currenthour=0;
  currentminute=0;
  seconds=0;
  remcounter=0;
  alarm=false;
  randomSeed(analogRead(0));
  
}
void puzzle()
{
  int randomnum=random(21);
  int torand=0;
  boolean solve=false;
  while(solve==false)
  {
    if(digitalRead(8)==LOW)
      torand++;
    else if(digitalRead(9)==LOW)
      torand--;
    else if(digitalRead(7)==LOW)
    {
      if(torand==randomnum)
      {
        solve=true;
        
      }
    }
    lcd.clear();
    lcd.print("Enter Number: ");
    lcd.print(randomnum);
    lcd.setCursor(0,1);
    lcd.print(torand);
    delay(300);
  }
}
void loop()
{
  lcd.clear();
  if(state==1)
  {
    if(digitalRead(7)==LOW)
    {
      input="Alarm Time:";
      state=2;
      delay(1000);
      
    }
    else if(digitalRead(8)==LOW)
    {
      currenthour++;
      if(currenthour==24)
        currenthour=0;
    }
    else if(digitalRead(9)==LOW)
    {
      currentminute++;
      if(currentminute==60)
        currentminute=0;
    }
    lcd.print(input);
    lcd.setCursor(0,1);
    lcd.print(currenthour);
    lcd.print(":");
    lcd.print(currentminute);
    delay(300);
  }
  else if(state==2)
  {
    if(digitalRead(7)==LOW)
    {
      input="Alarm On: ";
      temphour=currenthour;
      tempminute=currentminute;
      while(time==false)
      {
        remcounter++;
        if(temphour==alarmhour)
          time=true;
        tempminute=tempminute+30;
        if(tempminute>59)
        {
          temphour++;
          if(temphour==24)
            temphour=0;
          if(temphour==alarmhour)
          time=true;
          tempminute=(60-tempminute)*-1;
        }
        temphour++;
        if(temphour==24)
          temphour=0;
        if(temphour==alarmhour)
          time=true;
        if(time)
        {
          if(remcounter==1)
          {
            state=4;
            break;
          }
          if(temphour>alarmhour)
          {
            tempminute=tempminute-30;
            if(tempminute<0)
            {
              tempminute=60+tempminute;
              temphour--;
              if(temphour==-1)
              temphour=23;
            }
            temphour--;
            if(temphour==-1)
              temphour=23;
          }
          else if(tempminute>alarmminute)
          {
            tempminute=tempminute-30;
            if(tempminute<0)
            {
              tempminute=60+tempminute;
              temphour--;
              if(temphour==-1)
              temphour=23;
            }
            temphour--;
            if(temphour==-1)
              temphour=23;
          }
          alarmhour = temphour;
          alarmminute=tempminute;
          state=3;
          lcd.clear();
          lcd.print("Alarm Set For:");
          lcd.setCursor(0,1);
          lcd.print(alarmhour);
          lcd.print(":");
          lcd.print(alarmminute);
          delay(3000);
        } 
      }
      delay(1000);
    }
    else if(digitalRead(8)==LOW)
    {
      alarmhour++;
      if(alarmhour==24)
        alarmhour=0;
    }
    else if(digitalRead(9)==LOW)
    {
      alarmminute++;
      if(alarmminute==60)
        alarmminute=0;
    }
    lcd.print(input);
    lcd.setCursor(0,1);
    lcd.print(alarmhour);
    lcd.print(":");
    lcd.print(alarmminute);
    delay(300);
  }
  else
  {
    seconds++;
    if(seconds==60)
    {
      currentminute++;
      seconds=0;
    }
    if(currentminute==60)
    {
      currenthour++;
      currentminute=0;
    }
    if(currenthour==24)
      currenthour=0;
    if(currenthour==alarmhour)
    {
      if(currentminute==alarmminute)
      {
        if(alarm==false)
          state=4;
      }
    }
    if(state==4)
    {
      tone(13,1200);
      lcd.clear();
      lcd.print("Try this out...");
      delay(3000);
      random(21);
      puzzle();
      lcd.clear();
      lcd.print("Keep going...");
      delay(3000);
      puzzle();
      lcd.clear();
      lcd.print("One more...");
      delay(3000);
      puzzle();
      noTone(13);
      lcd.clear();
      lcd.print("Brush your teeth");
      lcd.setCursor(0,1);
      lcd.print("Wash your face");
      state=3;
      alarm=true;
      delay(5000);
      lcd.clear();
    }
    lcd.print(input);
    lcd.print(alarmhour);
    lcd.print(":");
    lcd.print(alarmminute);
    lcd.setCursor(0,1);
    lcd.print(currenthour);
    lcd.print(":");
    lcd.print(currentminute);
    lcd.print(":");
    lcd.print(seconds);
    delay(1000);
  }
  
}
