int latchPin = 4;
int clockPin = 7;
int dataPin  = 8;

void send(uint8_t seg, uint8_t dig) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, seg);
  shiftOut(dataPin, clockPin, MSBFIRST, dig);
  digitalWrite(latchPin, HIGH);
}

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {

  for (int i = 0; i < 100; i++) {
    send(0x00, 0x0E); delay(2);
    send(0x00, 0x0D); delay(2);
    send(0x00, 0x0B); delay(2);
    send(0x00, 0x07); delay(2);
  }

  for (int i = 0; i < 100; i++) {
    send(0xFF, 0x0F); delay(2);  
  }
}