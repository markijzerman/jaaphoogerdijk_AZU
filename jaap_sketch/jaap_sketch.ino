// in te stellen parameters
int buttonPin = 2; // button zit op digitale pin 2
int amtLEDs = 8; // hoeveel LED groepen totaal
int startLEDpin = 6; // op welke pin beginnen we met uitsturen
int period = 2; // periode in seconden

// niet in te stellen parameters
unsigned long startMillis;
unsigned long currentMillis;

int counter;
int lastCounter;
int countBackFrom;
int buttonState;
int lastButtonState;
int curLEDsON;

void setup() {
  Serial.begin(9600); // seriele communicatie 9600 bits/s
  pinMode(buttonPin, INPUT_PULLUP); // maak een input van de buttonPin, met interne pullup

  // set all output pins
  for(int i=startLEDpin; i<=(startLEDpin + amtLEDs); i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {  
  // lees button status
  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      startMillis = millis();
    }
    else {
      // wanneer HIGH dan is er losgelaten
      countBackFrom = lastCounter;
      startMillis = millis();
    }
  }

  // bij button PRESS
  if ((buttonState == LOW) && (curLEDsON < amtLEDs)) {
    currentMillis = millis() - startMillis;
    counter = currentMillis / (period*1000);

    if (counter != lastCounter) {
      // where the magic happens om omhoog te gaan
      //Serial.println(counter);
      curLEDsON ++;
      Serial.println(curLEDsON);
      
      int LEDaan = startLEDpin + (curLEDsON-1);
      digitalWrite(LEDaan, HIGH);
    }
    
    lastCounter = counter;
  }


  // bij button LOSLAAT
    if ((buttonState == HIGH) && (curLEDsON > 0)) {
    currentMillis = millis() - startMillis;
    counter = currentMillis / (period*1000);

      if (counter != lastCounter) {
        // where the magic happens om omlaag te gaan
        
        curLEDsON --;
        Serial.println(curLEDsON);

        int LEDuit = (curLEDsON + startLEDpin);
        digitalWrite(LEDuit, LOW);
    }
    
    lastCounter = counter;
  }

  
  // sla de state op
  lastButtonState = buttonState;

}
