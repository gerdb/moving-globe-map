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
#include "project.h"
#include "pwm.h"
#include "uart.h"

/*
 * local variables
 */
char mystr[60];


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

	while (1) {
		GPS_Task();
		PWM_SetServo(1,0);
		sprintf(mystr,"%6.3f" , 3.123);


		UART_puts(mystr);
	}

}
