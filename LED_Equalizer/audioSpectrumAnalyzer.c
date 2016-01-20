/***********************************************************************************************************
*
*   Audio Spectrum Analyzer LED Display
*       (aka: LED Equalizer)
*   Tiva C Series Launchpad Microcontroller Project
*
*   The purpose of this project was to demonstrate the skills and knowledge acquired from a microcontroller’s 
*   course curriculum by designing and implementing a microcontroller-based embedded system project. The goal 
*   of this project was to use the microcontroller to create an audio spectrum analyzer with a LED display.
* 
*
* 
*   Summary of Materials Needed:
*       - Over 150 generic LEDs
*           There were green, dim yellow/red, and red LEDs
*       - 3 Bread Board
*       - Several Wires
*       - Grove Sound Sensor    (This device detects the sound strength of it’s surroundings. It’s design is 
*                               based on the LM358 amplifier along with a electret microphone. It outputs an a
*                               analog signal to the TI Launchpad as a threshold value.)
*
*
*************************************************************************************************************/
 
#define SOUND_SENSOR           24        // Sound Sensor          
#define LED                    RED_LED   // LED pin
#define MAX_THRESHOLD_VALUE    2000      // Any number greater than max threshold will light up all 10 segments
#define MIN_THRESHOLD_VALUE    100       // The minimum threshold to light up segment 1
                                         //The min should be 1/10th the MAX Threshold 
                                         
//Thresholds for Segments
#define S2_THRESHOLD_VALUE    300
#define S3_THRESHOLD_VALUE    550
#define S4_THRESHOLD_VALUE    800
#define S5_THRESHOLD_VALUE    1000
#define S6_THRESHOLD_VALUE    1200
#define S7_THRESHOLD_VALUE    1400
#define S8_THRESHOLD_VALUE    1600
#define S9_THRESHOLD_VALUE    1700
       

#define ON                 HIGH                   // LED ON
#define OFF                LOW                    // LED OFF
#define _handle_led(x)     digitalWrite(LED, x)   // Handles on board LED

/* Holds the 10 segments for the LED sound equalizer display */
#define _handle_ledS1(x)   digitalWrite(31, x)    // Most left, Min value, Green      : LED PF_4
#define _handle_ledS2(x)   digitalWrite(32, x)    // Section 2 LEDS                   : LED PD_7
#define _handle_ledS3(x)   digitalWrite(33, x)    // Section 3 LEDS                   : LED PD_6
#define _handle_ledS4(x)   digitalWrite(34, x)    // Section 4 LEDS                   : LED PC_7
#define _handle_ledS5(x)   digitalWrite(35, x)    // Section 5 LEDS                   : LED PC_6
#define _handle_ledS6(x)   digitalWrite(36, x)    // Section 6 LEDS                   : LED PC_5
#define _handle_ledS7(x)   digitalWrite(37, x)    // Section 7 LEDS                   : LED PC_4
#define _handle_ledS8(x)   digitalWrite(38, x)    // Section 8 LEDS                   : LED PB_3
#define _handle_ledS9(x)   digitalWrite(39, x)    // Section 9 LEDS                   : LED PF_3
#define _handle_ledS10(x)  digitalWrite(40, x)    // Most right, Max value, Red LEDs  : LED PF_2


/* Global Variables */
int sound_value = 0;
int state = 0;

void setup() {
    /* Initialize led pin */
    pinMode(LED, OUTPUT);  
    digitalWrite(LED, LOW);
    
    // Intialize the min value S1
    pinMode(31, OUTPUT);  
    digitalWrite(31, LOW);
    
    // Intialize second section, S2
    pinMode(32, OUTPUT);  
    digitalWrite(32, LOW);
    
    // Intialize S3
    pinMode(33, OUTPUT);  
    digitalWrite(33, LOW);
    
    // Intialize S4
    pinMode(34, OUTPUT);  
    digitalWrite(34, LOW);
    
    // Intialize S5
    pinMode(35, OUTPUT);  
    digitalWrite(35, LOW);
    
    // Intialize S6
    pinMode(36, OUTPUT);  
    digitalWrite(36, LOW);
    
    // Intialize S7
    pinMode(37, OUTPUT);  
    digitalWrite(37, LOW);
    
    // Intialize S8
    pinMode(38, OUTPUT);  
    digitalWrite(38, LOW);
    
    // Intialize S9
    pinMode(39, OUTPUT);  
    digitalWrite(39, LOW);
    
    // Intialize S10
    pinMode(40, OUTPUT);  
    digitalWrite(40, LOW);  
    
    //Interrupt is fired whenever the sound sensor senses a value greater than MAX Threshold
   attachInterrupt(40, blink, RISING); // Rising triggers when pin goes from low to high
}
 
