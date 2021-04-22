#include <stdio.h>
#include <stdint.h>
#include "LTC2944.h"

const uint8_t i2caddr_short = 0b1100100;
const uint8_t i2caddr = 0b11001000;

const uint8_t control = 0x01;

const uint8_t tempMSB = 0x14;
const uint8_t tempLSB = 0x15;

uint16_t buffer = 0;
int8_t ack = 0;
float result = 0.0f;


void setup() {
  Serial.begin(9600);

  
  uint8_t setup_ctrl_reg = 0b11000000;
  ack = LTC2944_register_set_clear_bits(i2caddr, control, setup_ctrl_reg, 0); 
  
  if (!ack) {
    Serial.println("Successful Init of control register\r\n");
  } else {
    Serial.println("WTF");
  }
  
}



void loop() {
  //NOTE THE COMMAND BYTE IS THE REGISTER ADDRESS
  ack = LTC2944_read_16_bits(i2caddr, tempMSB, &buffer);
  if (!ack) {
     result = LTC2944_code_to_celcius_temperature(buffer);
     Serial.println(result);
  } else {
     result = LTC2944_code_to_celcius_temperature(buffer);
     Serial.print(result);
     Serial.println(", WTF");
  }

}
