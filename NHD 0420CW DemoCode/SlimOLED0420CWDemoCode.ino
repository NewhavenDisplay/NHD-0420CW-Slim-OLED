/*****************************************************************************
 
 Program for writing to Newhaven Display's NHD - 0420CW
 This code is written for the Arduino Uno.
 Copyright (c) 2021 - Newhaven Display International, Inc.
 Newhaven Display invests time and resources providing this open source code,
 please support Newhaven Display by purchasing products from Newhaven Display!
 Author: Zachary Palrang - Applications Engineer
 
 *****************************************************************************/
 
# define SCL 12 // Serial CLOCK
# define SDI 11 // Serial Data IN
# define CS 9 // Chip Select

void command(unsigned char i) // Command Writing Function
{unsigned int m;
digitalWrite(CS,LOW);    // CS MUST be low for that transfer of data
delayMicroseconds(1);
digitalWrite(SDI,HIGH);   // 1st - '1' of STARTING byte
digitalWrite(SCL,LOW);   // Beginning of CLOCK Cycle
digitalWrite(SCL,HIGH);
digitalWrite(SCL,LOW);   // Ending of CLOCK Cycle
delayMicroseconds(1);
digitalWrite(SDI,HIGH);  // 2nd - '1' of STARTING byte
digitalWrite(SCL,LOW);
digitalWrite(SCL,HIGH);
digitalWrite(SCL,LOW);
delayMicroseconds(1);
digitalWrite(SDI,HIGH);  // 3rd - '1' of STARTING byte
digitalWrite(SCL,LOW);
digitalWrite(SCL,HIGH);
digitalWrite(SCL,LOW);
delayMicroseconds(1);
digitalWrite(SDI,HIGH); // 4th - '1' of STARTING byte
digitalWrite(SCL,LOW);
digitalWrite(SCL,HIGH);
digitalWrite(SCL,LOW);
delayMicroseconds(1);
digitalWrite(SDI,HIGH); // 5th - '1' of STARTING byte
digitalWrite(SCL,LOW);
digitalWrite(SCL,HIGH);
digitalWrite(SCL,LOW);
delayMicroseconds(1);
digitalWrite(SDI,LOW);  // Writing to the Slim OLED
digitalWrite(SCL,LOW);
digitalWrite(SCL,HIGH);
digitalWrite(SCL,LOW);
delayMicroseconds(1);
digitalWrite(SDI,LOW);  //LOW FOR COMMAND funtion on DC bit 
digitalWrite(SCL,LOW);
digitalWrite(SCL,HIGH);
digitalWrite(SCL,LOW);
delayMicroseconds(1);
digitalWrite(SDI,LOW);  // Final 0 bit to end starting byte
digitalWrite(SCL,LOW);
digitalWrite(SCL,HIGH);
digitalWrite(SCL,LOW);
for(m=0;m<=3;m++)      // First 4 bits of data retrieval
{
  if((i&0x01)==0x01)   // Comapring the LSB i.e. (0000 0001)
  digitalWrite(SDI,HIGH);
  else 
  digitalWrite(SDI,LOW);
  while(0);
  i=(i>>1);            // Left Shift 1 bit to be compared 

  digitalWrite(SCL,LOW);
  while(0);
  digitalWrite(SCL,HIGH);
  while(0);
  digitalWrite(SCL,LOW);
}
for(m=4;m<=7;m++)      // Next 4 bits of information all dummy vaulues '0' 
{
digitalWrite(SDI,LOW);
digitalWrite(SCL,LOW);
delayMicroseconds(1);
digitalWrite(SCL,HIGH);
delayMicroseconds(1);
digitalWrite(SCL,LOW);
delayMicroseconds(1);}
for(m=8;m<=11;m++)     // Next 4 bits
{
  if((i&0x01)==0x01)
  digitalWrite(SDI,HIGH);     
  else 
  digitalWrite(SDI,LOW);
  while(0);
  i=(i>>1);
  digitalWrite(SCL,LOW);
  while(0);
  digitalWrite(SCL,HIGH);
  while(0);
  digitalWrite(SCL,LOW);
}
for(m=12;m<=15;m++)    // Last 4 bits
{
digitalWrite(SDI,LOW);  
digitalWrite(SCL,LOW);
delayMicroseconds(1);
digitalWrite(SCL,HIGH);
delayMicroseconds(1);
digitalWrite(SCL,LOW);
delayMicroseconds(1);}
digitalWrite(CS,HIGH);  // END of data Line
}

