// https://github.com/TriodeGirl/Arduino_Direct_Register_Operations

#define PORTBASE 0x40040000

#define PFS_P104PFS_BY ((volatile unsigned char  *)(PORTBASE + 0x0843 + ( 4 * 4))) // D3
#define PFS_P102PFS_BY ((volatile unsigned char  *)(PORTBASE + 0x0843 + ( 2 * 4))) // D5
#define PFS_P106PFS_BY ((volatile unsigned char  *)(PORTBASE + 0x0843 + ( 6 * 4))) // D6
#define PFS_P303PFS_BY ((volatile unsigned char  *)(PORTBASE + 0x08C3 + ( 3 * 4))) // D9
#define PFS_P112PFS_BY ((volatile unsigned char  *)(PORTBASE + 0x0843 + (12 * 4))) // D10

const uint16_t PERIOD_PIN3 = 10000;
const uint16_t PERIOD_PIN5 = 1000;
const uint16_t PERIOD_PIN6 = 500;
const uint16_t PERIOD_PIN9 = 100;
const uint16_t PERIOD_PIN10 = 50;

void setup() {
  *PFS_P104PFS_BY = 0x04; // нулевой бит устанавливает HIGH/LOW, второй - I/O
  *PFS_P102PFS_BY = 0x04;
  *PFS_P106PFS_BY = 0x04;
  *PFS_P303PFS_BY = 0x04;
  *PFS_P112PFS_BY = 0x04;
}

void loop() {
    static unsigned long lastTime1 = 0;
    static unsigned long lastTime2 = 0;
    static unsigned long lastTime3 = 0;
    static unsigned long lastTime4 = 0;
    static unsigned long lastTime5 = 0;

    unsigned long now = micros();

    if (now - lastTime1 >= PERIOD_PIN3) {
        *PFS_P104PFS_BY ^= 0x01;
        lastTime1 = now;
    }
    if (now - lastTime2 >= PERIOD_PIN5) {
        *PFS_P102PFS_BY ^= 0x01;
        lastTime2 = now;
    }
    if (now - lastTime3 >= PERIOD_PIN6) {
        *PFS_P106PFS_BY ^= 0x01;
        lastTime3 = now;
    }
    if (now - lastTime4 >= PERIOD_PIN9) {
        *PFS_P303PFS_BY ^= 0x01;
        lastTime4 = now;
    }
    if (now - lastTime5 >= PERIOD_PIN10) {
        *PFS_P112PFS_BY ^= 0x01;
        lastTime5 = now;
    }
}