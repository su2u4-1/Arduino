int state = 0;  // 0: lock, 1: unlock, 2: setPassword
int time = 0;   // Waiting time
int MaxWaitingTime = 1000;
int ArrMax = 16;
int inputIndex = 0;
int button[11] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int ctrl = 12;
int motor = 13;
int key[16]{0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int input[16]{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

void setup() {
    for (int i = 0; i < 11; i++) {
        pinMode(button[i], INPUT);
    }
    pinMode(motor, OUTPUT);
    Serial.begin(9600);
    Serial.print("Hello World!\n");
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
    for (int i = 0; i < inputIndex; i++) {
        if (input[i] != key[i] || key[i] == -1 || input[i] == -1) {
            return false;
        }
    }
    return true;
}

void loop() {
    for (int i = 0; i < 11; i++) {
        if (digitalRead(button[i]) && time <= 0) {
            time = 10000;
            if (i == 10) {
                if (state == 0 && check()) {
                    state = 1;
                } else if (state == 1) {
                    state = 2;
                } else if (state == 2) {
                    for (int i = 0; i < ArrMax; i++) {
                        key[i] = input[i];
                    }
                    state = 0;
                }
                Serial.println("enter");
                showInfo();
                for (int i = 0; i < ArrMax; i++) {
                    input[i] = -1;
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
    }
    if (time > 0) {
        time--;
    }
    if (time >= MaxWaitingTime) {
        for (int i = 0; i < ArrMax; i++) {
            input[i] = -1;
        }
    }
    if (state == 1) {
        digitalWrite(motor, HIGH);
    } else {
        digitalWrite(motor, LOW);
    }
}
