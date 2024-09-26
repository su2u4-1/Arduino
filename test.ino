char c = '0';

void setup() {
    pinMode(13, OUTPUT);
    Serial.begin(9600);
    Serial.print("Hello World!\n");
}

void loop() {
    if(Serial.available() > 0){
        c = Serial.read();
        if(c == '0'){
            digitalWrite(13, LOW);
            Serial.print("turn off\n");
        }
        else if(c == '1'){
            digitalWrite(13, HIGH);
            Serial.print("turn up\n");
        }
    }
}