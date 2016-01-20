
#RGB LED RAINBOW

######Using a small circuit containing an ATtiny45 and RGB Led to cycle through 7 main colors.
  
*The 7 colors go through: red, green, blue, cyan, yellow, magenta, and white.
      
The main colors red, green, and blue, are assigned to the PBx pins based on the header
file. Accorrding to the PBx value table, this project uses OFF(0) to light up the LED
and ON(1) turns off the led. 

This circuit cycles through the colors using a fade-in and fade-out cycle to provide a 
smooth transition between two colors. Smooth transitions are executed by leveraging the 
PWM concept and applying it to the LEDs. Using PWM, a LED can be modulated to appear 
brighter or slower based on the frequency and signal cycle.
