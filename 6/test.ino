int MaxWaitingTime = 10000000;
int ButtonDelay = 5000;
int ArrMax = 16;
int Button[11] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int Ctrl = 12;
int Motor = 13;
// ^ constant
// v variable
int state = 0;  // 0: lock, 1: unlock, 2: setPassword
int time = 0;   // Waiting time
int t = 0;
int inputIndex = 0;
int key[16]{0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int input[16]{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

void setup() {
    for (int i = 0; i < 11; i++) {
        pinMode(Button[i], INPUT);
    }
    pinMode(Motor, OUTPUT);
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
            for (int i = 0; i < ArrMax; i++) {
                key[i] = input[i];
            }
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

void loop() {
    for (int i = 0; i < 11; i++) {
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
        digitalWrite(Motor, LOW);
    } else if (state == 1) {
        digitalWrite(Motor, HIGH);
    } else {
        if ((time / 1000) % 2 == 0) {
            digitalWrite(Motor, HIGH);
        } else {
            digitalWrite(Motor, LOW);
        }
    }
}
