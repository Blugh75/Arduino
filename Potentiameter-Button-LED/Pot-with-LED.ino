/*Code came from 
 * https://www.arduino.cc/en/Tutorial/Debounce
 * The sketch below is based on Limor Fried's version of debounce, but the logic is inverted from her example. In her example, the switch returns LOW when closed, and HIGH when open. Here, the switch returns HIGH when pressed and LOW when not pressed. 
 * 
 * https://www.arduino.cc/en/Tutorial/AnalogInput
 * 
 * 
 * The circuit for this consists of a potentiameter, a button, and an LED
 * The program will use the button to toggle the LED on and off, once on you can use the potentiameter to make the LED blink faster or slower
 * 
 * Code adapted by Blugh Justin Namgauds
 */

int sensorPin = A1;    // select the input pin for the potentiometer
int ledPin = 10;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
const int buttonPin = 7;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status
boolean light_toggle = false;

//For supporting debounce
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 25;    // the debounce time; increase if the output flickers

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int lastButtonState = LOW;   // the previous reading from the input pin
int reading = 0;


void setup() {
   // declare the ledPin as an OUTPUT:
   pinMode(ledPin, OUTPUT);
    // initialize the pushbutton pin as an input:
   pinMode(buttonPin, INPUT);
   Serial.begin(9600);
}

void loop() 
{
    // read the state of the switch into a local variable:
    reading = digitalRead(buttonPin);

    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState) 
    {
      Serial.write("Received Press");
      // reset the debouncing timer
      lastDebounceTime = millis();
      Serial.println("Last Debounce = ");
      Serial.println(lastDebounceTime);
    }

    if ((millis() - lastDebounceTime) > debounceDelay) 
    {
         // whatever the reading is at, it's been there for longer
         // than the debounce delay, so take it as the actual current state:
         // if the button state has changed:
       if (reading != buttonState) 
       {
          buttonState = reading;
          Serial.println("Current Debounce = ");
          Serial.println(lastDebounceTime);
          Serial.println("Last Debounce = ");
          Serial.println(debounceDelay);
          
          // only toggle the LED if the new button state is HIGH
         if (buttonState == HIGH) 
         {
           ledState = !ledState;
       
            Serial.write("Button State entered");
            Serial.println("");
            if (light_toggle == false)
              {
                Serial.write("Light Toggle is False Setting to True");
                Serial.println("");
                light_toggle = true;
              }
            else if (light_toggle == true)
              {
                Serial.write("Light Toggle is True Setting to False");
                Serial.println("");
                light_toggle = false;
              }
          }
        }
    }

   if (light_toggle == true)
    {
        sensorValue = analogRead(sensorPin);
        // turn the ledPin on
        digitalWrite(ledPin, HIGH);
        // stop the program for <sensorValue> milliseconds:
        delay(sensorValue);
        // turn the ledPin off:
        digitalWrite(ledPin, LOW);
        // stop the program for for <sensorValue> milliseconds:
        delay(sensorValue);
    }
    else if (light_toggle == false)
    {
      digitalWrite(ledPin, LOW);
    }
    lastButtonState = reading;
}


