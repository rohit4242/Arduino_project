
// AUTOMATIC IRRIGATION SYSTEM

/* The program for AUTOMATIC IRRIGATION SYSTEM IS Written and Tested by__

 HS Sandesh Hegde
 Harish P Nair
 HV Sampad Nayak

DISCLAIMER: This is a Open Source Software and This Software is distributed in the hope that it will be useful,
            but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 

Connection Details 
ARDUINO PINS
0_________________N/C
1_________________N/C
2_________________LCD-14
3_________________LCD-13
4_________________LCD-12
5_________________LCD-11
6_________________N/C
7_________________WATER_LEVEL_STATUS_LED
8_________________N/C
9_________________SPEAKER
10________________N/C
11________________LCD-6
12________________LCD-4
13________________PUMP_STATUS_LED)_AND_TO_RELAY
A0________________SOIL_MOISTURE_SENSOR
A4________________LM35_(TEMPERATURE_SENSOR)  //Bug reported for Unstable Temperature Reading 

LCD-1_____________GND
LCD-5_____________GND
LCD-2_____________+Vcc
LCD-3_____________LCD_BRIGHTNESS


*/
 
#include <LiquidCrystal.h> //LCD Library

#define NOTE_C4 262 
#define NOTE_D4 294 
#define NOTE_E4 330 
#define NOTE_F4 349 
#define NOTE_G4 392 
#define NOTE_A4 440 
#define NOTE_B4 494 
#define NOTE_C5 523 

int temp;
//int T_Sensor = A4;
int M_Sensor = A0;
int W_led = 7;
int P_led = 13;
int Speaker = 9;
int val;
int cel;  

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
 {
    lcd.begin(16, 2);
    lcd.clear(); 
    pinMode(13,OUTPUT);
    pinMode(7,INPUT);
    pinMode(9,OUTPUT);
    Serial.begin(9600);
    /*
    val = analogRead(T_Sensor); //Read Temperature sensor value 
    
    int mv = ( val/1024.0)*5000; 
    cel = mv/10;
    */
    lcd.setCursor(0,1);
    lcd.print("THE TECHNOCRAT");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("AUTOMATIC");
    lcd.setCursor(0,1);
    lcd.print("IRIGATION SYSTEM");
    delay(2500);
    lcd.clear(); 
   
  
    delay(1000);
}

void loop()
{
  
  lcd.clear();
    /* val = analogRead(T_Sensor); //Read Temperature sensor value 
    Serial.println(val);
    int mv = ( val/1024.0)*5000; 
     cel = mv/10;
  */
  int Moisture = analogRead(M_Sensor); //Read Moisture Sensor Value 
  Serial.println(Moisture);
/*
  lcd.setCursor(0,0);
  lcd.print("TEMP:");
  lcd.setCursor(5,0);
  lcd.print(cel);
  lcd.setCursor(7,0);
  lcd.print("*C");
 */
 if (Moisture> 200)   // for dry soil
  { 
        lcd.setCursor(0,0);
        lcd.print("DRY SOIL");
        //lcd.setCursor(11,1);
        //lcd.print("SOIL");
       if (digitalRead(W_led)==1) //test the availability of water in storage
       {
         digitalWrite(13, HIGH);
         lcd.setCursor(0,1);
         lcd.print("PUMP:ON");
       }
       else
       {
         digitalWrite(13, LOW);
         lcd.setCursor(0,1);
         lcd.print("PUMP:OFF");
         lcd.setCursor(11,0);
        lcd.print("WATER");
        lcd.setCursor(11,1);
        lcd.print("LOW");
         
           
           tone(Speaker, NOTE_C4, 500); 
           delay(500); 
           tone(Speaker, NOTE_D4, 500);
           delay(500); 
           tone(Speaker, NOTE_E4, 500); 
           delay(500); 
           tone(Speaker, NOTE_F4, 500); 
           delay(500); 
           tone(Speaker, NOTE_G4, 500); 
           delay(500);
       }
    }
 
     if (Moisture>= 70 && Moisture<=200) //for Moist Soil
    { 
      lcd.setCursor(0,0);
     lcd.print("MOIST SOIL");
     //lcd.setCursor(11,1);
     //lcd.print("SOIL");
     digitalWrite(13,LOW);
     lcd.setCursor(0,1);
     lcd.print("PUMP:OFF");    
  }
 
  if (Moisture < 70)  // For Soggy soil
  { 
    lcd.setCursor(0,0);
     lcd.print("SOGGY SOIL");
     //lcd.setCursor(11,1);
     //lcd.print("SOIL");
     digitalWrite(13,LOW);
     lcd.setCursor(0,1);
     lcd.print("PUMP:OFF");
  }
 delay(1000);    
}  


/*References_________________________________________________
https://www.arduino.cc/en/Reference/LiquidCrystalSetCursor
http://www.instructables.com/id/Connect-A-16x2-LCD-Display-To-An-Arduino/
http://www.instructables.com/id/Soil-Moisture-Sensor/
http://www.instructables.com/id/Arduino-Temperature-Sensor-Interfacing-LM35-THE-EA/
https://www.arduino.cc/en/Reference/digitalRead
http://www.instructables.com/id/ARDUINO-TEMPERATURE-SENSOR-LM35/
http://www.electroschematics.com/6519/simple-soil-moisture-sensor-arduino-project/

*/
