#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)

struct can_frame canMsg;
 
MCP2515 mcp2515(10);
 
int lm35_pin=A0;
void setup()
{
  while (!Serial);
  Serial.begin(9600);
  SPI.begin();               //Begins SPI communication
  
  pinMode(lm35_pin,INPUT);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();
}
 
 
void loop()
{
  int temp_adc_val;
  float temp_val;
  temp_adc_val = analogRead(lm35_pin);	/* Read Temperature */
  temp_val = (temp_adc_val * 4.88);	/* Convert adc value to equivalent voltage */
  temp_val = (temp_val/10);	/* LM35 gives output of 10mv/°C */
  
  canMsg.can_id  = 0x036;           //CAN id as 0x036
  canMsg.can_dlc = 8;               //CAN data length as 8
  canMsg.data[0] = temp_val;              
  canMsg.data[1] = 0x00;             
  canMsg.data[2] = 0x00;            
  canMsg.data[3] = 0x00;
  canMsg.data[4] = 0x00;
  canMsg.data[5] = 0x00;
  canMsg.data[6] = 0x00;
  canMsg.data[7] = 0x00;
 
  mcp2515.sendMessage(&canMsg);     //Sends the CAN message
  delay(1000);
}