void setup() {
    Serial.begin(9600);
    Serial.print("Hello World!\n");
    pinMode(11, OUTPUT);
}

void loop() {
    for(int i = 0; i < 256; i++){
        analogWrite(11, i);
        Serial.print(i);
        delay(10);
    }
    for(int i = 255; i >= 0; i--){
        analogWrite(11, i);
        Serial.print(i);
        delay(10);
    }
}