/* source of code:
https://www.electroschematics.com/9798/reading-temperatures-i2c-arduino/ */
#include <Wire.h>

//register addresses
const int control = 0x01;
unsigned int current_msb = 0x02; // address 02
int current_lsb = 0x03; // address 03
int temp_msb = 0x14;
int temp_lsb = 0x15;
int temp_thresh = 0x16;

int addressLTC = 0b1100100;  // I2C address of our chip

void setup() {
  //pinMode(20, INPUT_PULLUP);
  //pinMode(21, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Begin");
  Wire.begin();     // create a wire object, join bus as master
  Serial.println("Wire Initialized");

  //initialize control register
  Wire.beginTransmission(addressLTC);
  //Wire.write(current_msb);  // this write is the current sense register
  Wire.write(temp_thresh);
  //Wire.write(0x07);  //write 7 to this register!
  byte transmitStat = Wire.endTransmission(addressLTC);
  Serial.print("Write?: ");
  Serial.println(transmitStat);
  
  /*Wire.requestFrom(addressLTC, 1);
  //while(Wire.available() == 0);
  int ctrl_reg = Wire.read();*/
  
  
}


void loop() {
  /*int c1 = read_reg(addressLTC, temp_msb);
  int c2 = read_reg(addressLTC, temp_lsb);
  
  int result = c1 << 16 + c2;*/
//  Serial.println("Result is");
//  Serial.println(ctrl_reg);
  Wire.beginTransmission(addressLTC);
  Wire.write(temp_thresh);
  byte transmitStatus = Wire.endTransmission(false);
  Serial.print("Is Transmit Success?: ");
  Serial.println(transmitStatus);

  
  byte receiveStatus = Wire.requestFrom(addressLTC, 1, false);
  //while(Wire.available() == 0);
  Serial.print("Bytes Received: ");
  Serial.println(receiveStatus);
  Serial.println(Wire.available());
  while(Wire.available()){
  byte ctrl_reg = Wire.read();
  
  Serial.print("Wire Control Register: ");
  Serial.println(ctrl_reg);}

  delay(500);  
}


int read_reg(int address, int reg) {
  //start the communication with IC with the address xx
  Wire.beginTransmission(address); 
  //send a bit and ask for register zero
  Wire.write(reg);
  //end transmission
  Wire.endTransmission();
  //request 1 byte from address xx
  Wire.requestFrom(address, 2); // 2 bytes?
  //wait for response
  while(Wire.available() == 0);
  //put the temperature in variable c
  int c = Wire.read();   
  return c;
}
