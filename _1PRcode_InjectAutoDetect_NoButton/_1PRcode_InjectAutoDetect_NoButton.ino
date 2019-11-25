int out = 5;
int pr1 = 15;
int pr1val = 0;
unsigned long startTime = 0;
const int _delay = 200;
const int stdev = 100;

int count = 0;
int countB = 0;
int sumB1 = 0;
int sum1 = 0;
int RAB1 = 0;
int RA1 = 0;

bool initialDelay = true;
bool injectionSensed = false;

void setup() {
  pinMode(out, OUTPUT);
  pinMode(pr1, INPUT);
  pinMode(8, INPUT);
}

void loop() {
  while (!injectionSensed) 
  {
    countB++;
    pr1val = analogRead(pr1);
    injectionSensed = (analogRead(pr1) > RAB1 + 150);
    sumB1 += pr1val;
    RAB1 = sumB1 / countB;
    digitalWrite(5, LOW);
  }
  while (injectionSensed)
  {
    if (initialDelay)
    {
      delay(5000);
      initialDelay = false;
      startTime = millis();
    }
    count++;
    pr1val = analogRead(pr1);
    sum1 += pr1val;
    RA1 = sum1 / count;

/*
    Serial.print(RA1);
    Serial.print("\t");
    Serial.print(millis() - startTime);
    Serial.println();*/

    Serial.print(pr1val);
    Serial.print("\t");
    Serial.print(millis() - startTime);
    Serial.println();

    if (pr1val > (RA1 + stdev))
      digitalWrite(out, HIGH);
    else
      digitalWrite(out, LOW);

    delay(_delay);
  }
}
