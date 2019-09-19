/**
 * @file Motor.cpp 
 * @author Jardel Brandon / João Santos <jardel.brandon@academico.ifpb.edu.br> <joao.santos@academico.ifpb.edu.br >
 * @version 1.0
 * @Date September 18, 2019
 * @brief This is the implementation of header file to control a motor that is connected to shield bridge H.
 *
 * @section LICENSE
 *
 * Copyright (c) 2010 Arduino LLC. All right reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * @section DESCRIPTION
 * This library allows an Arduino / Genuino board to control the drive of a DC motor,
 * or loads that are within the limit supported by Shield Bridge H, 
 * and can be powered in 4 different states using 4 Arduino / Genuino digital bits for control of Shield Bridge H states.
 *
 * @subsection 
 * For more information about this library please visit us at
 * https://github.com/JardelBrandon/Shield_Ponte_H_Arduino
 */
 
#include "Motor.h"

#define MAX_PWM 255

/**
 * @brief Constructor of Motor
 *
 * Constructor that configures an object of class Motor with the configured pins.
 */
Motor::Motor() {
    pinMode(_MOTOR_PIN_A1, OUTPUT);
    pinMode(_MOTOR_PIN_A2, OUTPUT);
    pinMode(_MOTOR_PIN_B1, OUTPUT);
    pinMode(_MOTOR_PIN_B2, OUTPUT);
    idle();
}

/**
 * @brief Limiter of speed 
 *
 * This method limits the speed value to 0 <x <255
 * 
 * @param int speed of Motor, the engine speed is regulated by arduino pwm
 *
 * @return int limitted speed
 */
int Motor::limiterSpeed(int speed) {
	return abs(speed) > MAX_PWM ? MAX_PWM : abs(speed);
}

/**
 * @brief Engine default state
 *
 * This method resets the motor to its default state, setting all control pins to low logic level.
 */
void Motor::idle() {
	switch (state) {
		case GO:
			digitalWrite(_MOTOR_PIN_A1, LOW);
			digitalWrite(_MOTOR_PIN_B1, LOW);
			break;
		case REVERSE:
			digitalWrite(_MOTOR_PIN_A2, LOW);
			digitalWrite(_MOTOR_PIN_B2, LOW);
			break;
		case LOCKED:
			digitalWrite(_MOTOR_PIN_A1, LOW);
			digitalWrite(_MOTOR_PIN_A2, LOW);
		default:
			digitalWrite(_MOTOR_PIN_A1, LOW);
			digitalWrite(_MOTOR_PIN_B1, LOW);
			digitalWrite(_MOTOR_PIN_A2, LOW);
			digitalWrite(_MOTOR_PIN_B2, LOW);
			break;
	}
	delayMicroseconds(DELAY_CHANGE_STATE);
	state = UNLOCKED;
}

/**
 * @brief Motor drive
 *
 * This method starts the engine by setting it in motion according to the speed passed as a parameter
 * 
 * @param int speed of Motor, the engine speed is regulated by arduino pwm
 * @warning this method param speed max is 255.
 */
void Motor::move(int speed) {
	if (speed > 0) {
		if(state != GO || state != UNLOCKED) {
			idle();
		}
	    analogWrite(_MOTOR_PIN_A1, limiterSpeed(speed));
	    digitalWrite(_MOTOR_PIN_B1, HIGH);
	    state = GO;
	}
	else if (speed < 0){
		if(state != REVERSE || state != UNLOCKED) {
			idle();
		}
	    analogWrite(_MOTOR_PIN_A2, limiterSpeed(speed));
	    digitalWrite(_MOTOR_PIN_B2, HIGH); 
	    state = REVERSE;
	}
	else {
		idle();
	}
}

/**
 * @brief Motor Braking
 *
 * This method brakes the engine by putting it to rest, according to the bollean value passed as a parameter, it is in a locked or free state.
 * 
 * @param bool lock:
 * if true, performs engine lockout;
 * if false, let the engine free. 
 */
void Motor::breaking(bool lock) {
	if (lock) {
		if (state != LOCKED || state != UNLOCKED) {
			idle();	
		}
		digitalWrite(_MOTOR_PIN_A1, HIGH);
		digitalWrite(_MOTOR_PIN_A2, HIGH);
		state = LOCKED;
	}
	else {
		if (state != UNLOCKED) {
			idle();
		}
	}
}
