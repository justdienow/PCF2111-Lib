#include <PCF2111.h>

#define PIN_DLEN 8
#define PIN_CLB  9
#define PIN_DATA 10

PCF2111 display(PIN_DLEN, PIN_CLB, PIN_DATA);

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
    Serial.begin(115200);
    display.begin();
}

void loop() {
//   unsigned long currentMillis = millis();
//   if (currentMillis - previousMillis >= interval) {
//     previousMillis = currentMillis;
//     Serial.println("----");

//     displayData[bp][digit] += 1;

//     Serial.print("displayData[bp][digit] :: ");
//     Serial.println(displayData[bp][digit]);

//     updateDisplay();
//     Serial.println("----");
//   }
}
