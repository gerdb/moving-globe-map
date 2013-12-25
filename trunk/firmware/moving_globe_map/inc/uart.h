/*
 *  Project:      moving globe map
 *  File:         uart.h
 *  Author:       gerd bartelt - www.sebulli.com
 *
 *  Description:  header file for uart.c
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
#ifndef UART_H_
#define UART_H_

//Function prototypes
void UART_Init(void);
void UART_Tx(char data);
char UART_Rx(void);
void UART_puts(char s[]);

#endif /* UART_H_ */
