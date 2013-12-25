/*
 *  Project:      moving globe map
 *  File:         gps.c
 *  Author:       gerd bartelt - www.sebulli.com
 *
 *  Description:  Decodes the GPS position
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
#include "gps.h"
#include "uart.h"

// constants
#define POS_N 18 // North coordinates (latitude)
#define POS_E 30 // East coordinates (longitude)
#define POS_Q 43 // Fix quality
#define POS_LENGTH 45
const unsigned char pattern[] = "$GPGGA,??????.???,????.????,N,?????.????,E,?,";


// global variables
unsigned char send = 0;
unsigned char dec;
float north = 0.0;
float east = 0.0;
unsigned char quality = 0;

unsigned int deg,min,post;

// local variables
unsigned char spos = 0;
char pat;

/*
 * Initialize the GPS module
 */
void GPS_Init(void){

}

/*
 * Decode the GPS data
 */
void GPS_Task(void) {
	char c;

	// Receive the next character
	c = UART_Rx();
	dec = c-'0';
	pat = pattern[spos];

	if ( ( pat == '?') || (pat == c)) {
		// Reset the variables
		if ( (spos == POS_N) || (spos == POS_E)) {
			deg = 0;
			min = 0;
			post = 0;
		}

		// Extract the north coordinates
		if (spos >= (POS_N) && (pat == '?')) {
			if (spos <= (POS_N+1)) {
				deg *= 10;
				deg += dec;
			} else if ((spos <= (POS_N+3))) {
				min *= 10;
				min += dec;
			} else if ((spos <= (POS_N+8))) {
				post *= 10;
				post += dec;
			}
		}

		// Convert the result to degrees
		if (spos == (POS_N+8) ) {
			north = post;
			north = north / 10000;
			north += min;
			north /= 60.0;
			north += deg;
		}

		// Extract the east coordinates
		if (spos >= (POS_E) && (pat == '?')) {

			if (spos <= (POS_E+2)) {
				deg *= 10;
				deg += dec;
			} else if ((spos <= (POS_E+4))) {
				min *= 10;
				min += dec;
			} else if ((spos <= (POS_E+9))) {
				post *= 10;
				post += dec;
			}
		}

		// Convert the result to degrees
		if (spos == (POS_E+9) ) {

			east = post;
			east = east / 10000;
			east += min;
			east /= 60.0;
			east += deg;
		}

		// Convert the result to degrees
		if (spos == (POS_Q) ) {

			quality = dec;
			send = 1;
		}
		spos++;
	}
	else {
		spos = 0;
	}


	// Limit to length of pattern
	if (spos > POS_LENGTH)
		spos = 0;
}