void data(unsigned char i)
{unsigned int m;
digitalWrite(CS,LOW);    // Start of data transfer
delayMicroseconds(1);
digitalWrite(SDI,HIGH);  // 1st - '1'
digitalWrite(SCL,LOW);
digitalWrite(SCL,HIGH);
digitalWrite(SCL,LOW);
delayMicroseconds(1);
digitalWrite(SDI,HIGH);  // 2nd - '1'
digitalWrite(SCL,LOW);
digitalWrite(SCL,HIGH);
digitalWrite(SCL,LOW);
delayMicroseconds(1);
digitalWrite(SDI,HIGH);  // 3rd - '1'
digitalWrite(SCL,LOW);
digitalWrite(SCL,HIGH);
digitalWrite(SCL,LOW);
delayMicroseconds(1);
digitalWrite(SDI,HIGH);  // 4th - '1'
digitalWrite(SCL,LOW);
digitalWrite(SCL,HIGH);
digitalWrite(SCL,LOW);
delayMicroseconds(1);
digitalWrite(SDI,HIGH); // 5th - '1'
digitalWrite(SCL,LOW);
digitalWrite(SCL,HIGH);
digitalWrite(SCL,LOW);
delayMicroseconds(1);
digitalWrite(SDI,LOW);  // Write
digitalWrite(SCL,LOW);
digitalWrite(SCL,HIGH);
digitalWrite(SCL,LOW);
delayMicroseconds(1);
digitalWrite(SDI,HIGH); // HIGH for DATA
digitalWrite(SCL,LOW);
digitalWrite(SCL,HIGH);
digitalWrite(SCL,LOW);
delayMicroseconds(1);
digitalWrite(SDI,LOW);  // Final 0 bit to end starting byte
digitalWrite(SCL,LOW);
digitalWrite(SCL,HIGH);
digitalWrite(SCL,LOW);
for(m=0;m<=3;m++)       // Bits 0-3
{
  if((i&0x01)==0x01)    // Bit Comparator
  digitalWrite(SDI,HIGH);
  else 
  digitalWrite(SDI,LOW);
  while(0);
  i=(i>>1);
  digitalWrite(SCL,LOW);
  while(0);
  digitalWrite(SCL,HIGH);
  while(0);
  digitalWrite(SCL,LOW);
}
for(m=4;m<=7;m++)       // Bits 4-7 All are LOW = 0
{
digitalWrite(SDI,LOW);
digitalWrite(SCL,LOW);
delayMicroseconds(1);
digitalWrite(SCL,HIGH);
delayMicroseconds(1);
digitalWrite(SCL,LOW);
delayMicroseconds(1);}
for(m=8;m<=11;m++)      // Bits 8-11
{
  if((i&0x01)==0x01)
  digitalWrite(SDI,HIGH);
  else 
  digitalWrite(SDI,LOW);
  while(0);
  i=(i>>1);
  digitalWrite(SCL,LOW);
  while(0);
  digitalWrite(SCL,HIGH);
  while(0);
  digitalWrite(SCL,LOW);
}
for(m=12;m<=15;m++)     // Bits 12-15 All are LOW = 0
{
digitalWrite(SDI,LOW);
digitalWrite(SCL,LOW);
delayMicroseconds(1);
digitalWrite(SCL,HIGH);
delayMicroseconds(1);
digitalWrite(SCL,LOW);
delayMicroseconds(1);}
digitalWrite(CS,HIGH);  //END of the data transfer
delayMicroseconds(1);
}


