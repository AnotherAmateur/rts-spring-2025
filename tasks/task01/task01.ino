const uint16_t PERIOD_PIN3 = 1e4;
const uint16_t PERIOD_PIN5 = 1e3;
const uint16_t PERIOD_PIN6 = 500;
const uint16_t PERIOD_PIN9 = 100;
const uint16_t PERIOD_PIN10 = 50;

const uint8_t PIN_3 = 8;
const uint8_t PIN_5 = 32;
const uint8_t PIN_6 = 64;
const uint8_t PIN_9 = 2;
const uint8_t PIN_10 = 4;

void setup() {
    DDRD = 0xff;
    DDRB = 0xff;
}

void loop() {
    static unsigned long lastTime1 = 0;
    static unsigned long lastTime2 = 0;
    static unsigned long lastTime3 = 0;
    static unsigned long lastTime4 = 0;
    static unsigned long lastTime5 = 0;

    unsigned long now = micros();

    if (now - lastTime1 >= PERIOD_PIN3) {
        PORTD ^= PIN_3;
        lastTime1 = now;
    }
    if (now - lastTime2 >= PERIOD_PIN5) {
        PORTD ^= PIN_5;
        lastTime2 = now;
    }
    if (now - lastTime3 >= PERIOD_PIN6) {
        PORTD ^= PIN_6;
        lastTime3 = now;
    }
    if (now - lastTime4 >= PERIOD_PIN9) {
        PORTB ^= PIN_9;
        lastTime4 = now;
    }
    if (now - lastTime5 >= PERIOD_PIN10) {
        PORTB ^= PIN_10;
        lastTime5 = now;
    }
}