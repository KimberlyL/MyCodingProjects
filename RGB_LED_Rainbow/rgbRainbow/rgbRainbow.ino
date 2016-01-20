/*
  RGB LED RAINBOW

  Using a small circuit containing an ATtiny45 and RGB Led to cycle through 7 main colors.
  
      The 7 colors go through: red, green, blue, cyan, yellow, magenta, and white.
      
  The main colors red, green, and blue, are assigned to the PBx pins based on the header
  file. Accorrding to the PBx value table, this project uses OFF(0) to light up the LED
  and ON(1) turns off the led. 
  
  This circuit cycles through the colors using a fade-in and fade-out cycle to provide a 
  smooth transition between two colors. Smooth transitions are executed by leveraging the 
  PWM concept and applying it to the LEDs. Using PWM, a LED can be modulated to appear 
  brighter or slower based on the frequency and signal cycle.
  
  by Kimberly Loza
 */


//Based on the ATMEL ATTINY45 / ARDUINO from pins_arduno.h header file
//
//                          +-\/-+
// Ain0 (D 5)[RESET]  PB5  1|    |8  Vcc
// Ain3 (D 3)[CLK_I]  PB3  2|    |7  PB2 (D 2)  Ain1  [SCK]
// Ain2 (D 4)[CLK_O]  PB4  3|    |6  PB1 (D 1)  pwm1  [MISO]
//                    GND  4|    |5  PB0 (D 0)  pwm0  [MOSI]
//                          +----+
//
//  static const uint8_t A0 = 6; // MOSI
//  static const uint8_t A1 = 7; // RED/MISO
//  static const uint8_t A2 = 8; // Green
//  static const uint8_t A3 = 9; // Blue

//Color Pin Constants
const int redLedPin   = 1;
const int greenLedPin = 8;
const int blueLedPin  = 9;

// PWM(~)
const int on  = 255;  // Max value of the PWM Cycle, full brightness
const int off = 0;    // Leds are off PWM
// The setup function runs once when you press reset or power the board
void setup() {
  // Setting all digital pins as outputs
  pinMode(redLedPin, OUTPUT);   // PB1      : MISO  Red   LED
  pinMode(greenLedPin, OUTPUT); // PB4||Ain4: CLK_I Green LED
  pinMode(blueLedPin, OUTPUT);  // PB3||Ain3: CLK_O Blue  LED
  
}

// Loops through the rainbow states
void loop() {
    setColor(on, off, off);     // Red      = {ON, OFF, OFF};
    setColor(off, on, off);     // Green    = {OFF, ON, OFF};    
    setColor(off, off, on);     // Blue     = {OFF, OFF, ON};    
    setColor(off, on, on);      // Cyan     = {OFF, ON, ON};
    setColor(on, on, off);      // Yellow   = {ON, ON, OFF};
    setColor(on, off, on);      // Magenta  = {ON, OFF, ON};
    setColor(on, on, on);       // White    = {ON, ON, ON}; 
  }


void setColor(int redValue, int greenValue, int blueValue) {    
    // Fade into the true color starting from greater than 50% Duty Cycle
    for (int brightness = 150; brightness <= on; brightness += 5){       
      //Determine the fade in brightness
      setBrightness(redValue, greenValue, blueValue, brightness);
      delay(100);
    }
        
    //Writes true color using only on and off states for 1sec
    int x = 0; // Temp counter
    do {
      sendColor(redValue, greenValue, blueValue);
      delay(100);
      x++;      
    }while(x < 10); 
     
    //Fades the color of the LED out by dimming the brightness
    for (int brightness = on; brightness >= 150; brightness -= 5 ){
      setBrightness(redValue, greenValue, blueValue, brightness);
      delay(100);
    }
}

// Writes as an analog value (PWM wave) to pin
void sendColor(int redValue, int greenValue, int blueValue){
  analogWrite(redLedPin, redValue);
  analogWrite(greenLedPin, greenValue);
  analogWrite(blueLedPin, blueValue);
  delay(100);
}

// Determines the fade-in and fade-out brightness by changing the PWM value
void setBrightness(int redValue, int greenValue, int blueValue, int brightness){
  if (redValue == on) {
    redValue = brightness;
  } 
  if (greenValue == on) {
    greenValue = brightness;
  }
  if (blueValue == on){
    blueValue = brightness;
  }
  sendColor(redValue, greenValue, blueValue); 
}
