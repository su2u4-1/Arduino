void setup() {
    pinMode(8, INPUT);
    Serial.begin(9600);
}

void loop() {
    Serial.print("BUTTON = ");
    Serial.println(digitalRead(8));
}
