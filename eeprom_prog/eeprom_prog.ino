#include <EEPROM.h>
#define EEPROM_D0 5
#define EEPROM_D7 12

#define AD_A0 2
#define AD_A1 3


// 4-bit hex decoder for common cathode 7-segment display
//byte data[] = { 0x7e, 0x30, 0x6d, 0x79, 0x33, 0x5b, 0x5f, 0x70, 0x7f, 0x7b, 0x77, 0x1f, 0x4e, 0x3d, 0x4f, 0x47 };

int value;
long addr,address,data,fdata;
long data1;
int val;
String stringBit="";
String stringBinary="";
long binaryNumber;
int decimalNumber;

long getaddress() {
  pinMode(AD_A0, INPUT);
  pinMode(AD_A1, INPUT);
  
  
  for (int pin = AD_A0; pin <= AD_A1; pin += 1) {
    val=digitalRead(pin);
    stringBit=String(val);
    stringBinary =stringBit+stringBinary ;
    binaryNumber = stringBinary.toInt();
  }
  addr = convertBinaryToDecimal(binaryNumber);
  binaryNumber = 0;
  val = 0;
  stringBit = "";
  stringBinary = "";
  return addr;
}

long getdata() {
  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {
    pinMode(pin, INPUT);
  }
 
  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {
    val=digitalRead(pin);
    stringBit=String(val);
    stringBinary = stringBinary + stringBit;
    binaryNumber = stringBinary.toInt();
  }
  fdata = convertBinaryToDecimal(binaryNumber);
  binaryNumber = 0;
  val = 0;
  stringBit = "";
  stringBinary = "";
  return fdata;
}

long convertBinaryToDecimal(long binary) {

  long number = binary;
  long decimalVal = 0;
  long baseVal = 1;
  long tempVal = number;
  long previousDigit;

  while (tempVal) {

    //Converts Binary to Decimal
    previousDigit = tempVal % 10;
    tempVal = tempVal / 10;
    decimalVal += previousDigit * baseVal;
    baseVal = baseVal * 2;

  }

  //Returns the Decimal number
  return decimalVal;

}
void writeEEPROM(int address, byte data) {
  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {
    pinMode(pin, OUTPUT);
  }

  for (int pin = EEPROM_D7; pin >= EEPROM_D0; pin -= 1) {
    digitalWrite(pin, data & 1);
    data = data >> 1;
  }
}

void setup()
{
  delay(5000);
  Serial.begin(9600);
  Serial.print("Erasing EEPROM \n");
  for (int address = 0; address<=EEPROM.length() ; address += 1) 
  {
    EEPROM.write(address,255);
  } 
  Serial.print("Erased EEPROM \n");
  for (int address = 0; address <=EEPROM.length(); address += 1) 
  {
    value = EEPROM.read(address);
    Serial.print(address);
    Serial.print(" : ");
    Serial.println(value,DEC);
    writeEEPROM(address, value);
    Serial.print("\n");
    delay(5);
  } 
  pinMode(4, INPUT);
  pinMode(13, INPUT);
  pinMode(A0, INPUT);
    Serial.print("Programmed EEPROM \n");
  for (int address = 0; address <=3; address += 1) 
  {
    value = EEPROM.read(address);
    Serial.print(address);
    Serial.print(" :  ");
    Serial.println(value,DEC);
    writeEEPROM(address, value);
    Serial.print("\n");
    delay(5000);
  } 
}

void loop()
{
  if(digitalRead(A0)==HIGH)
  {
    Serial.print("Program EEPROM \n");
    if(digitalRead(4)==HIGH)
    {
    Serial.print("Enter Address\n");
    address=getaddress();
    delay(5000);
    if(digitalRead(13)==HIGH)
    {
    Serial.print("Enter data to write\n");
    data1=getdata();
    Serial.print(address);
    
    Serial.print(" : ");
    Serial.println(value,DEC);
    EEPROM.write(address, data1);
    delay(5000);
    Serial.print("Programmed EEPROM \n");
    value = EEPROM.read(address);
    Serial.print(address);
    Serial.print(" : ");
    Serial.println(value,DEC);
    writeEEPROM(address, value);
    Serial.print("\n");
    delay(5000);
    }
  }
  } 
  
}