void loop() { 
  // Critical time-sensitive code
  noInterrupts();
  
  // Reads the sound value as an integer
  sound_value = analogRead(SOUND_SENSOR);
  
  
  delay(100);
  
  if (sound_value <  MIN_THRESHOLD_VALUE) {./
    state = 0;
  } else if ((MIN_THRESHOLD_VALUE<=sound_value)&&(sound_value<S2_THRESHOLD_VALUE)) {
    state = 1;
  } else if ((S2_THRESHOLD_VALUE<=sound_value)&&(sound_value<S3_THRESHOLD_VALUE)) {
    state = 2;
  } else if ((S3_THRESHOLD_VALUE<=sound_value)&&(sound_value<S4_THRESHOLD_VALUE)) {
    state = 3;
  } else if ((S4_THRESHOLD_VALUE<=sound_value)&&(sound_value<S5_THRESHOLD_VALUE)) {
    state = 4;
  } else if ((S5_THRESHOLD_VALUE<=sound_value)&&(sound_value<S6_THRESHOLD_VALUE)) {
    state = 5;
  } else if ((S6_THRESHOLD_VALUE<=sound_value)&&(sound_value<S7_THRESHOLD_VALUE)){
    state = 6;
  } else if ((S7_THRESHOLD_VALUE<=sound_value)&&(sound_value<S8_THRESHOLD_VALUE)){
    state = 7;
  } else if ((S8_THRESHOLD_VALUE<=sound_value)&&(sound_value<S9_THRESHOLD_VALUE)){
    state = 8;
  } else if ((S9_THRESHOLD_VALUE<=sound_value)&&(sound_value<MAX_THRESHOLD_VALUE)){
    state = 9;
  } else if (sound_value >= MAX_THRESHOLD_VALUE){
    state = 10;
  }
  
  // All other code that can be interrupted
 interrupts();
  
 switch (state) {
    case 0:
           //Do nothing
    break;
    
    case 1:// S1
            _handle_ledS1(ON); 
    break;
    
    case 2: // S2
             _handle_ledS1(ON);
             delay(10);
             _handle_ledS2(ON);
    break;
    
    case 3: // S3
             _handle_ledS1(ON);
             delay(10);
             _handle_ledS2(ON);
             delay(10);
             _handle_ledS3(ON);
    break;
    
    case 4:  // S4
             _handle_ledS1(ON);
             delay(10);
             _handle_ledS2(ON);
             delay(10);
             _handle_ledS3(ON);
             delay(10);
             _handle_ledS4(ON);
    break;
    
    case 5: // S5
             _handle_ledS1(ON);
             delay(10);
             _handle_ledS2(ON);
             delay(10);
             _handle_ledS3(ON);
             delay(10);
             _handle_ledS4(ON);
             delay(10);
             _handle_ledS5(ON);
    break;
    
    case 6: // S6
              _handle_ledS1(ON);
             delay(10);
             _handle_ledS2(ON);
             delay(10);
             _handle_ledS3(ON);
             delay(10);
             _handle_ledS4(ON);
             delay(10);
             _handle_ledS5(ON);
             delay(10);
             _handle_ledS6(ON);    
    break;
    
    case 7:  // S7
             _handle_ledS1(ON);
             delay(10);
             _handle_ledS2(ON);
             delay(10);
             _handle_ledS3(ON);
             delay(10);
             _handle_ledS4(ON);
             delay(10);
             _handle_ledS5(ON);
             delay(10);
             _handle_ledS6(ON);
             delay(10);
             _handle_ledS7(ON);    
    break;
    
    case 8: // S8
             _handle_ledS1(ON);
             delay(10);
             _handle_ledS2(ON);
             delay(10);
             _handle_ledS3(ON);
             delay(10);
             _handle_ledS4(ON);
             delay(10);
             _handle_ledS5(ON);
             delay(10);
             _handle_ledS6(ON);
             delay(10);
             _handle_ledS7(ON);
             delay(10);
             _handle_ledS8(ON);
    break;
    
    
    case 9: // S9
             _handle_ledS1(ON);
             delay(10);
             _handle_ledS2(ON);
             delay(10);
             _handle_ledS3(ON);
             delay(10);
             _handle_ledS4(ON);
             delay(10);
             _handle_ledS5(ON);
             delay(10);
             _handle_ledS6(ON);
             delay(10);
             _handle_ledS7(ON);
             delay(10);
             _handle_ledS8(ON);
             delay(10);
             _handle_ledS9(ON);
    break;
    
    case 10: // S10
             _handle_ledS1(ON);
             delay(10);
             _handle_ledS2(ON);
             _handle_ledS3(ON);
             delay(10);
             _handle_ledS4(ON);
             delay(10);
             _handle_ledS5(ON);
             delay(10);
             _handle_ledS6(ON);
             delay(10);
             _handle_ledS7(ON);
             delay(10);
             _handle_ledS8(ON);
             delay(10);
             _handle_ledS9(ON);
             delay(10);
             _handle_ledS10(ON); // Causes an interrupt    
    break;
    
    default:
        _handle_led(OFF);
        _handle_ledS1(OFF);
        _handle_ledS2(OFF);
        _handle_ledS3(OFF);
        _handle_ledS4(OFF);
        _handle_ledS5(OFF);
        _handle_ledS6(OFF);
        _handle_ledS7(OFF);
        _handle_ledS8(OFF);
        _handle_ledS9(OFF);
        _handle_ledS10(OFF);  ;
     break;
  }


  // Set LEDs back to default
  delay(100);
  // Sets all LEDs back to OFF default
  _handle_led(OFF);
  _handle_ledS1(OFF);
  _handle_ledS2(OFF);
  _handle_ledS3(OFF);
  _handle_ledS4(OFF);
  _handle_ledS5(OFF);
  _handle_ledS6(OFF);
  _handle_ledS7(OFF);
  _handle_ledS8(OFF);
  _handle_ledS9(OFF);
  _handle_ledS10(OFF);  
}

 
void blink() {
  static boolean pulse = HIGH;     
  // Makes the LEDs blink
    pulse = (pulse==HIGH) ? LOW : HIGH;
    
    _handle_led(pulse);
    delay (200);
    _handle_ledS1(pulse);
    _handle_ledS2(pulse);
    _handle_ledS3(pulse);
    _handle_ledS4(pulse);
    _handle_ledS5(pulse);
    _handle_ledS6(pulse);
    _handle_ledS7(pulse);
    _handle_ledS8(pulse);
    _handle_ledS9(pulse);
    _handle_ledS10(pulse); 
    delay (300); 
}