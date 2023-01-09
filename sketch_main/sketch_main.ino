// Counter for 7 segment display with common anode.

#define NUM_OF_SEGMENTS 7

// Consecutively segments:                     A, B, C, D, E, F, G
const uint8_t SEGMENT_PINS[NUM_OF_SEGMENTS] = {2, 3, 4, 5, 6, 7, 8};
const uint8_t ADD_BUTTON = 9;
const uint8_t SUB_BUTTON = 10;

const byte DIGIT_SEGMENTS[10][NUM_OF_SEGMENTS] = {
    {1, 1, 1, 1, 1, 1, 0}, // = 0
    {0, 1, 1, 0, 0, 0, 0}, // = 1
    {1, 1, 0, 1, 1, 0, 1}, // = 2
    {1, 1, 1, 1, 0, 0, 1}, // = 3
    {0, 1, 1, 0, 0, 1, 1}, // = 4
    {1, 0, 1, 1, 0, 1, 1}, // = 5
    {1, 0, 1, 1, 1, 1, 1}, // = 6
    {1, 1, 1, 0, 0, 0, 0}, // = 7
    {1, 1, 1, 1, 1, 1, 1}, // = 8
    {1, 1, 1, 1, 0, 1, 1}, // = 9
};

int counter = 0;
bool add_pressed = false;
bool sub_pressed = false;

void displayDigit(int digit)
{
    if (digit < 0 || digit > 9) {
        return;
    }

    for (int i = 0; i < NUM_OF_SEGMENTS; i++) {
        digitalWrite(SEGMENT_PINS[i], DIGIT_SEGMENTS[digit][i] != 0 ? LOW : HIGH);
    }
}

void setup()
{
    for (int i = 0; i < NUM_OF_SEGMENTS; i++) {
        pinMode(SEGMENT_PINS[i], OUTPUT);
    }

    pinMode(ADD_BUTTON, INPUT_PULLUP);
    pinMode(SUB_BUTTON, INPUT_PULLUP);

    counter = 0;
    add_pressed = false;
    sub_pressed = false;
}

void loop()
{
    displayDigit(counter);

    if (digitalRead(ADD_BUTTON) == LOW && !add_pressed) {
        add_pressed = true;
        if (counter < 9) {
            counter += 1;
        }
    } else if (digitalRead(ADD_BUTTON) == HIGH && add_pressed) {
        add_pressed = false;
    }

    if (digitalRead(SUB_BUTTON) == LOW && !sub_pressed) {
        sub_pressed = true;
        if (counter > 0) {
            counter -= 1;
        }
    } else if (digitalRead(SUB_BUTTON) == HIGH && sub_pressed) {
        sub_pressed = false;
    }

    delay(100);
}
