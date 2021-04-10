#include <Wire.h>
#include "LTC2944.h"

void setup() {
  
//  Wire.setSpeed(CLOCK_SPEED_100KHZ);
//  Wire.stretchClock(true);
  Wire.begin();
  LTC2944_mode = LTC2944_AUTOMATIC_MODE | prescalar_mode | alcc_mode ;
  ack |= LTC2944_write(LTC2944_I2C_ADDRESS, LTC2944_CONTROL_REG, LTC2944_mode);

}

void loop() {

  // Read 16-bit charge measurement
  ack |= LTC2944_read_16_bits(LTC2944_I2C_ADDRESS, LTC2944_VOLTAGE_MSB_REG, &voltage_measurement);
  // Convert voltage reading to Volts
  batteryState.voltage_V = LTC2944_code_to_voltage(voltage_measurement);
  Serial.print("Raw Battery Voltage: ");
  Serial.println(voltage_measurement);

}
