#include <Servo.h>

int ButtonDelay = 5000;
int ArrMax = 16;
int Button[11] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 13, 12};
int Motor = 11;
// ^ constant
// v variable
int state = 0;  // 0: lock, 1: unlock, 2: setPassword
int time = 0;   // Waiting time
int t = 0;
int inputIndex = 0;
int key[16]{0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int input[16]{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

Servo myservo;

void setup() {
    for (int i = 0; i < 11; i++) {
        pinMode(Button[i], INPUT);
    }
    Serial.begin(9600);
    Serial.print("Hello ");
    myservo.attach(Motor);
    myservo.write(0);
    delay(500);
    myservo.write(90);
    delay(500);
    myservo.write(0);
    Serial.print("World!\n");
}

void showInfo() {
    for (int i = 0; i < inputIndex; i++) {
        Serial.print(input[i]);
        Serial.print(", ");
    }
    Serial.print("\nstate: ");
    Serial.print(state);
    Serial.print("\ninputIndex: ");
    Serial.println(inputIndex);
}

bool check() {
    if (inputIndex <= 0) {
        return false;
    }
    for (int i = 0; i < inputIndex; i++) {
        if (input[i] != key[i] || key[i] == -1 || input[i] == -1) {
            return false;
        }
    }
    return true;
}

void f(int i) {
    if (i == 10) {
        if (state == 0 && check()) {
            state = 1;
        } else if (state == 1) {
            state = 2;
        } else if (state == 2) {
            state = 0;
            if (inputIndex == 0) {
                for (int j = 0; j < ArrMax; j++) {
                    key[j] = -1;
                }
                key[0] = 0;
            } else {
                for (int j = 0; j < ArrMax; j++) {
                    key[j] = input[j];
                }
            }
        }
        Serial.println("enter");
        showInfo();
        for (int j = 0; j < ArrMax; j++) {
            input[j] = -1;
        }
        inputIndex = 0;
    } else if (state == 0 || state == 2) {
        if (inputIndex < ArrMax) {
            input[inputIndex] = i;
            inputIndex++;
            Serial.println(i);
            showInfo();
        }
    } else if (state == 1) {
        state = 0;
    }
}

void loop() {
    for (int i = 0; i < 11; i++) {
        if (i == 9) {
            continue;  // error
        }
        if (digitalRead(Button[i]) && t <= 0) {
            t = ButtonDelay;
            time = 0;
            f(i);
        }
    }
    if (t > 0) {
        t--;
    }
    time++;
    if (state == 0) {
        myservo.write(0);
    } else {
        myservo.write(90);
    }
}
