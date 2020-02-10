/*
 * USART.c
 *
 * Created: 2/9/2020 2:01:56 PM
 *  Author: Ema
 */ 

#include "USART.h"

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void USART_init(USART_Config * UART_config)
{
	UCSRA.B.U2X1 = UART_config->Speed;
	UCSRB.UCSRB_ST.TXEN1 = UART_config->Tx_enable;
	UCSRB.UCSRB_ST.RXEN1 = UART_config->Rx_enable;
	UCSRB.UCSRB_ST.UCSZ21 = ((UART_config->DataSize)>>2);
	
        /*The URSEL must be one when writing the UCSRC*/
	UCSRC.UCSRC_ST.URSEL1 = 1;
	
	UCSRC.UCSRC_ST.UPM = UART_config->Parity;
	UCSRC.UCSRC_ST.USBS1 = UART_config->Stop;
	UCSRC.UCSRC_ST.UMSEL1 = UART_config->Mode;
	UCSRC.UCSRC_ST.UCSZ = UART_config->DataSize;
	
	
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
