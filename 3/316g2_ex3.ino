int a = LOW;
int v;

void setup() {
    pinMode(8, INPUT);
    pinMode(12, OUTPUT);
    Serial.begin(9600);
    Serial.println("start");
}

void loop() {
    v = digitalRead(8);
    if (v == HIGH) {
        while (v == HIGH) {
            v = digitalRead(8);
            delay(10);
        }
        Serial.print("LED turn ");
        if (a == LOW) {
            Serial.println("on");
            a = HIGH;
        } else {
            Serial.println("off");
            a = LOW;
        }
    }
    digitalWrite(12, a);
    delay(10);
}
