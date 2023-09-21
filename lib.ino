/*   ____ ____ _____ _  ___  _    _   _      _                    _     _ _
 *  / ___|  _ \_   _/ |/ _ \/ |  | | | | ___| |_ __   ___ _ __   | |   (_) |__  _ __ __ _ _ __ _   _
 * | |   | |_) || | | | | | | |  | |_| |/ _ \ | '_ \ / _ \ '__|  | |   | | '_ \| '__/ _` | '__| | | |
 * | |___|  _ < | | | | |_| | |  |  _  |  __/ | |_) |  __/ |     | |___| | |_) | | | (_| | |  | |_| |
 *  \____|_| \_\|_| |_|\___/|_|  |_| |_|\___|_| .__/ \___|_|     |_____|_|_.__/|_|  \__,_|_|   \__, |
 *                                            |_|                                              |___/ 
 *
 *                  A collection of helper functions for the CRT101 curriculum
 *                      !!!! PLEASE DO NOT CHANGE ANY CODE ON THIS PAGE !!!!
 *                             Zane Cochran & Jackson Pelot, 7/23
 */


#include <Adafruit_NeoPixel.h>


// Arrays store the last readings of all digital and analog pins
int dState[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int aState[7]  = {0,0,0,0,0,0,0};

int tempSensorVal[50]; // Stores previous readings for tempSensor function



Adafruit_NeoPixel strand; // Declare Neopixel object
uint32_t strandColorVar = 0;



// Starts neopixel, serial comms, and initializes vars
void start(int pin, int num) {

  Serial.begin(9600);
  Serial.println("\n:3");
  
  strand = Adafruit_NeoPixel(num, pin, NEO_GRB + NEO_KHZ800);

  strand.begin();
  strand.clear();
  strand.setBrightness(255);
  strand.show();


  for(int i = 0; i < 50; i++) {
    tempSensorVal[i] = 0;
  }
}



// Custom map implementation to use float arithmetic
float floatMap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}




/*  ___ _   _ ____  _   _ _____ ____
 * |_ _| \ | |  _ \| | | |_   _/ ___|
 *  | ||  \| | |_) | | | | | | \___ \
 *  | || |\  |  __/| |_| | | |  ___) |
 * |___|_| \_|_|    \___/  |_| |____/
 *
 */



//  Push Button
// (True when button is pressed, false otherwise)

bool pushButton(int pin) {
  pinMode(pin, INPUT); // Register pin as input

  dState[pin] = digitalRead(pin); // Read state of the pin, save to state array

  // Send status info to serial port 
  Serial.print("Push button on pin ");
  Serial.print(pin);
  Serial.print(" returned ");
  Serial.println(dState[pin]);

  // Return value of reading
  return dState[pin];
}




// Toggle Switch
// (Pressing the button switches the output from true to false)

bool toggleButton(int pin) {
  pinMode(pin, INPUT); // Register pin as input

  // Create array to store previous toggle switch readings for all digital pins
  // Array is static so it will persist accross function calls
  static bool prevState[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  // Creates variable 'r' of type 'int', reads current state of pin and writes it to 'r'
  int r = digitalRead(pin);
  
  // If the current state of the pin is 1 and the previous state was 0, change toggle state
  // (This indicates that the button went from being unpushed to being pushed)
  if(r==1 && prevState[pin] == 0) {
    dState[pin] = !dState[pin];
  }

  // Saves current reading to array of past readings for next time
  prevState[pin] = r;

  // Delay code excecution for 25ms to avoid button bounce
  delay(25);

  // Send status info to serial port
  Serial.print("Toggle button on pin ");
  Serial.print(pin);
  Serial.print(" returned ");
  Serial.println(dState[pin]);
  
  // Return the toggle state
  return dState[pin];
}




// Potentiometer

int pot(int pin) {
  aState[pin] = analogRead(pin); // Read state of the pin, save to state array

  // Send status info to serial port
  Serial.print("Potentiometer on pin ");
  Serial.print(pin);
  Serial.print(" returned ");
  Serial.println(aState[pin]);

  // Return pin reading
  return aState[pin];
}



// Photoresistor
// Takes a pin number, a min, and a max value
// Min and max determine what section of the analog range (0 to 1023)
// should be considered in the output. The specified subsection is then mapped
// back to the full analog range.

int lightSensor(int pin, int minimum, int maximum) {
  int a = analogRead(pin); // Creates variable 'a' of type 'int', reads the speficied pin, and writes the value to 'a'

  int aC = constrain(a, minimum, maximum);
  
  // Restricts analog range to min & max, and maps result back to full range
  aState[pin] = map(aC, minimum, maximum, 0, 1023);

  // Sends status info to serial
  Serial.print("Light Sensor on pin ");
  Serial.print(pin);
  Serial.print(" returned ");
  Serial.print(a);
  Serial.print(", mapped to ");
  Serial.println(aState[pin]);

  // Returns mapped reading
  return aState[pin];
}




// Temperature Sensor

int tempSensor(int pin, int minimum, int maximum) {

  // Read temp sensor, save to 'a'
  int a = analogRead(pin);

  float average = 0; // Stores average of previous readings

  // Calculates new average of readings and adds new reading to array
  for(int i = 1; i < 50; i++) {
    tempSensorVal[i-1] = tempSensorVal[i];
    average = average + tempSensorVal[i];
  }
  tempSensorVal[49] = a;
  average = average/49;
  
  
  // Constrain the averaged reading to the min/max
  float aC = constrain(average, minimum, maximum);

  // Maps averaged reading to the full analog range
  aState[pin] = (int) floatMap(aC, minimum, maximum, 0, 1023);
  
  // Sends status info to serial
  Serial.print("Temp Sensor on pin ");
  Serial.print(pin);
  Serial.print(" returned ");
  Serial.print(average);
  Serial.print(", mapped to ");
  Serial.println(aState[pin]);
  
  return aState[pin];
}






/*   _   _ _____ ___  ____ _____  _______ _
 *  | \ | | ____/ _ \|  _ \_ _\ \/ / ____| |
 *  |  \| |  _|| | | | |_) | | \  /|  _| | |
 *  | |\  | |__| |_| |  __/| | /  \| |___| |___
 *  |_| \_|_____\___/|_|  |___/_/\_\_____|_____|
 *
 */




void strandPart(int minimum, int maximum) {
  for(int i = minimum; i < maximum; i++) {
    strand.setPixelColor(i, strandColorVar);
  }
  strand.show();
}

void strandFill() {
  strandPart(0,strand.numPixels());
}

void strandMeter(int a) {
  strand.clear();
  int p = map(a, 0, 1023-10, 0, strand.numPixels());
  strandPart(0, p );

  Serial.print("Analog input "); 
  Serial.print(a);
  Serial.print(" mapped to ");
  Serial.print(p);
  Serial.print("/");
  Serial.print(strand.numPixels());
  Serial.println(" pixels");
}


void strandColor(int r, int g, int b) {
  strandColorVar = strand.Color(r,g,b);
  //hueA = h;
  //hueB = h;
}


void strandClear() {
  strand.clear();
  strand.show();
}

void strandBrightness(int b) {
  strand.setBrightness(b);
  strand.show();
}


uint32_t wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strand.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
    return strand.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strand.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


void colorMap(int a, int minimum, int maximum) {
  int hue = map(a, 0, 1023, minimum, maximum);
  
  strandColorVar = wheel(hue);

  Serial.print("Analog input "); 
  Serial.print(a);
  Serial.print(" mapped to hue of ");
  Serial.println(hue);
}
