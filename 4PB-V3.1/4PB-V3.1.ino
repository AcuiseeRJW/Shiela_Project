// Acuisee 4PB  4 button pushbox
////////////////////////////////////////////////////////////////////////////////////////////////
//                                   NOTES                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////
/*
  10-28-2018    RJW    1.0   Initial Code
  06-21-2019    RJW    2.0   Added next gen box hw - buzzer, 2 additional PB, IO remap
                             Added volume library to hadle clicks
  06-21-2019    RJW    3.0   remove the volume.h library and used the normal tone() function
                             Just don't need the sophistication of volume.h , clicks can
                             be handled just fine with the standard function
  06-24-2019    RJW    3.1   remapped pbs to match button wiring     
                             logic to make sound for only one bar pb when both activated                   
*/

#define Version        3.1
#define pbA            7
#define pbB            8
#define pbC            11
#define pbD            12
#define pbE            9
#define pbF            10
#define run_lt         13

  const int     BlinkTime           = 1000;
  long          previousMillis      = 0;
  int           divisor             = 1;        // can vary blink rate for pin 13 by changing
  unsigned long currentMillis       = millis(); // variable to store current millisec time
  boolean       pbA_on              = false;
  boolean       pbB_on              = false;
  boolean       pbC_on              = false;
  boolean       pbD_on              = false;
  boolean       pbE_on              = false;
  boolean       pbF_on              = false;
  int           buttonVal           = HIGH;
  int           pbA_lastState       = HIGH;
  int           pbB_lastState       = HIGH;
  int           pbC_lastState       = HIGH;
  int           pbD_lastState       = HIGH;
  int           pbE_lastState       = HIGH;
  int           pbF_lastState       = HIGH;
  unsigned long debounceDelay       = 50;       // millisecs to wait for change in pb state
  unsigned long pbA_lastDebounceTime = millis();
  unsigned long pbB_lastDebounceTime = millis();
  unsigned long pbC_lastDebounceTime = millis();
  unsigned long pbD_lastDebounceTime = millis();
  unsigned long pbE_lastDebounceTime = millis();
  unsigned long pbF_lastDebounceTime = millis();

////////////////////////////////////////////////////////////////////////////////////////////////
//                                   SETUP                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  pinMode(pbA,    INPUT_PULLUP);
  pinMode(pbB,    INPUT_PULLUP);
  pinMode(pbC,    INPUT_PULLUP);
  pinMode(pbD,    INPUT_PULLUP);
  pinMode(pbE,    INPUT_PULLUP);
  pinMode(pbF,    INPUT_PULLUP);
  pinMode(run_lt, OUTPUT);
  digitalWrite(run_lt, LOW);

  // Serial
  Serial.begin(115200);     // Start serial port at specified baud rate
  Serial.print  (F("\n\n  AcuiSee-4PB Version: "));
  Serial.println(Version);
  Serial.println(F("-------------------------------"));
  Serial.println(F("Serial started . . . "));
  delay(500);

}

