/*
 * ECU_1.c
 * Serial Communication App	
 * Author: Ema
 */ 
//#include <avr/io.h>

//#include "USART.h"


#include "spi.h"
#include "USART.h"
#include "softwareDelay.h"
#include "pushButton.h"
#include "timers.h"
#include "avr/interrupt.h"

volatile uint8_t Speed=0;

ISR(TIMER1_COMPA_vect)
{	
	SPI_sendByte(Speed);
	timer1Set(0);	
}

/* optional to get the init speed value from pc by interrupt
ISR(USART_RXC_vect)
{
	Speed =  UDR;
}*/

int main(void)
{
	SPI_ConfigType cnf = {SPI_MASTER,SPI_INTERRUPT_DISABLED,SPI_F_OSC_4};

	USART_Config ST_Config={USART_BAUDRATE,TX_ENABLE,RX_ENABLE,NO_DOUBLE_SPEED,DATA_SIZE_8,PARITY_DISABLE,STOP_1BIT,ASYNCH};
	
	/* Timer one init to send data every 1 sec*/
	timer1Init(T1_COMP_MODE_OCR1A_TOP,T1_OC1_DIS,T1_PRESCALER_1024, 0x00,15800,0x00,0x00, T1_INTERRUPT_CMP_1A);
	
	SPI_init(&cnf);
	USART_init(&ST_Config);
	
	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);
	
	while (!Speed)
	{
		Speed = UART_recieveByte();
		
	}  

timer1Start();
	
	while(1)
	{		
		if( Prepressed== pushButtonGetStatus(BTN_0))
				{
					cli();			//closing global interrupt
					
					Speed++;	
					UART_sendByte(Speed);
					
					while(Prepressed== pushButtonGetStatus(BTN_0));
					
					sei();		        //closing global interrupt				
				}
				if( Prepressed== pushButtonGetStatus(BTN_1))
				{
					cli();			//closing global interrupt
					Speed--;
					UART_sendByte(Speed);
					
					while(Prepressed== pushButtonGetStatus(BTN_1));	
					sei();			//closing global interrupt
				}		
	}
}


/*
	SPCR =0b00110001;
	SPSR =0x00;	
	PORTB_DIR=0b10111110;
	SPCR =0b01110001;
	
   */

