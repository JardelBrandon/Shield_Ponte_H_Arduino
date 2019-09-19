/**
 * @file Motor.h
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
 * \section DESCRIPTION
 * This library allows an Arduino / Genuino board to control the drive of a DC motor,
 * or loads that are within the limit supported by Shield Bridge H, 
 * and can be powered in 4 different states using 4 Arduino / Genuino digital bits for control of Shield Bridge H states.
 *
 * \subsection 
 * For more information about this library please visit us at
 * https://github.com/JardelBrandon/Shield_Ponte_H_Arduino
 */
 
#ifndef PONTE_H
#define PONTE_H

#include "Arduino.h"

/**
 * @brief States of Motor
 * 
 * Representation of different motor states used by h-bridge control pins
 */
enum State {
    GO,      /**< Move to one side. */
	REVERSE, /**< Move to other side. */
	LOCKED,  /**< stuck. */
	UNLOCKED /**< Default and free State. */
};


/**
 * @brief Motor Class
 *
 * Definition of Motor class attributes and methods
 */
class Motor {
    public:
        Motor();
        
        void move(int speed);
        void breaking(bool lock);    
 
    private:
        const uint8_t _MOTOR_PIN_A1 = 11;
        const uint8_t _MOTOR_PIN_B1 = 9;
        const uint8_t _MOTOR_PIN_A2 =  10;
        const uint8_t _MOTOR_PIN_B2 =  8;
        const int DELAY_CHANGE_STATE = 1; /*!< Microseconds @f$ 1 µs = 1 * 10^{-9} s @f$ */
		State state;
		
		void idle();
		int limiterSpeed(int speed);
};

#endif
