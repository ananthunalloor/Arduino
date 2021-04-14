#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t my_radio_pipe = 0xE8E8F0F0E1LL; //Remember that this code should be the same for the receiver

RF24 radio(9, 10);  //Set CE and CSN pins

// The sizeof this struct should not exceed 32 bytes
struct Data_to_be_sent {
  int ch1;
  int ch2;
};

//Create a variable with the structure above and name it sent_data
Data_to_be_sent sent_data;



void setup()
{
  radio.begin();
  Serial.begin(115200);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(my_radio_pipe);

  //Reset each channel value
  sent_data.ch1 = 0;
  sent_data.ch2 = 0;

}

/**************************************************/


void loop()
{
  int xAxis ,yAxis, distance, degree;
  unsigned long data = 0;
  int xmap,ymap;
   if (Serial.available() > 0) {
    String Income = Serial.readStringUntil('\r\n');
    data = Income.toInt();
    distance = data/1000;
    //degree = map(data%1000, 0, 360, 0, 255);
    degree = data%1000;
   }
   xAxis = (distance/100 * cos(degree))*255;
   yAxis = (distance/100 * sin(degree))*255;
   if(xAxis < 0){
    xmap = map(xAxis, 0 , -255, 100, 355);
    }
   else if(xAxis > 0){
    xmap = map(xAxis, 0 , 255, 360, 620);
    }
   else{
    xmap = 100;
    }
    if(yAxis < 0){
    ymap = map(yAxis, 0 , -255, 100, 355);
    }
   else if(yAxis > 0){
    ymap = map(yAxis, 0 , 255, 360, 620);
    }
   else{
    ymap = 100;
    }
  sent_data.ch1 = xmap;
  sent_data.ch2 = ymap;
  //sent_data.ch3 = map( analogRead(A2), 0, 1024, 255, 0);

  radio.write(&sent_data, sizeof(Data_to_be_sent));
    Serial.print(data);Serial.print("   xaxis - ");Serial.print(xAxis);
    Serial.print("  xMap - ");Serial.print(xmap);
    Serial.print("  yaxis - ");Serial.print(yAxis);
    Serial.print("  yMap - ");Serial.println(ymap);
  //Serial.println(analogRead(A0));
}
