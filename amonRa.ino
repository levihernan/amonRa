/*
  amonRa is a function designed to control lamp and fan of an indoor garden

  basic functions:
  sunRaise
  sunSet
  coolDown
  switchDay
  
/* SETTINGS! */
  int cantHorasDeLuz = 18; //En horas
  int coolDownTime = 300000; //En millis CAMBIAR A MINUTOS

  int lamp = D4;
  int fans = D3;
  int switchDayButton = D1;
  int dayLedPin = D0;

  
  boolean isDayTime = true;
  boolean isNightTime = false;
  boolean buttonState = 0;

  unsigned long dayStart=0; // day start reference

  
  int cantHorasDeSombra = 24 - cantHorasDeLuz;
  
  unsigned long dayInterval= cantHorasDeLuz * 3600000; // day time is set to 18hs
  unsigned long nightInterval= cantHorasDeSombra * 3600000; // nigh time is set to 6hs
  unsigned long fullDayInterval= 24 * 3600000; // nigh time is set to 6hs
  

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(lamp, OUTPUT);
  pinMode(fans, OUTPUT);
  pinMode(dayLedPin, OUTPUT);
  pinMode(switchDayButton, INPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {

   unsigned long currentMillis = millis(); // grab current time

   if ((unsigned long)(currentMillis - dayStart) >= dayInterval) {
    if (isDayTime){
      sunSet();
    }
   }

   if ((unsigned long)(currentMillis - dayStart) >= (dayInterval + nightInterval)) {
    if (isNightTime){
      sunRaise();
    }
   }

  buttonState = digitalRead(switchDayButton);
  
  if (buttonState) {
    Serial.println("Button pressed");
    if (isDayTime){
      dayStart += dayInterval - (currentMillis - dayStart);
    }
    if (isNightTime){
      sunRaise();
    }
    delay(500);
  }
}

void sunRaise() {
  Serial.println("está saliendo el sol");
  digitalWrite(lamp, LOW);
  digitalWrite(fans, LOW);
  isDayTime = true;
  isNightTime = false;
  digitalWrite(dayLedPin, HIGH);
  delay(1000);
  switchDay();
}

void sunSet() {
  Serial.print("zzzZZZ");
  digitalWrite(lamp, HIGH);
  delay(coolDownTime);
  Serial.println("zzz");
  digitalWrite(fans, HIGH);
  isDayTime = false;
  isNightTime = true;
  digitalWrite(dayLedPin, LOW);
  delay(1000);
}

void coolDown() {
  digitalWrite(fans,LOW);
  Serial.println("cooling down...");
  digitalWrite(fans,HIGH);
}

void switchDay(){
  dayStart = millis();
}

