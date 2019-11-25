int state = 0;

void setup() {
  pinMode(8, INPUT);
  pinMode(13, OUTPUT);
  attachInterrupt(8, switchBitch, FALLING);
}

void switchBitch()
{
  if (state == 0)
    state = 1;
   else if (state == 1)
    state = 0;
}

void loop() {
  while (state == 0){digitalWrite(13,LOW);}
  while (state == 1){digitalWrite(13, HIGH);}
}
