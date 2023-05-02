#include <PCF2111.h>

#define PIN_DLEN 8
#define PIN_CLB  9
#define PIN_DATA 10

// PCF2111 display(PIN_DLEN, PIN_CLB, PIN_DATA);

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
    Serial.begin(115200);

    PCF2111 display(PIN_DLEN, PIN_CLB, PIN_DATA);

    // byte** displayDataCopy = display.getDisplayData();
    // for (byte i = 0; i < LCD_BACKPLANE; i++) {
    //     for (byte j = 0; j < DATA_COUNT; j++) {
    //         Serial.print(displayDataCopy[i][j]);
    //         Serial.print(" ");
    //     }
    //     Serial.println();
    // }

    Serial.println("Call updateDisplay() :: BP 0");
    display.updateDisplay(0);
    Serial.println("Call updateDisplay() :: BP 1");
    display.updateDisplay(1);
    
    // for (byte i = 0; i < LCD_BACKPLANE; i++) {
    //     delete[] displayDataCopy[i];
    // }
    // delete[] displayDataCopy;
}

void loop() {
    // unsigned long currentMillis = millis();
    // if (currentMillis - previousMillis >= interval) {
    //     previousMillis = currentMillis;
    //     Serial.println("----");  
    //     // display.updateDisplay();  
    //     Serial.println("----");
    // }
}
