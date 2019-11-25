/* Include the software serial port library */

const int interrupt_pin = 12;
const int gate = 2;
const int drain = 1;
const int pr1 = 15; //pr = photoresistor
const int pr2 = 17;
const int pr3 = 19;
unsigned long time_interval = 500;//milliseconds
const int epsilon = 240;
bool turnoff = false;
volatile unsigned long t_zero;
float reading1;
float reading2;
float reading3;
volatile bool started = false;
float m_max1 = 0;
float m_max2 = 0;
float m_max3 = 0;


void setup() {
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  Serial3.begin(9600);
  delay(time_interval);  // Short delay, wait for the Mate to send back CMD
  initializePins();
}

void loop() {

  checkIfEnd();

  reading1 = analogRead(pr1);
  reading2 = analogRead(pr2);
  reading3 = analogRead(pr3);
  
  if (reading1 > m_max1)
  {
    m_max1 = reading1;
  }
  if (reading2 > m_max2)
  {
    m_max2 = reading2;
  }
  if (reading3 > m_max3)
  {
    m_max3 = reading3;
  }

  printPRs();
  delay(time_interval);
}

void startTimer(){
  t_zero = millis()/1000.0;//in seconds
  started = true;
  //digitalWrite(gate, HIGH);
  detachInterrupt(interrupt_pin);
}

void checkIfEnd(){
  bool t1 = reading1/m_max1 <= 0.8;
  bool t2 = reading2/m_max2 <= 0.8;
  bool t3 = reading3/m_max3 <= 0.8;
  
  if (t1 && t2)
  {
    Serial.println("covered 1 & 2");
    Serial3.println("covered 1 & 2");
    turnoff = true;
  }
  else if(t1 && t3)
  {
    Serial.println("covered 1 & 3");
    Serial3.println("covered 1 & 3");
    turnoff = true;
  }
  else if (t2 && t3)
  {
    Serial.println("covered 2 & 3");
    Serial3.println("covered 2 & 3");
    turnoff = true;
  }
  if (turnoff)
  {
    digitalWrite(gate, LOW);
    Serial.println("END");
    Serial3.println("END");
    while(1) {}
  }
}
void initializePins(){
  pinMode(gate, OUTPUT);
  digitalWrite(gate, HIGH);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin), startTimer, RISING);
}

const void printPRs(){
  Serial.print(millis()/1000.0 - t_zero);
  Serial.print(",");   
  Serial.print(reading1/m_max1,2);    
  Serial.print(",");                   
  Serial.print(reading2/m_max2,2);    
  Serial.print(","); 
  Serial.print(reading3/m_max3,2);     
  Serial.println();        

  Serial3.print(millis()/1000.0 - t_zero);
  Serial3.print(",");   
  Serial3.print(reading1/m_max1,2);    
  Serial3.print(",");                   
  Serial3.print(reading2/m_max2,2);    
  Serial3.print(","); 
  Serial3.print(reading3/m_max3,2);     
  Serial3.println(); 
}


