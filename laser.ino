#include "TM1637Display.h"

int LASER_POWER = 16; 
int LASER_SENSE = 3; 
int RXLED = 17;

int SEG_CLK = 8;
int SEG_DIO =9;

int START = 0;

TM1637Display display(SEG_CLK, SEG_DIO);

volatile byte state = LOW;

void setup()
{
 laser_config();  
 digitalWrite(LASER_POWER, HIGH);
 Serial.begin(9600); 
}

void loop()
{
  //uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  display.setBrightness(0x0f);

  //data[0] = display.encodeDigit((START/1000)%10);
  //data[1] = display.encodeDigit((START/100)%10);
  //data[2] = display.encodeDigit(START%100/10);
  //data[3] = display.encodeDigit(START%10);

  display.showNumberDecEx(START, (0x80 >> 1), true, 4, 0);
  // All segments on
  //display.setSegments(data);
  delay(10);

  START=START+1;

}

void laser_config()
{
  //Set the Laser Power to GPIO Output
  pinMode(LASER_POWER, OUTPUT);  
  pinMode(RXLED, OUTPUT);

  //Attach a IRQ Interrupt Service (laser_irq) to a falling edge
  attachInterrupt(digitalPinToInterrupt(LASER_SENSE), laser_irq, FALLING);
}

void laser_irq()
{
  state = !state;
  digitalWrite(RXLED, state);    // set the RX LED OFF
 
  Serial.println("Laser IRQ Interrupt");  
}
