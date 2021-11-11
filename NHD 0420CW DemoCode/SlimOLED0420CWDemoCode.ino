/*****************************************************************************
 
 Program for writing to Newhaven Display's NHD - 0420CW
 This code is written for the Arduino Uno.
 Copyright (c) 2021 - Newhaven Display International, Inc.
 Newhaven Display invests time and resources providing this open source code,
 please support Newhaven Display by purchasing products from Newhaven Display!
 Author: Zachary Palrang - Applications Engineer
 
 *****************************************************************************/

#define SCL 12 // Serial CLOCK
#define SDI 11 // Serial Data IN
#define CS 9   // Chip Select

void setCS()
{
  digitalWrite(CS, HIGH); // END of data Line
}

void clearCS()
{
  digitalWrite(CS, LOW); // CS MUST be low for that transfer of data
  delayMicroseconds(1);
}

void clockCycle()
{
  digitalWrite(SCL, LOW);  // Beginning of CLOCK Cycle
  delayMicroseconds(1);
  digitalWrite(SCL, HIGH);
  delayMicroseconds(1);
  digitalWrite(SCL, LOW); // Ending of CLOCK Cycle
  delayMicroseconds(1);
}

void putData (uint8_t data)
{
  for (int m = 0; m < 8; m++) 
  {
    if ((data & 0x01) == 0x01) // Comapring the LSB i.e. (0000 0001)
    {
      digitalWrite(SDI, HIGH);
    } else {
      digitalWrite(SDI, LOW);
    }
    while (0);
    data = (data >> 1); // Left Shift 1 bit to be compared
    clockCycle();
  }
}

void command(unsigned char data) // Command Writing Function
{
  uint8_t firstByte = data & 0x0F; // Clear upper nibble.
  uint8_t secondByte = (data >> 4) & 0x0F; // Right shift by 4 and clear upper nibble.

  clearCS();

  // Send 0b00011111 to enter command write mode
  uint8_t writeCommand = 0b00011111;
  putData(writeCommand);

  putData(firstByte);
  putData(secondByte);

  clearCS();
}

void data(unsigned char data)
{
  unsigned int m;

  uint8_t firstByte = data & 0x0F; // Clear upper nibble.
  uint8_t secondByte = (data >> 4) & 0x0F; // Right shift by 4 and clear upper nibble.

  clearCS();

  // Send 0b00011111 to enter data write mode
  uint8_t writeData = 0b01011111;
  putData(writeData);

  putData(firstByte);
  putData(secondByte);

  setCS();
}

void StartMessage()
{                
  // Intitial System Message
  command(0x01); // Clear the display
  delay(1);
  command(0x02); // Return Home
  delay(1);

  data(0x1F); //Block

  for(int i = 0; i < 18; i++)
  {
    data(0xD6); //Block
  }

  data(0x1F); //Block
  data(0x1F); //Block

  data(' '); //Space
  data(' '); //Space
  data('S');
  data('l');
  data('i');
  data('m');
  data(' '); //Space
  data('O');
  data('l');
  data('e');
  data('d');
  data(' '); //Space
  data('D');
  data('e');
  data('m');
  data('o');
  data(' '); //Space
  data(' '); //Space

  data(0x1F); //Block
  data(0x1F); //Block

  data(' '); //Space
  data('N');
  data('e');
  data('w');
  data('h');
  data('a');
  data('v');
  data('e');
  data('n');
  data(' '); //Space
  data('D');
  data('i');
  data('s');
  data('p');
  data('l');
  data('a');
  data('y');
  data(' '); //Space

  for(int i = 0; i < 21; i++)
  {
    data(0x1F); //Block
  }
}

void Right()
{                
  // Shift Right Section

  for(int i = 0; i < 23; i++)
  {
    data(' ');    //Space
  }

  data('S');    //S
  data('c');    //c
  data('r');    //r
  data('o');    //o
  data('l');    //l
  data('l');    //l
  data(' ');    //Space
  data('R');    //R
  data('i');    //i
  data('g');    //g
  data('h');    //h
  data('t');    //t

  for(int i = 0; i < 7; i++)
  {
    data(' ');    //Space
  }

  for(int i = 0; i < 7; i++)
  {
    data(0xDF);    // >
    data(' ');    //Space
  }

  for(int i = 0; i < 24; i++)
  {
    data(' ');    //Space
  }

  for(int i = 0; i < 42; i++)
  {
    command(0x1C); // Shift to right
    delay(100);    // Time delay between shifts
  }
}