////////////////////////////////////////////////////////////////////////////////////////////////
//                                   LOOP                                                     //
////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {

  // Button A
  buttonVal = digitalRead(pbA);

  if (pbA_lastState != buttonVal) {
    if ((millis() - pbA_lastDebounceTime) > debounceDelay) {
      if ((buttonVal == LOW) && !(pbA_on))  {
        pbA_on = true;
        pbA_lastState = LOW;
        pbA_lastDebounceTime = millis();
        Serial.println(F("A"));
        ClickOn();
      }

      if ((buttonVal == HIGH) && (pbA_on)) {
        pbA_on = false;
        pbA_lastState = HIGH;
        pbA_lastDebounceTime = millis();
        Serial.println(F("a"));
        ClickOff();
      }
    }
  }

  // Button B
  buttonVal = digitalRead(pbB);

  if (pbB_lastState != buttonVal) {
    if ((millis() - pbB_lastDebounceTime) > debounceDelay) {
      if ((buttonVal == LOW) && !(pbB_on))  {
        pbB_on = true;
        pbB_lastState = LOW;
        pbB_lastDebounceTime = millis();
        Serial.println(F("B"));
        ClickOn();
      }

      if ((buttonVal == HIGH) && (pbB_on)) {
        pbB_on = false;
        pbB_lastState = HIGH;
        pbB_lastDebounceTime = millis();
        Serial.println(F("b"));
        ClickOff();
      }
    }
  }

  // Button C
  buttonVal = digitalRead(pbC);

  if (pbC_lastState != buttonVal) {
    if ((millis() - pbC_lastDebounceTime) > debounceDelay) {
      if ((buttonVal == LOW) && !(pbC_on))  {
        pbC_on = true;
        pbC_lastState = LOW;
        pbC_lastDebounceTime = millis();
        Serial.println(F("C"));
        ClickOn();
      }

      if ((buttonVal == HIGH) && (pbC_on)) {
        pbC_on = false;
        pbC_lastState = HIGH;
        pbC_lastDebounceTime = millis();
        Serial.println(F("c"));
        ClickOff();
      }
    }
  }

  // Button D
  buttonVal = digitalRead(pbD);

  if (pbD_lastState != buttonVal) {
    if ((millis() - pbD_lastDebounceTime) > debounceDelay) {
      if ((buttonVal == LOW) && !(pbD_on))  {
        pbD_on = true;
        pbD_lastState = LOW;
        pbD_lastDebounceTime = millis();
        Serial.println(F("D"));
        ClickOn();
      }

      if ((buttonVal == HIGH) && (pbD_on)) {
        pbD_on = false;
        pbD_lastState = HIGH;
        pbD_lastDebounceTime = millis();
        Serial.println(F("d"));
        ClickOff();
      }
    }
  }

  // Button E
  buttonVal = digitalRead(pbE);

  if (pbE_lastState != buttonVal) {
    if ((millis() - pbE_lastDebounceTime) > debounceDelay) {
      if ((buttonVal == LOW) && !(pbE_on))  {
        pbE_on = true;
        pbE_lastState = LOW;
        pbE_lastDebounceTime = millis();
        Serial.println(F("E"));
        if (!pbF_on) ClickOn();      // don't make a sound if the other bar pb is still on
      }

      if ((buttonVal == HIGH) && (pbE_on)) {
        pbE_on = false;
        pbE_lastState = HIGH;
        pbE_lastDebounceTime = millis();
        Serial.println(F("e"));
        if (!pbF_on) ClickOff();    // don't make a sound if the other bar pb is still on
      }
    }
  }

  // Button F
  buttonVal = digitalRead(pbF);

  if (pbF_lastState != buttonVal) {
    if ((millis() - pbF_lastDebounceTime) > debounceDelay) {
      if ((buttonVal == LOW) && !(pbF_on))  {
        pbF_on = true;
        pbF_lastState = LOW;
        pbF_lastDebounceTime = millis();
        Serial.println(F("F"));
        if (!pbE_on) ClickOn();      // don't make a sound if the other bar pb is still on
      }

      if ((buttonVal == HIGH) && (pbF_on)) {
        pbF_on = false;
        pbF_lastState = HIGH;
        pbF_lastDebounceTime = millis();
        Serial.println(F("f"));
        if (!pbE_on) ClickOff();    // don't make a sound if the other bar pb is still on
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////
  //                                   BLINK                                                     //
  ////////////////////////////////////////////////////////////////////////////////////////////////
    currentMillis = millis();
    if (currentMillis - previousMillis > BlinkTime / divisor) {
      previousMillis = currentMillis;              // save the last time you blinked the LED
      digitalWrite(run_lt,  !digitalRead(run_lt)); // change state of run light
     }

} // end of Loop


////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Clicking                                                //
///////////////////////////////////////////////////////////////////////////////////////////////
void ClickOn() {
  //tone(5,1500,5);
  tone(5, 2000, 5);
  delay(50);
}
void ClickOff() {
  tone(5, 1500, 5);
  delay(50);
}
