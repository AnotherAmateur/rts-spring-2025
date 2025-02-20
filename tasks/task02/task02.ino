uint8_t intNum;
const int ITERS_COUNT = 100; 

volatile int signalPeriods[ITERS_COUNT];
volatile int index = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  intNum = digitalPinToInterrupt(2);
  attachInterrupt(intNum, captureSignal, RISING);
}

void loop() {
  if (index == ITERS_COUNT) {
    unsigned long sum = 0;
    index = 0;

    for (int i = 0; i < ITERS_COUNT; i++) {
      sum += signalPeriods[i];
    }

    int averagePeriod = sum / ITERS_COUNT;
    float rmsd = 0;

    for (int i = 0; i < ITERS_COUNT; i++) {
      rmsd += pow(signalPeriods[i] - averagePeriod, 2);
    }

    rmsd /= ITERS_COUNT;
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
  static unsigned long lastTime = 0;

  if (lastTime != 0) {
    signalPeriods[index] = currentTime - lastTime;
    index++;
  }

  lastTime = currentTime;

  if (index == ITERS_COUNT) {
    detachInterrupt(intNum);
  }
}