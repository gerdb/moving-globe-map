/*
 *  Project:      moving globe map
 *  File:         tranform.h
 *  Author:       gerd bartelt - www.sebulli.com
 *
 *  Description:  header file for tranform.c
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
#ifndef TRANSFORM_H_
#define TRANSFORM_H_

// global variables
extern double r; // radius
extern double a; // angle


//Function prototypes
void TRANSFORM_Init(void);
void TRANSFORM_Transform(void);

#endif /* TRANSFORM_H_ */
