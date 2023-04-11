#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display
 
struct can_frame canMsg;
 
MCP2515 mcp2515(10);                 // SPI CS Pin 10

 
void setup()
{
  Serial.begin(9600);                //Begins Serial Communication at 9600 baudrate
  SPI.begin();                       //Begins SPI communication
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  lcd.setCursor(0, 0);
  lcd.print("CANBUS Comm.");
  delay(3000);
  
 
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();                  //Sets CAN at normal mode
}
 
 
void loop()
{
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
  {
    float temp = canMsg.data[0];
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(temp);
    delay(1000);
    lcd.clear();
  }
}