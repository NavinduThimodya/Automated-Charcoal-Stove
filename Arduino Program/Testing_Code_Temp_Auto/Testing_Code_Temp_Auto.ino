#include <TM1637Display.h>

/// Time Counters ////////
float sec_count = 0.0;
int min_count = 0;
int hr_count = 0;
/////////////////////////

int mode_1 = A1;
int mode_2 = A2;
int mode_3 = A3;
int mode_4 = A4;
int mode_5 = A5;
int MODE_changer = 12;


int Timer_CLK = 3;
int Timer_DIO = 2;
int Temp_CLK = 1;
int Temp_DIO = 0;

int Timer_Btn_plus = 6;
int Timer_Btn_minus = 5;
int Temp_Btn_plus = 8;
int Temp_Btn_minus = 7;
int Timer_Btn_off = 4;

int cooler_motor = 9;
int heat_motor = 10;

int Time_min = 9;
int Time_hr = 0;

TM1637Display Time_display(Timer_CLK, Timer_DIO);
TM1637Display Temp_display(Temp_CLK, Temp_DIO);

int Mode_pos = 0;

int Display_Temp = 40;
int Uppper_Temp;
int Lower_Temp;

/// Status Variables
bool istimeroff = true;
bool isStoveOn = true;

// For time counting
int Blinking_pos = 0;

int Temp = 30;
float Tmp = Temp*1.0;

void setup()
{
  Time_display.setBrightness(1);
  Temp_display.setBrightness(1);
  pinMode(Timer_Btn_plus,INPUT);
  pinMode(Timer_Btn_minus,INPUT);
  pinMode(Temp_Btn_plus,INPUT);
  pinMode(Temp_Btn_minus,INPUT);

  pinMode(MODE_changer,INPUT);
  pinMode(mode_1,OUTPUT);
  pinMode(mode_2,OUTPUT);
  pinMode(mode_3,OUTPUT);
  pinMode(mode_4,OUTPUT);
  pinMode(mode_5,OUTPUT);

  digitalWrite(mode_1,HIGH);// Manual
  digitalWrite(mode_2,LOW);// cook
  digitalWrite(mode_3,LOW);// Hot pot
  digitalWrite(mode_4,LOW);// Fry
  digitalWrite(mode_5,LOW);// Boil
  
}

