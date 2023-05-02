#define PIN_DLEN 8
#define PIN_CLB  9
#define PIN_DATA 10

#define DATA_COUNT 4
byte displayData[2][DATA_COUNT] = {{0,0,0,0},{0,0,0,0}};

byte activeBP = 0;
byte number = 0;
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;   // will store last time LCD was updated
// constants won't change:
const long interval = 1000;         // interval at which to update the LCD

void setup() {
  Serial.begin(115200);

  pinMode(PIN_DLEN, OUTPUT);
  digitalWrite(PIN_DLEN, LOW);
  pinMode(PIN_CLB , OUTPUT);
  digitalWrite(PIN_CLB, LOW);
  pinMode(PIN_DATA, OUTPUT);
  digitalWrite(PIN_DATA, LOW);
}

void shiftBit(byte value) {
  // Serial.print("shiftBit value:: ");
  // Serial.println(value);
  digitalWrite(PIN_CLB, HIGH);
  digitalWrite(PIN_DATA, value);
  digitalWrite(PIN_CLB, LOW);
}

void shiftByte(byte value) {
  byte tmp = value;
  for(byte c=0; c<8; c++) {
    shiftBit(tmp & 1);
    tmp = tmp >> 1;
  }
}

void updateDisplay() {
  activeBP ^= 0x01;

  Serial.print("In updateDisplay() - activeBP :: ");
  Serial.println(activeBP);

  digitalWrite(PIN_DLEN, HIGH);
  shiftBit(0);                  // leading zero

  for(byte c=0; c < DATA_COUNT; c++) {
    shiftByte(displayData[activeBP][c]);
  }

  shiftBit(activeBP);           // load bit
  digitalWrite(PIN_DLEN, LOW);
  shiftBit(0);                  // load pulse
}

byte bp = 1;
byte digit = 0;
void loop() {
  unsigned long currentMillis = millis();
  while (Serial.available()==0){} // wait for user input
  number = (byte)Serial.parseInt();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Serial.println("----");
    Serial.print("Number :: ");
    Serial.println(number);
    //  displayData[bp][digit] += 1;
    displayData[bp][digit] = number;
    // displayData[0][1] = displayData[0][0];
    // displayData[0][2] = displayData[0][0];
    // displayData[0][3] = displayData[0][0];
    // displayData[1][0] = displayData[0][0];
    // displayData[1][1] = displayData[0][0];
    // displayData[1][2] = displayData[0][0];
    // displayData[1][3] = displayData[0][0];

    Serial.print("displayData[bp][digit] :: ");
    Serial.println(displayData[bp][digit]);
    // Serial.print("displayData[1][0] :: ");
    // Serial.println(displayData[1][0]);
    // Serial.print("displayData[0][2] :: ");
    // Serial.println(displayData[0][2]);
    // Serial.print("displayData[0][3] :: ");
    // Serial.println(displayData[0][3]);

    updateDisplay();
    Serial.println("----");
  }
}
