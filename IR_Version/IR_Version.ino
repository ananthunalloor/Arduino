#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int ProxSensor=2;
int inputVal = 0;
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);




//uint16_t proximity_data = 0;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {

  mlx.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  pinMode(ProxSensor,INPUT);
  Serial.begin(9600);
   display.clearDisplay();
      display.invertDisplay(false);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("WELCOME");
      delay(3000);
}


void loop() {
  String temperature = "";
  /*
    Serial.print("Ambient ");
    Serial.print(mlx.readAmbientTempC());
    Serial.print(" C");
    Serial.println();

    Serial.print("Target  ");
    Serial.print(mlx.readObjectTempC());
    Serial.print(" C");
    Serial.println();
  */

  noTone(5);

  inputVal = digitalRead(ProxSensor);
  Serial.println(inputVal);
  if (inputVal == 0 && mlx.readObjectTempF() < 100) {


    temperature = String(mlx.readObjectTempC(), 1);
    Serial.print(" Body Temperature:");
    Serial.println(mlx.readObjectTempC());
    display.clearDisplay();
    display.invertDisplay(false);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(8, 0);
    display.clearDisplay();
    display.println("Body-Temp:");
    display.setCursor(25, 18);
    display.print(mlx.readObjectTempF());

    display.setCursor(85, 8);
    display.print(".");


    display.setTextColor(WHITE);
    display.setCursor(85, 18);
    display.print(" F");
    tone(8, 1397, 1000);
    display.clearDisplay();
    display.invertDisplay(false);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(8, 0);
    display.clearDisplay();
    display.println("GET IN");
   delay(5000);

  }
  if (inputVal == 0) {
    if (mlx.readObjectTempF() > 102) {
      
      // play a note on pin 8 for 500 ms:
      tone(8, 523, 500);

      display.clearDisplay();
      display.invertDisplay(false);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");
      tone(8, 523, 500);
      delay(500);

      display.invertDisplay(true);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");
      tone(8, 523, 500);
      delay(500);


      display.invertDisplay(true);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");
      delay(500);


      display.invertDisplay(false);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");
      tone(8, 523, 500);
      delay(500);

      display.invertDisplay(true);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");
      tone(8, 523, 500);
      delay(500);


      display.invertDisplay(true);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");
      delay(500);


      display.invertDisplay(false);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");
      tone(8, 523, 500);
      delay(500);




      display.setCursor(23, 18);
      display.print(mlx.readObjectTempF());
      display.setCursor(93, 8);
      display.print(".");
      display.setTextColor(WHITE);
      display.setCursor(93, 18);
      display.print(" F");
      display.display();


      delay(5000);
    }

  }

  if (inputVal == 0) {
    if (mlx.readObjectTempF() < 100) {

      display.setCursor(93, 8);
      display.print(".");


      display.setTextColor(WHITE);
      display.setCursor(93, 18);
      display.print(" F");
      display.display();
    }
  }

  else if (inputVal == 1) {
    delay(1000);

    display.clearDisplay();
    //display.invertDisplay(true);
    display.setTextSize(2.8);
    display.setTextColor(WHITE);
    display.setCursor(45, 1);
    display.clearDisplay();
    display.println("NOT");
    display.setCursor(17, 17);
    display.print("DETECTED");
    display.display();
    digitalWrite(5, LOW);

  }
}
