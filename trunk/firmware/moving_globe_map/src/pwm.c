/*
 *  Project:      moving globe map
 *  File:         pwm.c
 *  Author:       gerd bartelt - www.sebulli.com
 *
 *  Description:  Servo signal generation
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <avr/io.h>
#include "project.h"
#include "pwm.h"

/*
 * Initialize the PWM module
 */
void PWM_Init(void) {

	// OC1A and OC1B as output
	DDRB |= _BV(PB1);
	DDRB |= _BV(PB2);
	PORTB &= ~_BV(PB1);
	PORTB &= ~_BV(PB2);

	// Set at BOTTOM, Clear at match
	TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11);

	// Fast PWM, Top of ICR1, prescaler: 1:1
	TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);

	// Set period time to 4ms
	ICR1 = 64000;

	// Set PWM of Servo1 to 1500µs
	OCR1A = 1500*16;

	// Set PWM of Servo1 to 1500µs
	OCR1B = 1500*16;
}

/*
 * Set the PWM of the servo
 *
 * \param servo Servo number 0 or 1
 * \param val Servo value from -8000 ... +8000
 */
void PWM_SetServo(unsigned char servo, signed int val) {

	//Limit the servo values
	if (val < -12000)
		val = -12000;
	if (val > 12000)
		val = 12000;

	if (servo == 0) {
		OCR1A = 1500*16 + val;
	}
	if (servo == 1) {
		OCR1B = 1500*16 + val;
	}
}