void Left()
{                
  //Shift Left Section

  for(int i = 0; i < 23; i++)
  {
    data(' ');    //Space
  }

  data('S');
  data('c');
  data('r');
  data('o');
  data('l');
  data('l');
  data(' '); //Space
  data('L');
  data('e');
  data('f');
  data('t');

  for(int i = 0; i < 8; i++)
  {
    data(' ');    //Space
  }

  for(int i = 0; i < 7; i++)
  {
    data(0xE1);    // <
    data(' ');    //Space
  }

  for(int i = 0; i < 24; i++)
  {
    data(' ');    //Space
  }

  for(int i = 0; i < 42; i++)
  {
    command(0x18); // Shift to left
    delay(100);    // Time delay between shifts
  }
}

void Unique()
{             
  //Display Special Characters

  for(int i = 0; i < 5; i++)
  {
    data(' '); //Space
  }

  data('C'); //C
  data('h'); //h
  data('a'); //a
  data('r'); //r
  data('a'); //a
  data('c'); //c
  data('t'); //t
  data('e'); //e
  data('r'); //r
  data('s'); //s

  for(int i = 0; i < 5; i++)
  {
    data(' '); //Space
  }

  // Print numbers (0123456789)
  for(int i = 0x30; i <= 0x39; i++)
  {
    data(i);
  }

  // Print special characters 
  // (! " #   % & ' ( ) * + , . / )
  for(int i = 0x21; i <= 0x2F; i++)
  {
    data(i);
  }

  // Print special characters 
  // (: ; < = > ?)
  for(int i = 0x3A; i <= 0x3F; i++)
  {
    data(i);
  }

  // Print special characters 
  // ( +- >- <- u(micro) (music symbol) (music symbol) Bell Heart Diamond FlowerT LCBracketL BRBracketL " ")
  for(int i = 0x8C; i <= 0x99; i++)
  {
    data(i);
  }

  data(0xA2); //$
  data(0xB1); //Cents

  data(0xB4); //Lambda
  data(0xB5); //Omega
  data(0xB6); //Pi
  data(0xB7); //Fork
  data(0xB8); //Sum

  data(0xDE); //-^
  data(0xDF); //->
  data(0xE0); //-v
  data(0xE1); //<-

  data(0xFD); //{
  data(0xFF); //}0

  data(0x14); //<<
  data(0x15); //>>
}

void Clear()
{
  delay(200);
  command(0x01); // Clear display
  command(0x02); // Return Home (0,0)
}

void initialize()
{
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

void Big()
{                // Code for Double Height
  command(0x2A); // Function Set (extended command set)
  command(0x1D); // Double Height Enabled
  command(0x2D); // Double Line Enabled
  command(0x2A); // Function Set (extended command set)
  command(0x1F); // Display Shirt Enabled
  data(0x20);    //Space
  data(0x20);    //Space
  data(0x20);    //Space
  data(0x44);    //D
  data(0x6F);    //o
  data(0x75);    //u
  data(0x62);    //b
  data(0x6C);    //l
  data(0x65);    //e
  data(0x20);    //Space
  data(0x48);    //H
  data(0x65);    //e
  data(0x69);    //i
  data(0x67);    //g
  data(0x68);    //h
  data(0x74);    //t
  data(0x20);    //Space
  data(0x20);    //Space
  data(0x20);    //Space
  data(0x20);    //Space
  data(0x20);    //Space
  data(0x20);    //Space
  data(0x20);    //Space
  data(0x20);    //Space
  data(0x43);    //C
  data(0x68);    //h
  data(0x61);    //a
  data(0x72);    //r
  data(0x61);    //a
  data(0x63);    //c
  data(0x74);    //t
  data(0x65);    //e
  data(0x72);    //r
  data(0x73);    //s
  data(0x21);    //!
}

void setup()
{
  pinMode(9, OUTPUT);  // Declaring  CS as OUTPUT
  pinMode(11, OUTPUT); // Delcaring SDI as OUTPUT
  pinMode(12, OUTPUT); // Declaring SCL as OUTPUT

  initialize();            // Initialization
  StartMessage();      // Start Message
  delay(5000);
  Clear(); // Clear Screen
}

void loop()
{
  Right(); // Scroll Right
  Clear(); // Clear Screen
  delay(100);

  Left();  // Scroll Left
  Clear(); // Clear Screen
  delay(100);

  Unique(); // Show Unique Characters
  delay(7500);

  Clear(); // Clear Screen
  Big();   // Double Height Characters
  delay(7500);

  Clear();  // Clear Screen
  initialize(); // ReInitializae
}
