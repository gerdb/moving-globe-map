/*
 *  Project:      moving globe map
 *  File:         main.c
 *  Author:       gerd bartelt - www.sebulli.com
 *
 *  Description:  main file
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
#include <stdio.h>
#include <math.h>
#include "project.h"
#include "pwm.h"
#include "uart.h"
#include "gps.h"
#include "transform.h"


//#define DEMO

/*
 * local variables
 */
char mystr[60];
unsigned long t=0;

/*
 * Main Init
 */
void MAIN_Init(void) {

}

/*
 * Main function
 */
int main(void) {

	//Initialize all modules
	PWM_Init();
	UART_Init();
	MAIN_Init();
	GPS_Init();
	TRANSFORM_Init();

	while (1) {
#ifndef DEMO
		GPS_Task();
		TRANSFORM_Transform();
#else
		t++;
		a = 100 * sin ((double)t / 10000);
		r = 0.3 * sin ((double)t / 7000);;
#endif
		// Is the position on the map ?
		if ((r > -0.5) && (r < 0.5)) {

			// Set the servos
			PWM_SetServo(0, -a / 360.0 * 28000);
			PWM_SetServo(1, -r * 28000);
		}

		//Debug output
		if (send) {
			send = 0;
			//sprintf(mystr,"\n\r%5.4f %5.4f %d %5.4f %5.4f\n\r" , north, east, quality, a, r);
			//UART_puts(mystr);
		}

	}

}
