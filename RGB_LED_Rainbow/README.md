
#RGB LED RAINBOW

###Using a small circuit containing an ATtiny45 and RGB Led to cycle through 7 main colors.
  
    *The 7 colors go through: red, green, blue, cyan, yellow, magenta, and white.
      
  The main colors red, green, and blue, are assigned to the PBx pins based on the header
  file. Accorrding to the PBx value table, this project uses OFF(0) to light up the LED
  and ON(1) turns off the led. 
  
  This circuit cycles through the colors using a fade-in and fade-out cycle to provide a 
  smooth transition between two colors. Smooth transitions are executed by leveraging the 
  PWM concept and applying it to the LEDs. Using PWM, a LED can be modulated to appear 
  brighter or slower based on the frequency and signal cycle.



//Based on the ATMEL ATTINY45 / ARDUINO from pins_arduno.h header file
//
//                          +-\/-+
// Ain0 (D 5)[RESET]  PB5  1|    |8  Vcc
// Ain3 (D 3)[CLK_I]  PB3  2|    |7  PB2 (D 2)  Ain1  [SCK]
// Ain2 (D 4)[CLK_O]  PB4  3|    |6  PB1 (D 1)  pwm1  [MISO]
//                    GND  4|    |5  PB0 (D 0)  pwm0  [MOSI]
//                          +----+
//
