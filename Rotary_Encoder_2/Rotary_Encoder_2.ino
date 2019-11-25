#define encoder0PinA  15
#define encoder0PinB  16

volatile unsigned int encoder0Pos = 0;

void setup() {
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(digitalPinToInterrupt(15), doEncoderA, CHANGE);

  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(digitalPinToInterrupt(16), doEncoderB, CHANGE);

  Serial.begin (9600);
}

void loop() {
  //Do stuff here
}

void doEncoderA() {
  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) {

    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = encoder0Pos + 1;         // CW
      Serial.println(encoder0Pos);
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
      Serial.println(encoder0Pos);
    }
  }

  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == HIGH) {
      encoder0Pos = encoder0Pos + 1;          // CW
      Serial.println(encoder0Pos);
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
      Serial.println(encoder0Pos);
    }
  }
  //Serial.println (encoder0Pos, DEC);
  // use for debugging - remember to comment out
}

void doEncoderB() {
  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {

    // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {
      encoder0Pos = encoder0Pos + 1;         // CW
      Serial.println(encoder0Pos);
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
      Serial.println(encoder0Pos);
    }
  }

  // Look for a high-to-low on channel B

  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinA) == LOW) {
      encoder0Pos = encoder0Pos + 1;          // CW
      Serial.println(encoder0Pos);
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
      Serial.println(encoder0Pos);
    }
  }
}
