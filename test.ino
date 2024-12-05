int ButtonDelay = 5000;
int Button[11] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int Motor = 13;
// ^ constant
// v variable
int state = 0;  // 0: lock, 1: unlock, 2: setPassword
int time = 0;   // Waiting time
int t = 0;

void setup() {
    for (int i = 0; i < 11; i++) {
        pinMode(Button[i], INPUT);
    }
    pinMode(Motor, OUTPUT);
}

void loop() {
    for (int i = 0; i < 11; i++) {
        if (digitalRead(Button[i]) && t <= 0) {
            t = ButtonDelay;
            time = 0;
            state = 1;
        }
    }
    if (t > 0) {
        t--;
    } else {
        state = 0;
    }
    time++;
    if (state == 0) {
        digitalWrite(Motor, LOW);
    } else if (state == 1) {
        digitalWrite(Motor, HIGH);
    }
}
