/*
not so Simple program to test buttons and LEDs on the PCB
*/

// arrrr arrays yay

// LED pins
const int LED_PINS[] = {D0, D1, D2, D3};


// Button pins
const int BUTTON_PINS[] = {D10, D9, D8, D7};

// Debounce variables idk what im doing aaa
const unsigned long DEBOUNCE_DELAY = 50; // 50 ms debounce time i think
unsigned long lastDebounceTime[4] = {0};
int lastButtonStates[4] = {HIGH};
int buttonStates[4] = {HIGH};


// calculator vars
int input1 = 0;
int input2 = 0;

int output = 0;

String calculator_state = "input";

// Setup
void setup(){
    // Set LED pins to outputs
    for(int i = 0; i < 4; i++) {
        pinMode(LED_PINS[i], OUTPUT);
    }
    
    // Set Button pins to INPUT PULLUPs
    for(int i = 0; i < 4; i++) {
        pinMode(BUTTON_PINS[i], INPUT_PULLUP);
    }
    
    resetLEDs();
}

// reset everything so its off/sleepy mode
void resetLEDs() {
    // loop for all the LEDs
    for(int i = 0; i < 4; i++) {
        digitalWrite(LED_PINS[i], LOW);
    }
}



int binaryToDecimal(String binary) {

    // store counters + vars
    int decimal = 0;
    int power = 0;
    // loop from right to left and convert
    for (int currentBinaryIndex = binary.length() - 1; currentBinaryIndex >= 0; currentBinaryIndex--) {
        if (binary.charAt(currentBinaryIndex) == '1') {
            // cool power stuff
            decimal += pow(2, power);
        }
        power++;
    }
    return decimal;
}

String decimalToBinary(int decimal) {
    // simple just zero answer
    if (decimal == 0) return "0";

    // we store binary in this String 
    String binary = "";

    // loop per digit, do the power thingy???
    while (decimal > 0) {

        binary = String(decimal % 2) + binary;
        decimal /= 2;
    }
    return binary;
}

void showBinary(String binary, int startLEDIndex = 0, int digitsToShow = 4) {
    /*
    this function uses the LEDS on the PCB to show binary, it's arranged in a 2x2 grid so reading it can be slightly confusing
    lets you specify the number of digits to show, defaulting to 4 yay
    */
    resetLEDs();
    
    // Ensure we're working with the specified number of digits from the right
    int binaryLength = binary.length();
    int startIndex = max(0, binaryLength - digitsToShow);
    
    // Counter for LED index
    int ledIndex = startLEDIndex;
    
    // Loop through the specified number of digits
    for (int i = startIndex; i < binaryLength && ledIndex < startLEDIndex + digitsToShow; i++) {
        if (binary.charAt(i) == '1') {
            digitalWrite(LED_PINS[ledIndex], HIGH);
        }
        ledIndex++;
    }
}

int readButtons() {
    /*
    very complicated aaa
    */
    int pressedButtonCount = 0;
    int lastPressedButton = -1;

    for(int i = 0; i < 4; i++) {
        int reading = digitalRead(BUTTON_PINS[i]);
        
        // If the button state has changed
        if(reading != lastButtonStates[i]) {
            // Reset the debounce timer
            lastDebounceTime[i] = millis();
        }
        
        // Check if enough time has passed for debounce
        if((millis() - lastDebounceTime[i]) > DEBOUNCE_DELAY) {
            // If the button state is different from the current state
            if(reading != buttonStates[i]) {
                buttonStates[i] = reading;
                
                // Button is pressed (LOW for INPUT_PULLUP)
                if(buttonStates[i] == LOW) {
                    pressedButtonCount++;
                    lastPressedButton = i;
                }
            }
        }
        
        // Save the current reading for next iteration
        lastButtonStates[i] = reading;
    }
    
    // Return based on number of pressed buttons
    if (pressedButtonCount > 1) {
        return -2;  // Multiple buttons pressed
    } else if (pressedButtonCount == 1) {
        return lastPressedButton;  // Single button pressed
    } else {
        return -1;  // No buttons pressed
    }
}

void loop() {
    if (calculator_state == "input") {
        resetLEDs();
        String binary1 = "0000";
        String binary2 = "0000";
        bool inputting_first = true;

        while (calculator_state == "input") {
            int buttonState = readButtons();

            if (buttonState == 0 || buttonState == 1) {  // Top buttons
                if (inputting_first) {
                    // Toggle specific bit in binary1
                    binary1.setCharAt(buttonState, 
                        binary1.charAt(buttonState) == '0' ? '1' : '0');
                    showBinary(binary1);
                }
            }
            else if (buttonState == 2 || buttonState == 3) {  // Bottom buttons
                if (!inputting_first) {
                    // Toggle specific bit in binary2
                    binary2.setCharAt(buttonState - 2, 
                        binary2.charAt(buttonState - 2) == '0' ? '1' : '0');
                    showBinary(binary2);
                }
            }
            else if (buttonState == -2) {  // Multiple buttons pressed
                // Switch between input1 and input2
                inputting_first = !inputting_first;
                delay(200);  // Debounce delay
            }

            // Convert inputs to decimal
            input1 = binaryToDecimal(binary1);
            input2 = binaryToDecimal(binary2);
            
            // Optional: show which input is currently being edited
            digitalWrite(LED_PINS[inputting_first ? 0 : 3], HIGH);
        }

        // Perform calculation
        output = input1 + input2;
        calculator_state = "output";
    }
    else if (calculator_state == "output") {
        // Convert output to binary and display yay
        String outputBinary = decimalToBinary(output);
        showBinary(outputBinary);

        // Wait for button press to reset
        while (readButtons() == -1) {
            //stall time
        }

        // reset so you can count again
        calculator_state = "input";
        resetLEDs();
    }
}
