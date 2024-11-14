#include <vector>

int state = 0;  // 0: lock, 1: unlock, 2: setPassword
int time = 0;   // Waiting time
int MaxWaitingTime = 1000;
int button[11] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int ctrl = 12;
vector<int> key{0, 0, 0, 0};
vector<int> input;

void setup() {
    for (int i = 0; i < 11; i++) {
        pinMode(button[i], INPUT);
    }
    pinMode(motor, OUTPUT);
}

void loop() {
    for (int i = 0; i < 11; i++) {
        if (digitalRead(button[i])) {
            time = 0;
            if (i == 10) {
                if (state == 0 && input == key) {
                    state = 1;
                } else if (state == 1) {
                    state = 2;
                } else if (state == 2) {
                    key = input;
                    state = 0;
                }
                input.clear();
            } else if (state == 0 || state == 2) {
                input.push_back(i);
            }
        }
    }
    time++;
    if (time >= MaxWaitingTime) {
        input.clear();
    }
    if (state == 1) {
        // Motor running
    }
}
