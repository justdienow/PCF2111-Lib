#define PIN_DLEN 8
#define PIN_CLB  9
#define PIN_DATA 10

void shiftBit(byte value) {
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

void setup() {
  Serial.begin(115200);

  pinMode(PIN_DLEN, OUTPUT);
  digitalWrite(PIN_DLEN, LOW);
  pinMode(PIN_CLB , OUTPUT);
  digitalWrite(PIN_CLB, LOW);
  pinMode(PIN_DATA, OUTPUT);
  digitalWrite(PIN_DATA, LOW);


}

void loop() {
    //
}