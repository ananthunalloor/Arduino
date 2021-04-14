#include <Wire.h>
//#include <SparkFun_APDS9960.h>
#include <APDS9930.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define echoPin 2
#define trigPin 3 
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);




//SparkFun_APDS9960 apds = SparkFun_APDS9960();
APDS9930 apds = APDS9930();
uint16_t proximity_data = 0;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
long duration;
int distance;

void setup() {

  mlx.begin();
  apds.init();
  apds.enableProximitySensor(false);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

  display.clearDisplay();
      display.invertDisplay(false);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("WELCOME");

    delay(2000);

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
    digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  noTone(5);
  //apds.readProximity(proximity_data);
  //Serial.println(proximity_data);
  //delay(500);
  proximity_data = distance;
  if (proximity_data <= 5 && mlx.readObjectTempF() < 100) {


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
    display.print(mlx.readObjectTempF()+4);

    display.setCursor(85, 8);
    display.print(".");


    display.setTextColor(WHITE);
    display.setCursor(85, 18);
    display.print(" F");
    display.display();
    tone(8, 1397, 1000);
delay(3000);
      display.clearDisplay();
      display.invertDisplay(false);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("GET IN");

    delay(3000);

  }
  if (proximity_data <= 5) {
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
      display.print(mlx.readObjectTempF()+4);
      display.setCursor(93, 8);
      display.print(".");
      display.setTextColor(WHITE);
      display.setCursor(93, 18);
      display.print(" F");
      display.display();


      delay(5000);
    }

  }

  if (proximity_data <= 5) {
    if (mlx.readObjectTempF() < 100) {

      display.setCursor(93, 8);
      display.print(".");


      display.setTextColor(WHITE);
      display.setCursor(93, 18);
      display.print(" F");
      display.display();
    }
  }

  else if (proximity_data >= 10) {
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
