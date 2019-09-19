#include <Motor.h>

#define delayTime 5000

Motor motor;

void setup() {
}
 
void loop() {
  motor.move(1024);
  delay(delayTime);
  motor.move(-500);
  delay(delayTime);
  motor.move(0);
  motor.breaking(false);
  delay(delayTime);
  motor.move(150);
  delay(delayTime);
  motor.breaking(true);
  delay(delayTime);
  motor.move(-150);
  delay(delayTime);
  motor.move(0);
  delay(delayTime);
  motor.breaking(false);
  delay(delayTime);
}
