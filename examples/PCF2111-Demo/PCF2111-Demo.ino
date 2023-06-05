#include <PCF2111.h>

#define PIN_DLEN 8
#define PIN_CLB  9
#define PIN_DATA 10

PCF2111 display(PIN_DLEN, PIN_CLB, PIN_DATA);

void setup() {
  Serial.begin(115200);

  // Write some static numbers to the display
  display.writeDisplay(0, 1);
  display.writeDisplay(1, 2);
  display.writeDisplay(2, 3);
  display.writeDisplay(3, 4);
  display.writeDisplay(4, 5);
  display.writeDisplay(5, 6);
  display.writeDisplay(6, 7);
  display.writeDisplay(7, 8);
  delay(500);
}

void loop() {
  // Cycle through each digit position and write a '0'
  for (byte i = 0; i < 8; i++) {
    display.writeDisplay(i, 0);
    delay(250);
  }
  
  // Cycle through each digit position and write count from '0' to 'F'
  for (byte i = 0; i < 8; i++) {
    for (byte j = 0; j < 16; j++) {
      display.writeDisplay(i, j);
      delay(250);
    }    
  }

  // Cycle through each digit position and write a '8'
  for (byte i = 0; i < 8; i++) {
    display.writeDisplay(i, 8);
    delay(250);
  }
}