void StartMessage(){// Intitial System Message
  command(0x01);    // Clear the display
  delay(1);
  command(0x02);    // Return Home
  delay(1);
  data(0x1F);  //Block
  data(0xD6);  //Block
  data(0xD6);  //Block
  data(0xD6);  //Block
  data(0xD6);  //Block
  data(0xD6);  //Block
  data(0xD6);  //Block
  data(0xD6);  //Block
  data(0xD6);  //Block
  data(0xD6);  //Block
  data(0xD6);  //Block
  data(0xD6);  //Block
  data(0xD6);  //Block
  data(0xD6);  //Block
  data(0xD6);  //Block
  data(0xD6);  //Block
  data(0xD6);  //Block
  data(0xD6);  //Block
  data(0xD6);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x53);  //S
  data(0x6C);  //l
  data(0x69);  //i
  data(0x6D);  //m
  data(0x20);  //Space
  data(0x4F);  //O
  data(0x4C);  //l
  data(0x45);  //e
  data(0x44);  //d
  data(0x20);  //Space
  data(0x44);  //D
  data(0x65);  //e
  data(0x6D);  //m
  data(0x6F);  //o
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x20);  //Space
  data(0x4E);  //N
  data(0x65);  //e
  data(0x77);  //w
  data(0x48);  //h
  data(0x61);  //a
  data(0x76);  //v
  data(0x65);  //e
  data(0x6E);  //n
  data(0x20);  //Space
  data(0x44);  //D
  data(0x69);  //i
  data(0x73);  //s
  data(0x70);  //p
  data(0x6C);  //l
  data(0x61);  //a
  data(0x79);  //y
  data(0x20);  //Space
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  data(0x1F);  //Block
  }

void Right(){  // Shift Right Section
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x53);  //S
  data(0x63);  //c
  data(0x72);  //r
  data(0x6F);  //o
  data(0x6C);  //l
  data(0x6C);  //l
  data(0x20);  //Space
  data(0x52);  //R
  data(0x69);  //i
  data(0x67);  //g
  data(0x68);  //h
  data(0x74);  //t
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0xDF);  // >
  data(0x20);  //Space
  data(0xDF);  // >
  data(0x20);  //Space
  data(0xDF);  // >
  data(0x20);  //Space
  data(0xDF);  // >
  data(0x20);  //Space
  data(0xDF);  // >
  data(0x20);  //Space
  data(0xDF);  // >
  data(0x20);  //Space
  data(0xDF);  // >
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  command(0x1C);  // Shift to right  
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
  command(0x1C);  // Shift
  delay(100);     // Time delay between shifts
}

void Left(){   //Shift Left Section
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x53);  //S
  data(0x63);  //c
  data(0x72);  //r
  data(0x6F);  //o 
  data(0x6C);  //l
  data(0x6C);  //l
  data(0x20);  //Space
  data(0x4C);  //L
  data(0x65);  //e
  data(0x66);  //f
  data(0x74);  //t
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0xE1);  // <  
  data(0x20);  //Space
  data(0xE1);  // <
  data(0x20);  //Space
  data(0xE1);  // <
  data(0x20);  //Space
  data(0xE1);  // <
  data(0x20);  //Space
  data(0xE1);  // <
  data(0x20);  //Space
  data(0xE1);  // <
  data(0x20);  //Space
  data(0xE1);  // <
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  command(0x18);  // Shift to left 
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts     
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  command(0x18);  // Shift
  delay(100);     // Time delay between shifts
  }

void Unique(){ //Display Special Characters
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x43);  //C
  data(0x68);  //h
  data(0x61);  //a
  data(0x72);  //r
  data(0x61);  //a
  data(0x63);  //c
  data(0x74);  //t
  data(0x65);  //e
  data(0x72);  //r
  data(0x73);  //s
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x20);  //Space
  data(0x30);  //0
  data(0x31);  //1
  data(0x32);  //2
  data(0x33);  //3
  data(0x34);  //4
  data(0x35);  //5
  data(0x36);  //6
  data(0x37);  //7
  data(0x38);  //8
  data(0x39);  //9
  data(0x21);  //!
  data(0x22);  //"
  data(0x23);  //#
  data(0x24);  //
  data(0x25);  //%
  data(0x26);  //&
  data(0x27);  //'
  data(0x28);  //(
  data(0x29);  //)
  data(0x2A);  //*
  data(0x2B);  //+
  data(0x2C);  //,
  data(0x2D);  //-
  data(0x2E);  //.
  data(0x2F);  ///
  data(0x3A);  //:
  data(0x3B);  //;
  data(0x3C);  //<
  data(0x3D);  //=
  data(0x3E);  //>
  data(0x3F);  //?
  data(0x8C);  //+-
  data(0x8D);  //>-
  data(0x8E);  //<-
  data(0x8F);  //u(micro)
  data(0x90);  //(music symbol)
  data(0x91);  //(music symbol)
  data(0x92);  //Bell
  data(0x93);  //Heart
  data(0x94);  //Diamond
  data(0x95);  //Flower T
  data(0x96);  //LC Bracket L
  data(0x97);  //BR Bracket L
  data(0x98);  //"
  data(0x99);  //"
  data(0xA2);  //$
  data(0xB1);  //Cents
  data(0xB4);  //Lambda
  data(0xB5);  //Omega
  data(0xB6);  //Pi
  data(0xB7);  //Fork
  data(0xB8);  //Sum
  data(0xDE);  //-^
  data(0xDF);  //->
  data(0xE0);  //-v
  data(0xE1);  //<-
  data(0xFD);  //{
  data(0xFF);  //}0
  data(0x14);  //<<
  data(0x15);  //>>
}

