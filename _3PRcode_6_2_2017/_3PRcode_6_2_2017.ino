int out = 5;
int pr1 = 15;
int pr2 = 17;
int pr3 = 19;
int pr1val = 0;
int pr2val = 0;
int pr3val = 0;
const int _delay = 200;
const int _threshold = 590;

void setup() {
  pinMode(out, OUTPUT);
  pinMode(pr1, INPUT);
  pinMode(pr2, INPUT);
  pinMode(pr3, INPUT);
  pinMode(8, INPUT);
}

void loop() {
    pr1val = analogRead(pr1);
    pr2val = analogRead(pr2);
    pr3val = analogRead(pr3);

    Serial.print(pr1val);
    Serial.print("\t");
    Serial.print(pr2val);
    Serial.print("\t");
    Serial.print(pr3val);
    Serial.print("\t");
    Serial.print(millis());
    Serial.println();
      
    bool _12 = pr1val > _threshold && pr2val > _threshold;
    bool _13 = pr1val > _threshold && pr3val > _threshold;
    bool _23 = pr2val > _threshold && pr3val > _threshold;

    if (_12 || _13 || _23)
      digitalWrite(out, LOW);
    else
      digitalWrite(out, HIGH);

    delay(_delay);
}
