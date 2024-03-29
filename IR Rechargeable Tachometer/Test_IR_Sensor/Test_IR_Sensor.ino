const int IRPin = 2;

volatile int count = 0;

volatile bool tooSlow = false;

void setup() {
  //Setup should be done without any interrupts
  noInterrupts();
  
  //Set IR pin as input pin
  pinMode(IRPin,INPUT);

  attachInterrupt(digitalPinToInterrupt(IRPin), resetTimer, FALLING);
  
  //Initialize Timer 1
  TCCR1A = 0;
  TCCR1B = 0;
  
  //Set prescaler 256
  TCCR1B |= (1 << CS12);

  //Set the timer in overflow mode
  TIMSK1 |= (1 << TOIE1);

  TCNT1 = 0;

  Serial.begin(9600);

  //Enable all the interrupts
  interrupts();
}

void loop() {
  Serial.println(count);

  if(tooSlow==true){
    Serial.println("TOO SLOW!");
  }

  delay(500);
}

ISR(TIMER1_OVF_vect){
  tooSlow = true;
}

void resetTimer(){
  count = TCNT1;
  TCNT1 = 0;
}

