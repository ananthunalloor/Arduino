#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <APDS9930.h>

APDS9930 apds = APDS9930();
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
uint16_t proximity_data = 0;

void setup() {
  mlx.begin();
  apds.init();
  apds.enableProximitySensor(false);
  Serial.begin(9600);
}

void loop() {
 // Serial.println(mlx.readObjectTempF());
  Serial.println(proximity_data);
}