void loop()
{  
  int Timer_plus = digitalRead(Timer_Btn_plus);
  int Timer_minus = digitalRead(Timer_Btn_minus);
  int Timer_off = digitalRead(Timer_Btn_off);

  int Temp_plus = digitalRead(Temp_Btn_plus);
  int Temp_minus = digitalRead(Temp_Btn_minus);

  int Mode_change = digitalRead(MODE_changer);
 

  // Temperature Regulator ////// 
  if (Temp >= (Display_Temp + 5)){
    // Cool the stove
    if (isStoveOn){
      analogWrite(cooler_motor,255);
      analogWrite(heat_motor,0);
      Tmp = Tmp - 0.05;
    }

  }else if (Temp <= (Display_Temp - 5)){
    // Heat up the stove
    if (isStoveOn){
      analogWrite(cooler_motor,0);
      analogWrite(heat_motor,255);
      Tmp = Tmp + 0.05;
    }
  }else{
    // Constant fan rpm
    if (isStoveOn){
      if (Temp > Display_Temp){
        analogWrite(cooler_motor,(Temp - Display_Temp)*51);
        Tmp = Tmp - (Temp - Display_Temp) * 0.005;
      }else if (Temp < Display_Temp){
        analogWrite(heat_motor,(Display_Temp - Temp)*51);
        Tmp = Tmp + (Display_Temp - Temp) * 0.005;
      }else{
        //In Threshold Value
        if ((Temp - Tmp)>5.0){
          Tmp = random((Display_Temp-4),Display_Temp);
        }else{
          Tmp = random(Display_Temp,(Display_Temp+4));
        }
        
        }
      }

  }
  /////////////////////////////


  // Modes Configurations //////

  /////////////////////////////////////////////// Manual ///////////////////////////////////////////////
  if (Mode_pos == 0){
    if (istimeroff){
      uint8_t dd[] = {0x0,0x3f,0x71,0x71}; // off
      Time_display.setSegments(dd);
    }else{
      Time_display.showNumberDec(Time_min+1+Time_hr*100,true);
    }
    if (isStoveOn){
      Temp_display.showNumberDec(Display_Temp,false);
    }else{
      uint8_t dd[] = {0x0,0x3f,0x71,0x71}; // off
      Temp_display.setSegments(dd);
    }
  }
  ///////////////////////////////////////////// Cook ///////////////////////////////////////////////////
  if (Mode_pos == 1){
    if (istimeroff){
      uint8_t dd[] = {0x0,0x3f,0x71,0x71}; // off
      Time_display.setSegments(dd);
    }else{
      // set time
      //Time_min = 
      //Time_hr = 
      Time_display.showNumberDec(Time_min+1+Time_hr*100,true);
    }
    if (isStoveOn){
      uint8_t ddx1[] = {0x0,0x76,0x6,0x0}; // H 1
      Temp_display.setSegments(ddx1);
    }else{
      uint8_t dd[] = {0x0,0x3f,0x71,0x71}; // off
      Temp_display.setSegments(dd);
    }
  }
    //////////////////////////////////////////// Hot Pot ///////////////////////////////////////////////
  if (Mode_pos == 2){
    if (istimeroff){
      uint8_t dd[] = {0x0,0x3f,0x71,0x71}; // off
      Time_display.setSegments(dd);
    }else{
      // set time
      //Time_min = 
      //Time_hr = 
      Time_display.showNumberDec(Time_min+1+Time_hr*100,true);
    }
    if (isStoveOn){
      uint8_t ddx1[] = {0x0,0x76,0x5b,0x0}; // H 2
      Temp_display.setSegments(ddx1);
    }else{
      uint8_t dd[] = {0x0,0x3f,0x71,0x71}; // off
      Temp_display.setSegments(dd);
    }
  }
    ///////////////////////////////////////////// Fry //////////////////////////////////////////////////
  if (Mode_pos == 3){
    if (istimeroff){
      uint8_t dd[] = {0x0,0x3f,0x71,0x71}; // off
      Time_display.setSegments(dd);
    }else{
      // set time
      //Time_min = 
      //Time_hr = 
      Time_display.showNumberDec(Time_min+1+Time_hr*100,true);
    }
    if (isStoveOn){
      uint8_t ddx1[] = {0x0,0x76,0x4f,0x0}; // H 3
      Temp_display.setSegments(ddx1);
    }else{
      uint8_t dd[] = {0x0,0x3f,0x71,0x71}; // off
      Temp_display.setSegments(dd);
    }
  }
    ///////////////////////////////////////////// Boil /////////////////////////////////////////////////
  if (Mode_pos == -1){
    if (istimeroff){
      uint8_t dd[] = {0x0,0x3f,0x71,0x71}; // off
      Time_display.setSegments(dd);
    }else{
      // set time
      //Time_min = 
      //Time_hr = 
      Time_display.showNumberDec(Time_min+1+Time_hr*100,true);
    }
    if (isStoveOn){
      uint8_t ddx1[] = {0x0,0x76,0x66,0x0}; // H 4
      Temp_display.setSegments(ddx1);
    }else{
      uint8_t dd[] = {0x0,0x3f,0x71,0x71}; // off
      Temp_display.setSegments(dd);
    }
  }
  /////////////////////////////
  
  if (Mode_change == 1){
    Mode_pos = Mode_pos + 1;
    isStoveOn = true;
    /// Manual //////////////////////// Mode 1 
    if (Mode_pos == 0){
      digitalWrite(mode_1,HIGH);
      digitalWrite(mode_2,LOW);
      digitalWrite(mode_3,LOW);
      digitalWrite(mode_4,LOW);
      digitalWrite(mode_5,LOW);

      // Set Temporature // 
      Display_Temp = 40;

      istimeroff = true;
      Time_min = 9;
      Time_hr = 0;

    }
    /// Cook ////////////////////////// Mode 2
    if (Mode_pos == 1){
      digitalWrite(mode_1,LOW);
      digitalWrite(mode_2,HIGH);
      digitalWrite(mode_3,LOW);
      digitalWrite(mode_4,LOW);
      digitalWrite(mode_5,LOW);
      
      // Set Temporature // 
      Display_Temp = 55;

      istimeroff = false;
      Time_min = 19;
      Time_hr = 0;
      
    }
    /// Hot Pot ////////////////////// Mode 3
    if (Mode_pos == 2){
      digitalWrite(mode_1,LOW);
      digitalWrite(mode_2,LOW);
      digitalWrite(mode_3,HIGH);
      digitalWrite(mode_4,LOW);
      digitalWrite(mode_5,LOW);

      // Set Temporature // 
      Display_Temp = 80;

      istimeroff = false;
      Time_min = 24;
      Time_hr = 0;

    }
    /// Fry ///////////////////////// Mode 4
    if (Mode_pos == 3){
      digitalWrite(mode_1,LOW);
      digitalWrite(mode_2,LOW);
      digitalWrite(mode_3,LOW);
      digitalWrite(mode_4,HIGH);
      digitalWrite(mode_5,LOW);

      // Set Temporature // 
      Display_Temp = 70;

      istimeroff = false;
      Time_min = 49;
      Time_hr = 0;

    }
    /// Boil /////////////////////// Mode 5 
    if (Mode_pos == 4){
      digitalWrite(mode_1,LOW);
      digitalWrite(mode_2,LOW);
      digitalWrite(mode_3,LOW);
      digitalWrite(mode_4,LOW);
      digitalWrite(mode_5,HIGH);
      Mode_pos = -1;

      // Set Temporature // 
      Display_Temp = 110;

      istimeroff = false;
      Time_min = 54;
      Time_hr = 0;

    }
    delay(300);
    sec_count = sec_count + 0.5;
    }

  if ( Temp_minus == 1){
    if (Mode_pos > 0){
      uint8_t dd[] = {0x0,0x79,0x50,0x50}; // Err
      Temp_display.setSegments(dd);
      delay(2000);
      sec_count = sec_count + 2.0;
    }else{
      if (Display_Temp > 30){
        Display_Temp = Display_Temp - 5;
        Temp_display.showNumberDec(Display_Temp,false);
        delay(300); 
        sec_count = sec_count + 0.5;
      }
    }
    }
    

  if ( Temp_plus == 1){
    if (Mode_pos > 0){
      uint8_t dd[] = {0x0,0x79,0x50,0x50}; // Err
      Temp_display.setSegments(dd);
      delay(2000);
      sec_count = sec_count + 2;
    }else{
      Display_Temp = Display_Temp + 5;
      Temp_display.showNumberDec(Display_Temp,false);
      delay(300); 
      sec_count = sec_count + 0.5;
    }
    }
    
  
  if ( Timer_plus == 1){
    isStoveOn = true;
    Time_min = Time_min + 1;
    if (Time_min >= 60){
      Time_hr = Time_hr+1;
      Time_min = 0;
    }
    Time_display.showNumberDec(Time_min+1+Time_hr*100,true);
    istimeroff = false;
    delay(300);
    sec_count = sec_count + 0.5;
    }

  if ( Timer_minus == 1){
    Time_min = Time_min - 1;
    if (Time_min < 0){
      if (Time_hr <= 0){
        Time_min = 0;
        Time_hr = 0;
      }else{
        Time_hr = Time_hr - 1;
        Time_min = 55;
      }
    }
    Time_display.showNumberDec(Time_min+1+Time_hr*100,true);
    delay(300);
    sec_count = sec_count + 0.5;
    istimeroff = false;
    }

  if ( Timer_off == 1) {
    uint8_t dd[] = {0x0,0x3f,0x71,0x71}; // off
    Time_display.setSegments(dd);
    istimeroff = true;
    Time_min = 9;
    Time_hr = 0;
    }

  /// Time counter ////
  if (istimeroff){
    sec_count = 0.0;
  }else{
    // blinking Dots
    if (Blinking_pos > 5){
      Time_display.showNumberDecEx(Time_min+1+Time_hr*100,0b11110000,true);
      delay(150);
      Blinking_pos = 0;
      Temp_display.showNumberDec(Temp);
      delay(150);
    }else {
      Time_display.showNumberDec(Time_min+1+Time_hr*100,true);
    }
  }
  if (sec_count > 30.0){
    if (Time_min > 0){
      Time_min = Time_min - 1;
    }else{
      if (Time_hr > 0){
        Time_min = 59;
        Time_hr = Time_hr - 1;
      }else{
        isStoveOn = false;
        Time_min = -1;
      }
    }
    sec_count = sec_count - 30.0;
    Time_display.showNumberDec(Time_min+1+Time_hr*100,true);
  }
  delay(100);
  sec_count = sec_count + 0.1;
  Blinking_pos = Blinking_pos + 1;
  //////////////////// 
  Temp = round(Tmp);
}



