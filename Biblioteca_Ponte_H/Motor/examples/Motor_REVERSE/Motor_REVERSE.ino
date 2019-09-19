#include <Motor.h>


#define delayTime 1000

Motor motor;
int speedMotor = -255;

void setup() {
  motor.move(speedMotor);
}
 
void loop() {
}
