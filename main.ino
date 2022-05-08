
#include <LiquidCrystal.h>
#include <time.h>
#include <TimeLib.h>

#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int soilMoistureValue = 0;
int sensorInput;
double temp;

int timeHour;
int timeMin;
int timeSec;
//----------------------------------------


void setup() {
  Serial.begin(9600); 
  lcd.begin(16, 2);
  pinMode(8,OUTPUT);

}
void loop() {
     soil_moisture();
     temp_humidity();

}

void soil_moisture()
{
soilMoistureValue = analogRead(A0);
Serial.println(soilMoistureValue);
  
if(soilMoistureValue > 0 && soilMoistureValue <=150)
{
  Serial.println("===============");
  Serial.println(soilMoistureValue);
  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture: ");
  lcd.setCursor(0, 1);
  lcd.print("LOW  ");
  lcd.print(soilMoistureValue);
  
  if (soilMoistureValue > 0 && soilMoistureValue <=150)
   {
    digitalWrite(8, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MOTOR: ON");
    delay(5000);
   }
  else
  {
    digitalWrite(8, LOW);
    lcd.print("MOTOR: OFF");
    delay(2000);
    lcd.clear();
  }
}
else if(soilMoistureValue >150 && soilMoistureValue <= 500)
{
  Serial.println("===============");
  Serial.println(soilMoistureValue);
  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture: ");
  lcd.setCursor(0, 1);
  lcd.print("MID  ");
  lcd.print(soilMoistureValue);
  delay(2000);
  lcd.clear();
  if (soilMoistureValue > 0 && soilMoistureValue <=150)
   {
    digitalWrite(8, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MOTOR: ON");
    delay(5000);
   }
  else
  {
    digitalWrite(8, LOW);
    lcd.print("MOTOR: OFF");
    delay(2000);
    lcd.clear();
  }
}
else if(soilMoistureValue >300 && soilMoistureValue <=900)
{
  Serial.println("===============");
  Serial.print(soilMoistureValue);
  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture: ");
  lcd.setCursor(0, 1);
  lcd.print("HIGH  ");
  lcd.print(soilMoistureValue);
  delay(2000);
  lcd.clear();
  if (soilMoistureValue > 0 && soilMoistureValue <=150)
   {
    digitalWrite(8, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MOTOR: ON");
    delay(5000);
   }
  else
  {
    digitalWrite(8, LOW);
    lcd.print("MOTOR: OFF");
    delay(2000);
    lcd.clear();
  }
}  
}

void temp_humidity()
{
  sensorInput = analogRead(A1); //read the analog sensor and store it
  temp = (double)sensorInput / 1024; //find percentage of input reading
  temp = temp * 5; //multiply by 5V to get voltage
 // temp = temp – 0.5; //Subtract the offset
  temp = temp * 100; //Convert to degrees

  Serial.print("TEMPERATURE = ");
  Serial.print(temp);
  Serial.print("*C");
  Serial.println();
  lcd.setCursor(0,0);
  lcd.print("Temperature: ");
  lcd.setCursor(0, 1);
  lcd.print(temp);
  delay(2000);  
  lcd.clear();
}
void digitalClockDisplay(){
  // digital clock display of the time
  lcd.print("Time ");
  lcd.print(hour());
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  lcd.setCursor(0, 1);
  lcd.print("Date ");
  lcd.print(day());
  lcd.print("/");
  lcd.print(month());
  lcd.print("/");
  lcd.print(year()); 
   
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  lcd.print(":");
  if(digits < 10)
    lcd.print('0');
  lcd.print(digits);
}


//void processSyncMessage() {
//  unsigned long pctime;
//  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013
//
//  if(Serial.find(TIME_HEADER)) {
//     pctime = Serial.parseInt();
//     if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
//       setTime(pctime); // Sync Arduino clock to the time received on the serial port
//     }
//  }
//}

time_t requestSync()
{
  Serial.write(TIME_REQUEST);  
  return 0; // the time will be sent later in response to serial mesg
}

// create a function to display the current time on display and to update the time every second

//void cur_time()
//{
//    Serial.print("Time: ");
//    Serial.print(timeHour);
//    Serial.print(":");
//    Serial.print(timeMin);
//    Serial.print(":");
//    Serial.print(timeSec);
//    Serial.println();
//    lcd.setCursor(0,0);
//    lcd.print("Time: ");
//    lcd.setCursor(0, 1);
//    lcd.print(timeHour);
//    lcd.print(":");
//    lcd.print(timeMin);
//    lcd.print(":");
//    lcd.print(timeSec);
//    delay(2000);
//    lcd.clear();
//
//}