/*
  Easy Helper Functions to Copy & Paste!

  // SETUP Functions
  start(pin, numPixels);  // pin - which pin NeoPixels are plugged into (e.g. 6) and how many pixels are on the strip (e.g. 10)

  // NeoPixel Functions (Use in LOOP)
  strandColor(r, g, b);               // Set the current strand color to a combination of red (r), green (g), and blue (b) values.
  strandFill();                       // Light up the entire strand with the current strand color
  strandClear();                      // Clears the entire strand
  strandBrightness(255);              // A number between 0 (not bright at all) and 255 (full brightness)
  strandPart(min, max);               // Light up part of the strand given a range. The first LED on the strand is 0. 
  strandMeter(analog);                // Lights up a part of the strand given a value between 0 - 1023
  colorMap(analog, hueMin, hueMax);   // Changes the hue of the color given a value between 0 - 1023 (analog), and 0 - 255 (hueMin/Max)

  // Sensor Functions (Use in LOOP)
  pushButton(pin);                    // Returns a true or false value if the button plugged into a pin is pressed (can be used with touch sensors and sound sensors too!)
  toggleButton(pin);                  // Toggles true or false value if the button plugged into a pin is pressed (can be used with touch sensors and sound sensors too!)
  pot(pin);                           // Returns a value between 0 - 1023 of a potentiometer
  lightSensor(pin, min, max)          // Returns a value between 0 - 1023 of a light sensor. Can be constrained between min and max
  tempSensor(pin, min, max);          // Returns a value between 0 - 1023 of a temperature sensor. Can be constrained between min and max

*/
