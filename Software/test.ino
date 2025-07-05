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
bool LED1_STATE = false;
bool LED2_STATE = false;
bool LED3_STATE = false;
bool LED4_STATE = false;

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
    /*
    This might blow up because of debouncing and stuff, I'll have to add millis stuff later.

    */
    if(digitalRead(BUTTON1_PIN) == LOW){
        // if(LED1_STATE == false){
        //     digitalWrite(LED1_PIN, HIGH)
            
        // }else{
        //     digitalWrite(LED1_PIN,LOW)

        // }
        LED1_STATE = !LED1_STATE;
        digitalWrite(LED1_PIN, LED1_STATE);
    }

    if(digitalRead(BUTTON2_PIN) == LOW){
        LED2_STATE = !LED2_STATE;
        digitalWrite(LED2_PIN,LED2_STATE);
    }

    if(digitalRead(BUTTON3_PIN) == LOW){
        LED3_STATE = !LED3_STATE;
        digitalWrite(LED3_PIN, LED3_STATE);
    }

    if(digitalRead(BUTTON4_PIN) == LOW){
        LED4_STATE = !LED4_STATE;
        digitalWrite(LED4_PIN, LED4_STATE);
    }

}