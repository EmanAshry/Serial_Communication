/*
 * USART.c
 *
 * Created: 2/9/2020 2:01:56 PM
 *  Author: Ema
 */ 

#include "USART.h"

/*Baud prescale for no double speed*/
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void USART_init(USART_Config * UART_config)
{
	/*To set the last bit at Register C*/
	uint8_t UCSRC_URSEL_Value= 128;

	/ * U2X for transmission speed * /	
	UCSRA.B.U2X1 = UART_config->Speed;

	/ ************************** UCSRB Description **************************
	 * RXEN  = 1 Receiver Enable
	 * TXEN  = 1 Transmitter Enable
	 *********************************************************************** /
	UCSRB.UCSRB_ST.TXEN1 = UART_config->Tx_enable;
	UCSRB.UCSRB_ST.RXEN1 = UART_config->Rx_enable;
	
	/ ************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = Asynch/Synch Operation
	 * UPM1:0  = parity bit
	 * USBS    = stop bit
	 * UCSZ1:0 = data size
	 *********************************************************************** / 
	UCSRC.UCSRC_B = UCSRC_URSEL_Value|(UART_config->Parity)|(UART_config->Stop)|(UART_config->Mode)|(UART_config->DataSize); 
	
	/ * First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH* /
	UBRRH = BAUD_PRESCALE>>8;
	UBRRL = BAUD_PRESCALE;
	
}

void UART_sendByte(const uint8_t data)
{
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for 
	 * transmitting a new byte so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA.UCSRA_B,UDRE)){}
	/* Put the required data in the UDR register and it also clear the UDRE flag as 
	 * the UDR register is not empty now */	 
	UDR = data;
}

uint8_t UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this 
	 * flag is set to one */
	while(BIT_IS_CLEAR(UCSRA.UCSRA_B,RXC)){}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag 
	   will be cleared after read this data */	 
    return UDR;		
}

void UART_sendString(const uint8_t *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}

void UART_receiveString(uint8_t *Str)
{
	uint8_t i = 0;
	Str[i] = UART_recieveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}
	Str[i] = '\0';
}
