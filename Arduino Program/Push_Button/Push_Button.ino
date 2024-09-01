#include <TM1637Display.h>

int Timer_CLK = 3;
int Timer_DIO = 2;
int Temp_CLK = 1;
int Temp_DIO = 0;

int Timer_Btn_plus = 8;
int Timer_Btn_minus = 9;
int Temp_Btn_plus = 6;
int Temp_Btn_minus = 7;
int Timer_Btn_off = 5;

int Temp = 25;
int Time_min = 0;
int Time_hr = 0;

TM1637Display Time_display(Timer_CLK, Timer_DIO);
TM1637Display Temp_display(Temp_CLK, Temp_DIO);


void setup()
{
  Time_display.setBrightness(1);
  Temp_display.setBrightness(1);
  pinMode(Timer_Btn_plus,INPUT);
  pinMode(Timer_Btn_minus,INPUT);
  pinMode(Temp_Btn_plus,INPUT);
  pinMode(Temp_Btn_minus,INPUT);
  
}

void loop()
{

  //display.clear();
  
  int Timer_plus = digitalRead(Timer_Btn_plus);
  int Timer_minus = digitalRead(Timer_Btn_minus);
  int Timer_off = digitalRead(Timer_Btn_off);

  int Temp_plus = digitalRead(Temp_Btn_plus);
  int Temp_minus = digitalRead(Temp_Btn_minus);

  Temp_display.showNumberDec(Temp,false);
  // Time_display.showNumberDec(Time_min+Time_hr*100,false);

  if ( Temp_minus == 1){
    Temp = Temp - 5;
    Temp_display.showNumberDec(Temp,false);
    delay(1000); // Wait for 1000 millisecond(s)
  }

  if ( Temp_plus == 1){
    Temp = Temp + 5;
    Temp_display.showNumberDec(Temp,false);
    delay(1000); // Wait for 1000 millisecond(s)
  }
  
  if ( Timer_plus == 1){
    Time_min = Time_min + 5;
    if (Time_min >= 60){
      Time_hr = Time_hr+1;
      Time_min = 0;
      delay(200); // Wait for 1000 millisecond(s)
    }
    Time_display.showNumberDec(Time_min+Time_hr*100,false);
    }
  // if ( Timer_minus == 1){
  //   Time_min = Time_min - 5;
  //   if (Time_min < 0){
  //     if (Time_hr <= 0){
  //       Time_min = 0;
  //       Time_hr = 0;
  //     }else{
  //       Time_hr = Time_hr - 1;
  //       Time_min = 55;
  //     }
  //     delay(1000); // Wait for 1000 millisecond(s)
  //   }
  //   Time_display.showNumberDec(Time_min+Time_hr*100,false);
  //   }

  if ( Timer_off == 1) {
    uint8_t dd[] = {0x0,0x3f,0x71,0x71}; // off
    Time_display.setSegments(dd);
    delay(1100); // Wait for 1000 millisecond(s)
  }
  
}


