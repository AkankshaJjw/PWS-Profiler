#!/usr/bin/env python
from smbus import SMBus
import time

def main():
    # Define registers values from datasheet
    control = 0x01
    current_msb = 0x02; # address 02
    current_lsb = 0x03; # address 03
    temp_msb = 0x14
    temp_lsb = 0x15
    temp_thresh = 0x16

    i2caddress = 0b1100100;  # I2C address of our chip

    i2cbus = SMBus(1)  # Create a new I2C bus
    print("Begin\n")
    i2cbus.write_byte_data(i2caddress, control, 0x07)
    control_value = i2cbus.read_byte_data(i2caddress, control)  # Read the value of Port B
    print("Value of the control register: ", control) # print the value of Port B

if __name__ == "__main__":
    main()