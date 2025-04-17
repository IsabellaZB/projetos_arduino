#include <Servo.h>

Servo motor;

void setup() {
    motor.attach(9);
}

void loop() {
    motor.write(00);
    delay(1000);
    motor.write(280);
    delay(1000);
}
