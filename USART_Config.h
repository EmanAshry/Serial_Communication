/*
 * USART_Config.h
 *
 * Created: 2/9/2020 2:04:02 PM
 *  Author: Ema
 */ 


#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_
#include "std_types.h"

/* USART */
#define UBRRL   *((reg_type8_t)(0X29))
#define UBRRH	*((reg_type8_t)(0X40))
#define UDR     *((reg_type8_t)(0X2C))

/*bitfields*/

#define UCSRB   (*(volatile UCSRB_Reg*)(0X2A))
#define UCSRA   (*((volatile UCSRA_Reg*)0X2B))
#define UCSRC	(*(volatile UCSRC_Reg*)(0X40))


/* UCSRA */
#define RXC     7
#define TXC     6
#define UDRE    5
#define FE      4
#define DOR     3
#define PE      2
#define U2X     1
#define MPCM    0

/* UCSRB */
#define RXCIE   7
#define TXCIE   6
#define UDRIE   5
#define RXEN    4
#define TXEN    3
#define UCSZ2   2
#define RXB8    1
#define TXB8    0

/* UCSRC */
#define URSEL   7
#define UMSEL   6
#define UPM1    5
#define UPM0    4
#define USBS    3
#define UCSZ1   2
#define UCSZ0   1
#define UCPOL   0

/************************************************************************/
/*					      bit manipulation                              */
/************************************************************************/

typedef struct {
	uint8_t MPCM1   :1;
	uint8_t U2X1    :1;
	uint8_t PE1	    :1;
	uint8_t DOR1    :1;
	uint8_t FE1     :1;
	uint8_t UDRE1   :1;
	uint8_t TXC1	:1;
	uint8_t RXC1    :1;
}UCSRA_ST;

typedef union {
	uint8_t UCSRA_B;
	UCSRA_ST B;
	
}UCSRA_Reg;

typedef union {
	uint8_t UCSRB_B;
	struct {
		uint8_t TXB81   :1;
		uint8_t RXB81   :1;
		uint8_t UCSZ21  :1;
		uint8_t TXEN1   :1;
		uint8_t RXEN1   :1;
		uint8_t UDRIE1  :1;
		uint8_t TXCIE1  :1;
		uint8_t RXCIE1  :1;
	}UCSRB_ST;
}UCSRB_Reg;

typedef union {
	uint8_t UCSRC_B;
	struct {
		uint8_t UCPOL1  :1;
		uint8_t UCSZ	:2;
		uint8_t USBS1   :1;
		uint8_t UPM		:2;
		uint8_t UMSEL1  :1;
		uint8_t URSEL1  :1;
	}UCSRC_ST;
}UCSRC_Reg;


#endif /* USART_CONFIG_H_ */