int out = 5;
int pr1 = 15;
int pr2 = 17;
int pr3 = 19;
int pr1val = 0;
int pr2val = 0;
int pr3val = 0;
unsigned long startTime = 0;
unsigned long lastButtonPress = 0;
const int _delay = 200;
const int stdev = 100;

int count = 0;
int sum1 = 0;
int sum2 = 0;
int sum3 = 0;
int RA1 = 0;
int RA2 = 0;
int RA3 = 0;

int state = 0;
bool initialDelay = true;

void setup() {
  pinMode(out, OUTPUT);
  pinMode(pr1, INPUT);
  pinMode(pr2, INPUT);
  pinMode(pr3, INPUT);
  pinMode(8, INPUT);
  attachInterrupt(8, switchBitch, FALLING);

  count = 0;
  sum1 = 0;
  sum2 = 0;
  sum3 = 0;
  RA1 = 0;
  RA2 = 0;
  RA3 = 0;
}

void switchBitch()
{
  if (millis() < lastButtonPress + 500)
    return;
  if (state == 0)
    state = 1;
  else if (state == 1)
    state = 0;
  lastButtonPress = millis();
  Serial.println("Switched");
}

void loop() {
  while (state == 0) 
  {
    initialDelay = true;
    digitalWrite(5, LOW);
  }
  while (state == 1)
  {
    if (initialDelay)
    {
      delay(5000);
      initialDelay = false;
      startTime = millis();
    }
    count++;
    pr1val = analogRead(pr1);
    pr2val = analogRead(pr2);
    pr3val = analogRead(pr3);
    sum1 += pr1val;
    sum2 += pr2val;
    sum3 += pr3val;
    RA1 = sum1 / count;
    RA2 = sum2 / count;
    RA3 = sum3 / count;

/*
    Serial.print(RA1);
    Serial.print("\t");
    Serial.print(RA2);
    Serial.print("\t");
    Serial.print(RA3);
    Serial.print("\t");
    Serial.print(millis() - startTime);
    Serial.println();*/

    Serial.print(pr1val);
    Serial.print("\t");
    Serial.print(pr2val);
    Serial.print("\t");
    Serial.print(pr3val);
    Serial.print("\t");
    Serial.print(millis() - startTime);
    Serial.println();
      
    bool _12 = pr1val > (RA1 + stdev) && pr2val > (RA2 + stdev);
    bool _13 = pr1val > (RA1 + stdev) && pr3val > (RA3 + stdev);
    bool _23 = pr2val > (RA2 + stdev) && pr3val > (RA3 + stdev);

    if (_12 || _13 || _23)
      digitalWrite(out, HIGH);
    else
      digitalWrite(out, LOW);

    delay(_delay);
  }
}
