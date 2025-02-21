uint8_t intNum;

const int MARGIN = 2;
const int ITERS_COUNT = 100 + MARGIN;

volatile int signalPeriods[ITERS_COUNT];
volatile int index = 0;
volatile unsigned long lastTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  intNum = digitalPinToInterrupt(2);
  attachInterrupt(intNum, captureSignal, RISING);
}

void loop() {
  if (index >= ITERS_COUNT) {
    unsigned long sum = 0;
    index = 0;

    for (int i = MARGIN; i < ITERS_COUNT; i++) {
      sum += signalPeriods[i];
    }

    int averagePeriod = sum / (ITERS_COUNT - MARGIN);
    float rmsd = 0;

    for (int i = MARGIN; i < ITERS_COUNT; i++) {
      rmsd += pow(signalPeriods[i] - averagePeriod, 2);
    }

    rmsd /= (ITERS_COUNT - MARGIN);
    rmsd = sqrt(rmsd);

    Serial.print("Period: ");
    Serial.println(averagePeriod);
    Serial.print("rmsd: ");
    Serial.println(rmsd);

    attachInterrupt(intNum, captureSignal, RISING);
  }
}

void captureSignal() {
  unsigned long currentTime = micros();
  signalPeriods[index++] = currentTime - lastTime;
  lastTime = currentTime;

  if (index >= ITERS_COUNT) {
    detachInterrupt(intNum);
  }
}