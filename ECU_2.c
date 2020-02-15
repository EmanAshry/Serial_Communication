/*
 * ECU_2.c
 * Serial Communication App
 *  Author: Ema
 */ 


#include "USART.h"
#include "spi.h"
#include "pushButton.h"
#include "led.h"
#include "sevenSeg.h"
#include "timers.h"
#include <avr/interrupt.h>

volatile uint8_t spi_speed=0;
volatile uint8_t spi_flag =0;


void spi_app(void)
{
	spi_flag=1;
	spi_speed = SPI_receiveByte();
}


int main(void)
{
	uint8_t Distance = 0;	
	uint8_t BStart_flag =0;
	uint8_t Threshold =2;
	
	En_buttonStatus_t status_0 = Released;
	En_buttonStatus_t status_1 = Released;
	
	USART_Config ST_Config={USART_BAUDRATE,TX_ENABLE,RX_ENABLE,NO_DOUBLE_SPEED,DATA_SIZE_8,PARITY_DISABLE,STOP_1BIT,ASYNCH};
	SPI_ConfigType cnf = {SPI_SLAVE,SPI_INTERRUPT_ENABLED,SPI_F_OSC_4};
		
	USART_init(&ST_Config);
	SPI_setCallBack(&spi_app);
	SPI_init(&cnf);
	
	pushButtonInit(BTN_0);
	pushButtonInit(BTN_1);
	
	sei();			//enable global interrupt
	
    while(1)
    {
		status_0 = pushButtonGetStatus(BTN_0);
		
		if(status_0)
		{
			BStart_flag = 1;
		}

		while (BStart_flag)
		{
			
			if(spi_flag)
			{
				spi_speed = (spi_speed-48);
				
				Distance += spi_speed;
				spi_flag = 0;
			}
			
			status_1 = pushButtonGetStatus(BTN_1);
			
			if(status_1)
			{
				UART_sendByte(Distance);
				Distance = 0;
				BStart_flag = 0;
			}
		}
		
			
        //TODO:: Please write your application code 
    }
}