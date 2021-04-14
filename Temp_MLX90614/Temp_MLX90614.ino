
#include <Wire.h>
#include <Adafruit_MLX90614.h>

//#define I2C_ADDR 0x27 //I2C adress, you should use the code to scan the adress first (0x27) here

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  mlx.begin();
  Serial.begin(9600);
}

void loop() {
 Serial.print("Temp : ");
 Serial.print(mlx.readObjectTempC());
 Serial.print(" C");
 Serial.println();
 delay(1000);

}
