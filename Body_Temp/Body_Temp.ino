#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

int echoPin = 2;
int trigPin = 3;

void setup() {
  mlx.begin();
  Serial.begin(9600);
}

void loop() {
  Serial.println(calcDist());
}

int calcDist()
{
  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 
  return distance;
}

void alert(){
  delay(5000);
}
