/*
Simple program to test buttons and LEDs on the PCB
*/

// Constants for pin declarations
// perhaps use arrays in the future

// LED pins
const int LED1_PIN = D0;
const int LED2_PIN = D1;
const int LED3_PIN = D2;
const int LED4_PIN = D3;

// Button pins
const int BUTTON1_PIN = D10;
const int BUTTON2_PIN = D9;
const int BUTTON3_PIN = D8;
const int BUTTON4_PIN = D7; 

// LED states:
bool LED_STATE = true;

// Setup
void setup(){

    // Set LED pins to outputs
    pinMode(LED1_PIN,OUTPUT);
    pinMode(LED2_PIN,OUTPUT);
    pinMode(LED3_PIN,OUTPUT);
    pinMode(LED4_PIN,OUTPUT);
    // Set Button pins to INPUT PULLUPs (I guess my board is a toddler, idt the kit includes pullups though /jk)
    pinMode(BUTTON1_PIN,INPUT_PULLUP);
    pinMode(BUTTON2_PIN,INPUT_PULLUP);
    pinMode(BUTTON3_PIN,INPUT_PULLUP);
    pinMode(BUTTON4_PIN,INPUT_PULLUP);

}



void loop(){
    delay(1000);
    digitalWrite(LED1_PIN, LED_STATE);
    digitalWrite(LED2_PIN, !LED_STATE);
    digitalWrite(LED3_PIN, !LED_STATE);
    digitalWrite(LED4_PIN,LED_STATE );
    LED_STATE = !LED_STATE;


}