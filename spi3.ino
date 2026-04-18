int latchPin = 4;
int clockPin = 7;
int dataPin  = 8;

#define A 0x01
#define B 0x02
#define C 0x04
#define D 0x08
#define E 0x10
#define F 0x20
#define G 0x40

uint8_t segment[10] = {
  A|B|C|D|E|F,        
  F|E,               
  A|B|G|E|D,          
  A|B|G|C|D,          
  F|G|B|C,           
  A|F|G|C|D,          
  A|F|E|D|C|G,        
  A|B|C,             
  A|B|C|D|E|F|G,     
  A|B|C|G|F           
};

uint8_t digitCode[4] = {0x0E, 0x0D, 0x0B, 0x07};

bool COMMON_ANODE = true;

uint8_t getSeg(uint8_t num) {
  if (COMMON_ANODE)
    return ~segment[num];
  else
    return segment[num];
}

void send(uint8_t seg, uint8_t dig) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, seg);
  shiftOut(dataPin, clockPin, MSBFIRST, dig);
  digitalWrite(latchPin, HIGH);
}

void clearAll() {
  send(0x00, 0x0F);
}

void displayNumber(int num) {

  int d[4];

  d[0] = num / 1000;
  d[1] = (num / 100) % 10;
  d[2] = (num / 10) % 10;
  d[3] = num % 10;

  for (int i = 0; i < 4; i++) {
    clearAll();
    send(getSeg(d[i]), digitCode[i]);
    delayMicroseconds(800);
  }
}

int count = 0;
unsigned long prevTime = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {

  displayNumber(count);

  if (millis() - prevTime >= 100) {
    prevTime = millis();
    count++;

    if (count > 1000)
      count = 0;
  }
}