/*
 * USART.h
 *
 * Created: 2/9/2020 2:02:18 PM
 *  Author: Ema
 */ 


#ifndef USART_H_
#define USART_H_

#include "USART_Config.h"
/*******************************************************************************
 *                      User Defined Types                                     *
 *******************************************************************************/

typedef struct usart_config{
	uint16_t Baudrate;
	uint8_t	 Tx_enable;
	uint8_t  Rx_enable;
	uint8_t  Speed;
	uint8_t  DataSize;
	uint8_t  Parity;
	uint8_t  Stop;
	uint8_t	 Mode;
}USART_Config;

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* UART Driver Baud Rate */
#define USART_BAUDRATE 9600
#define F_CPU 16000000UL

#define DOUBLE_SPEED			1
#define NO_DOUBLE_SPEED			0
#define SYNCH					(1<<6)
#define ASYNCH					0
#define PARITY_DISABLE			0
#define PARITY_EVEN				(1<<5)
#define PARITY_ODD				((1<<5)|(1<<4))
#define STOP_1BIT				0
#define STOP_2BIT				(1<<3)
#define DATA_SIZE_5				0
#define DATA_SIZE_6				1
#define DATA_SIZE_7				2
#define DATA_SIZE_8				((1<<1)|(1<<2))
#define CLOCK_POL_FALLING		0
#define CLOCK_POL_RISING		1
#define TX_ENABLE				1
#define RX_ENABLE				1

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) (REG & (1<<BIT))

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) (!(REG & (1<<BIT)))


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

extern void USART_init(USART_Config * UART_config);

extern void UART_sendByte(const uint8_t data);

extern uint8_t UART_recieveByte(void);

extern void UART_sendString(const uint8_t *Str);

extern void UART_receiveString(uint8_t *Str); // Receive until #




#endif /* USART_H_ */