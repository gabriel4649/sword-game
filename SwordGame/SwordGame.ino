/*
  SwordGame

  Code for the Lilypad Arduino driven electronic best for the sword
  fighting game for smart-phones. 
*/

// Initial HP, which also corresponds to number leds
#define INITIAL_HP 4;

// Pin that detects a sword hit from the conductive fabric
const int conductiveFabricPin = 7;

// Pin to fire vibe board
const int vibePin = 8;

int ledPins[] = {
  2, 3, 4, 5}; // an array of pin numbers to which LEDs are attached
int pinCount = INITIAL_HP; // the number of pins (i.e. the length of the array)

// Saves the current button state
int conductiveFabricState = 0;

// Save the remaining live gauge
int hp = INITIAL_HP;

// whether we need to update life gauge
boolean updateLife = false;

unsigned long time;
unsigned long oldTime = 0;
unsigned long timeDelta = 0;
unsigned long threshold = 2500;

void setup() {                

  Serial.begin(115200);
  // initialize the conductive fabric pin as an input.
  pinMode(conductiveFabricPin, INPUT); 
  // set pin to high, we are using pull-up configuration
  digitalWrite(conductiveFabricPin, HIGH); 

  // initialize the vibe pin as an output.
  pinMode(vibePin, OUTPUT); 
  // set pin to low, we don't want it activated
  digitalWrite(vibePin, LOW); 

  // intiliaze all led pins
  for (int thisPin = 0; thisPin < pinCount; thisPin++)  {
    pinMode(ledPins[thisPin], OUTPUT);   
  
  }

  // start hp on max
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    digitalWrite(ledPins[thisPin], HIGH);  
  }

}

// the loop routine runs over and over again forever:
void loop() {

  conductiveFabricState = digitalRead(conductiveFabricPin);


  // detect swrod hits
  if (conductiveFabricState == LOW ) {

    time = millis();
    timeDelta = time - oldTime;

    if (timeDelta > threshold) {
      // decreate life counter
      --hp;
      // now we want to updat hp display
      updateLife = true;
      oldTime = millis();

      // Activate vibe board
      digitalWrite(vibePin, HIGH); 
      // Vibrate for one second
      delay(1000);
      // Deactivate vibe board
      digitalWrite(vibePin, LOW); 
    }

    // Display life gauge
    if (updateLife = true) {
      // reset status variable
      updateLife = false;

      // loop from the lowest pin to the highest:
      for (int thisPin = 0; thisPin < pinCount; thisPin++) {
	if (thisPin > hp) {
	  // turn the pin on:
	  digitalWrite(ledPins[thisPin], HIGH);  
	}
	else {
	  // turn the pin off:
	  digitalWrite(ledPins[thisPin], LOW);    
	}

      }

    }

  }

}


