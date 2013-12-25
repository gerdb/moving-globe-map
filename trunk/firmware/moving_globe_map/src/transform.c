/*
 *  Project:      moving globe map
 *  File:         tranform.c
 *  Author:       gerd bartelt - www.sebulli.com
 *
 *  Description:  Transforms the GPS coordinates into servo values
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
#include <math.h>
#include "project.h"
#include "gps.h"
#include "uart.h"
#include "transform.h"

// constants
// Coordinates (corner of the map) from http://www.svensoltmann.de/google-maps-koordinaten.html
#define TOP			48.753888524335096
#define RIGHT		8.286761999261216
#define BOTTOM		48.583814325265074
#define LEFT		8.029322504735319
#define OFFSET_A	-75 //Degree


#define HEIGHT (TOP-BOTTOM)
#define WIDTH  (RIGHT-LEFT)
#define OFFSET_N ((TOP+BOTTOM)/2)
#define OFFSET_E ((RIGHT+LEFT)/2)



// global variables
double r = 0.0; // radius
double a = 0.0; // angle

// local variables
double n; // Offset north
double e; // Offset north


/*
 * Initialize the Module
 */
void TRANSFORM_Init(void){

}

/*
 * Do the transformation
 */
void TRANSFORM_Transform(void) {

	// Relative to the center of the map (globe)
	n = north - OFFSET_N;
	e = east  - OFFSET_E;


	// Scale the coordinates to +- 1.000
	n /= (HEIGHT/2.0);
	e /= (WIDTH/2);

	// Calculate the radius
	r = sqrt(n*n + e*e);

	// Calculate the angle
	if (n != 0.0) {
		a = atan(e/n);
	}
	else {
		a = M_PI / 2;
	}

	// negative north value
	if (n < 0.0) {
		a += M_PI;
	}

	// convert to degrees
	a = a / M_PI * 180.0;

	// Offset
	a += OFFSET_A;

	// Limit a to -90..270
	if (a < 90.0) {
		a += 360.0;
	}
	if (a >= 270.0) {
		a -= 360.0;
	}

	// Use a negative radius for angle 90' .. 270'
	if (a >= 90.0) {
		a -= 180.0;
		r *= -1;
	}

}
