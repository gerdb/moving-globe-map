/*
 *  Project:      moving globe map
 *  File:         uart.c
 *  Author:       gerd bartelt - www.sebulli.com
 *
 *  Description:  Serial communication with the GPS module
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
#include "uart.h"

/*
 * Initialize the UART module
 */
void UART_Init(void)
{
    // Set baud rate to 9k6
    UBRR0H = 0;
    UBRR0L = 207;

    // Enable 2x speed
    UCSR0A = _BV(U2X0);

    // enabled receive and transmit
    UCSR0B = _BV(RXEN0)|_BV(TXEN0);

    // Async. mode, 8N1
    UCSR0C = (0<<UMSEL00)|(0<<UPM00)|(0<<USBS0)|(3<<UCSZ00)|(0<<UCPOL0);
}

/*
 * Send one byte
 *
 * \param data the byte to send
 */
void UART_Tx(char data)
{
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
}



/*
 * Wait and read one byte from the serial port
 *
 * \return the received byte/character
 */
char UART_Rx(void)
{
    while (!(UCSR0A & (1<<RXC0)));
    return UDR0;
}