void Clear(){
  delay(200);
  command(0x01); // Clear display
  command(0x02); // Return Home (0,0)
}

void zation(){
 command(0x2A); // Function Set (extended command set)
 command(0x71); // Function Selection A
 data(0x5C);    // Enable 5V Regulator
 command(0x28); // Function Set (fundamental command set) 
 command(0x08); // Display off, Cursor off, Blink off
 command(0x2A); // Function Set (extended command set)
 command(0x79); // OLED command set enabled
 command(0xD5); // Set displayed clock divide ratio/oscillator frequency
 command(0x70); // Set displayed clock divide ratio/oscillator frequency
 command(0x78); // OLED command set disabled
 command(0x09); // Extemded function set (4-Lines)
 command(0x06); // COM SEG direction
 command(0x72); // Function selection B
 data(0x00);    // ROM CGRAM
 command(0x28); // Function Set (fundamental command set)
 command(0x79); // OLED command set enabled
 command(0xDA); // Set SEG pins hardware configuration
 command(0x00); // Set SEG pins harware configuration
 command(0xDC); // Function selection C
 command(0x10); // Function selection C
 command(0x81); // Contrast Control
 command(0xFF); // Contrast value of 7F = 127/256
 command(0xD9); // Set phase length
 command(0xF1); // Set phase length
 command(0xDB); // Set VCOMH deselect level
 command(0x40); // Set VCOMH deselect level
 command(0x78); // OLED command set disabled
 command(0x28); // Function SET
 command(0x01); // Clear
 command(0x80); // (1,1) starting point
 command(0x0C); // Display ON
 delay(10);
}

void Big(){       // Code for Double Height
  command(0x2A);  // Function Set (extended command set)
  command(0x1D);  // Double Height Enabled
  command(0x2D);  // Double Line Enabled
  command(0x2A);  // Function Set (extended command set)
  command(0x1F);  // Display Shirt Enabled
  data(0x20);     //Space
  data(0x20);     //Space
  data(0x20);     //Space
  data(0x44);     //D 
  data(0x6F);     //o
  data(0x75);     //u
  data(0x62);     //b
  data(0x6C);     //l
  data(0x65);     //e
  data(0x20);     //Space
  data(0x48);     //H
  data(0x65);     //e
  data(0x69);     //i
  data(0x67);     //g
  data(0x68);     //h
  data(0x74);     //t
  data(0x20);     //Space
  data(0x20);     //Space
  data(0x20);     //Space
  data(0x20);     //Space
  data(0x20);     //Space
  data(0x20);     //Space
  data(0x20);     //Space
  data(0x20);     //Space
  data(0x43);     //C
  data(0x68);     //h
  data(0x61);     //a
  data(0x72);     //r
  data(0x61);     //a
  data(0x63);     //c
  data(0x74);     //t
  data(0x65);     //e
  data(0x72);     //r
  data(0x73);     //s
  data(0x21);     //!
  }


void setup() {
  pinMode(9,OUTPUT);    // Declaring  CS as OUTPUT        
  pinMode(11,OUTPUT);   // Delcaring SDI as OUTPUT
  pinMode(12,OUTPUT);   // Declaring SCL as OUTPUT
  zation();             // Initialization
  StartMessage();       // Start Message
  delay(5000);
  Clear();              // Clear Screen
  }
  
void loop(){
  Right();    // Scroll Right
  Clear();    // Clear Screen
  delay(100);
  Left();     // Scroll Left
  Clear();    // Clear Screen
  delay(100);
  Unique();   // Show Unique Characters
  delay(7500);
  Clear();    // Clear Screen
  Big();      // Double Height Characters
  delay(7500);
  Clear();   // Clear Screen
  zation();  // ReInitializae 
  }
