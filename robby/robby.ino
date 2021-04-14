#include <HX711_ADC.h> 
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // LiquidCrystal_I2C library
HX711_ADC LoadCell(4, 5); // data pin, clock pin
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);
int led = 2;
int taree = 6;
int up = 7;
int down = 8;
int start = 9;
int BUZZER = 10;
int pump = 11;
int sensor = 12;
float a = 50;
float b = 0;
int c = 31;   // Adjust this to remove zero error
int d = 0;

void setup() {
  pinMode(pump, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode (taree, INPUT_PULLUP);
  pinMode (up, INPUT_PULLUP);
  pinMode (down, INPUT_PULLUP);
  pinMode (sensor, INPUT);
  LoadCell.begin(); // start connection to HX711
  LoadCell.start(500); // load cells gets 500ms of time to stabilize
  LoadCell.setCalFactor(832.10); // calibration factor for load cell => strongly dependent on your individual setup
  lcd.init(); // begins connection to the LCD module
  lcd.backlight(); // turns on the backlight
  lcd.setCursor(4, 0); // set cursor to first row
  lcd.print("*** EASY ***"); // print out to LCD
 lcd.setCursor(4, 1); // set cursor to first row
  lcd.print("* HOMEMADE *"); // print out to LCD
   lcd.setCursor(4, 2); // set cursor to first row
  lcd.print("* PROJECTS *"); // print out to LCD
   lcd.setCursor(4, 3); // set cursor to first row
  lcd.print("************"); // print out to LCD
  delay(2000);
  digitalWrite(led,HIGH);
  tone(BUZZER, 1000);
  delay(200);
  noTone(BUZZER);
  digitalWrite(led,LOW);
  lcd.clear();
  lcd.setCursor(0, 0); // set cursor to first row
  lcd.print("--Filling Machine---"); // print out to LCD

  
}
void loop() 
{
  if (digitalRead (up) == HIGH)
  {
    a=a+1;
    digitalWrite(led,HIGH);
    tone(BUZZER, 2000);
  delay(100);
  noTone(BUZZER);
  delay(100);
  digitalWrite(led,LOW);
   if (a>500)
    {
      a=500;
    } 
      while (digitalRead (up) == HIGH)
  { 
  lcd.setCursor(15, 1); // set cursor to secon row
  lcd.print(a, 0);
  lcd.print("g");
  lcd.print(" ");
    delay(50);
    a=a+10;
  
    if (a>500)
    {
      a=500;
    } 
  
  } 
  }
   if (digitalRead (down) == HIGH)
  {
    a=a-1;
    digitalWrite(led,HIGH);
    tone(BUZZER, 2000);
  delay(100);
  noTone(BUZZER);
  delay(100);
  digitalWrite(led,LOW);
   if (a<=50)
    {
      a=50;
    } 
      while (digitalRead (down) == HIGH)
  { 
  lcd.setCursor(15, 1); // set cursor to secon row
  lcd.print(a, 0);
  lcd.print("g");
  lcd.print(" ");
    delay(50);
    a=a-10;
  
    if (a<=50)
    {
      a=50;
    } 
  
  } 
  }
  lcd.setCursor(15, 1); // set cursor to secon row
  lcd.print(a, 0);
  lcd.print("g");
  lcd.print(" ");
  digitalWrite(pump,LOW);
  LoadCell.update(); // retrieves data from the load cell
  int i = LoadCell.getData(); // get output value
  lcd.setCursor(1, 1); // set cursor to first row
  lcd.print("   Set Amount "); // print out to LCD
   lcd.setCursor(0, 2); // set cursor to secon row
  lcd.print("Current Weight ");
  lcd.setCursor(15, 2); // set cursor to secon row
  lcd.print(i); // print out the retrieved value to the second row
  lcd.print("g");
  lcd.print(" ");
   if (i>=999)
  {
  lcd.setCursor(0, 2); // set cursor to secon row
  lcd.print("    Over Loaded     ");
  i=0; 
  delay(100);
    digitalWrite(pump, LOW);
    digitalWrite(led,HIGH);
   tone(BUZZER, 2000);
  delay(500);
  noTone(BUZZER);
  digitalWrite(led,LOW);
  }

  if (digitalRead (taree) == HIGH)
  {  
    digitalWrite(led,HIGH);
  tone(BUZZER, 2000);
  delay(200);
  noTone(BUZZER);
  digitalWrite(led,LOW);
   lcd.setCursor(0, 2); // set cursor to secon row
    lcd.print("    Taring...       ");
   LoadCell.start(500);
     digitalWrite(led,HIGH);
  tone(BUZZER, 2000);
  delay(100);
  noTone(BUZZER);
  digitalWrite(led,LOW);
  }
if(digitalRead(startt) == HIGH && digitalRead(sensor) == HIGH)
 {
   lcd.setCursor(0,3); // column, row
  lcd.print("ERROR! No Bottle/Jar");
  digitalWrite(led,HIGH);
   tone(BUZZER, 1000);
  delay(200);
  noTone(BUZZER);
  delay(100);
   tone(BUZZER, 1000);
  delay(500);
  noTone(BUZZER);
  delay(1000);
  digitalWrite(led,LOW);
   lcd.setCursor(0,3); // column, row
  lcd.print("                    ");
  }


  
if(digitalRead(startt) == HIGH && digitalRead(sensor) == LOW  && d == 0) 
{ 
  digitalWrite(led,HIGH);
  tone(BUZZER, 1500);
  delay(200);
  noTone(BUZZER);
  digitalWrite(led,LOW);

lcd.setCursor(0, 3); // set cursor to first row
lcd.print("                    "); // print out to LCD
lcd.setCursor(3, 3); // set cursor to first row
lcd.print("Filling... "); // print out to LCD
  
  while (1)
  { 

  digitalWrite(pump, HIGH); 
  LoadCell.update(); // retrieves data from the load cell
  int i = LoadCell.getData(); // get output value
  lcd.setCursor(1, 1); // set cursor to first row
  lcd.print("   Set Amount "); // print out to LCD
lcd.setCursor(0, 2); // set cursor to secon row
  lcd.print("Current Weight ");
  lcd.setCursor(15, 2); // set cursor to secon row
  lcd.print(i); // print out the retrieved value to the second row
  lcd.print("g");
  lcd.print(" ");
b=(i/(a-c))*100;
lcd.setCursor(15, 3); // set cursor to first row
lcd.print(b, 0);
lcd.print("% ");
  
   if (i>=999)
  {
  lcd.setCursor(0, 2); // set cursor to secon row
  lcd.print("    Over Loaded     ");
  i=0; 
  delay(100);
    digitalWrite(pump, LOW);
    digitalWrite(led,HIGH);
   tone(BUZZER, 500);
  delay(1000);
  noTone(BUZZER);
  digitalWrite(led,LOW);
  }
  if (i >= (a-c) || i>999)
  break;
  } 
  digitalWrite(pump, LOW);
  lcd.setCursor(0, 3); // set cursor to first row
lcd.print("   Completed   100% "); // print out to LCD
digitalWrite(led,HIGH);
   tone(BUZZER, 2200);
  delay(100);
  noTone(BUZZER);
  delay(30);
   tone(BUZZER, 2200);
  delay(300);
  noTone(BUZZER);
  digitalWrite(led,LOW);
 d = 1;
}
if(digitalRead(startt) == HIGH && d == 1)
 {
   lcd.setCursor(0,3); // column, row
  lcd.print("Place New Bottle/Jar");
  digitalWrite(led,HIGH);
   tone(BUZZER, 1000);
  delay(200);
  noTone(BUZZER);
  delay(100);
   tone(BUZZER, 1000);
  delay(500);
  noTone(BUZZER);
  delay(800);
  digitalWrite(led,LOW);
   lcd.setCursor(0,3); // column, row
  lcd.print("                    ");
  }
  
  if(digitalRead(sensor) == HIGH) 
{
 d = 0;
}
}
