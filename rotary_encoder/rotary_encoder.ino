#include <Bounce.h>

const int encoderPinA = 15;
const int encoderPinB = 16;

int angle = 0;

int encoderPos = 0;
int encoderStepsPerRevolution = 24;

boolean encoderALast = LOW; //remembers the previous state of the encoder pin A

Bounce rotaryA = Bounce(encoderPinA,5);
Bounce rotaryB = Bounce(encoderPinB,5);

void setup() {
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  digitalWrite(encoderPinA, HIGH);
  digitalWrite(encoderPinB, HIGH);
  Serial.begin(9600);
}

void loop() {
  if (rotaryA.update() || rotaryB.update())
  {
  boolean encoderA = digitalRead(encoderPinA);

  if ((encoderALast == HIGH) && (encoderA == LOW))
  {
    if (digitalRead(encoderPinB) == LOW)
    {
      encoderPos--;
    }
    else
    {
      encoderPos++;
    }
    angle = (encoderPos % encoderStepsPerRevolution) * 360 / encoderStepsPerRevolution;
    Serial.print(encoderPos);
    Serial.print(" ");
    Serial.println(angle);
  }
  encoderALast = encoderA;
  }
}

