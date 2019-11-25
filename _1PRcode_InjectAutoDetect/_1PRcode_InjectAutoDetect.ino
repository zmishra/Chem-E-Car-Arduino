int out = 5;
int pr1 = 15;
int pr1val = 0;
unsigned long startTime = 0;
unsigned long lastButtonPress = 0;
const int _delay = 200;
const int stdev = 100;

int count = 0;
int countB = 0;
int sumB1 = 0;
int sum1 = 0;
int RAB1 = 0;
int RA1 = 0;

int state = 0;
bool initialDelay = true;
bool injectionSensed = false;

void setup() {
  pinMode(out, OUTPUT);
  pinMode(pr1, INPUT);
  pinMode(8, INPUT);
  attachInterrupt(8, switchBitch, FALLING);
}

void switchBitch()
{
  if (millis() < lastButtonPress + 500)
    return;
  if (state == 0)
  {
    state = 1;
  }
  else if (state == 1)
  {
    state = 0;
    count = 0;
    countB = 0;
    sumB1 = 0;
    sum1 = 0;
    RAB1 = 0;
    RA1 = 0;
    initialDelay = true;
    injectionSensed = false;
  }
  lastButtonPress = millis();
  Serial.println("Switched");
}

void loop() {
  while (state == 0) 
  {
    countB++;
    pr1val = analogRead(pr1);
    sumB1 += pr1val;
    RAB1 = sumB1 / countB;
    digitalWrite(5, LOW);
  }
  while (state == 1)
  {
    if(!injectionSensed)
      injectionSensed = (analogRead(pr1) > RAB1 + 150);
    else
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
}
