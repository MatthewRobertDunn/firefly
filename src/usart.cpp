#include "usart.h"

// --------------------------------------------------------
/**
 * @brief Initialize USART1 with predefined settings
 */
// --------------------------------------------------------

#if defined (UART_MODE_RX)
    static volatile uint8_t uart_rxHead = 0, uart_rxTail = 0;
    static volatile uint16_t lastRXerrorFlag = 0;
#endif

void UART_init()
{
	uint16_t tmp16 = USART_WordLength_8b | USART_Parity_No;
	RCC->APB2PCENR |= UART_PORT_RCC | RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO;

	AFIO->PCFR1 &= UART_AFIO_PCFR1_RESET_MASK;
	AFIO->PCFR1 |= UART_AFIO_PCFR1;

#if defined(UART_MODE_TX)
	UART_PORT->CFGLR &= ~(0xf<<(4*UART_PIN_TX));
	UART_PORT->CFGLR |= (GPIO_Speed_10MHz | GPIO_CNF_OUT_PP_AF)<<(4*UART_PIN_TX);
	tmp16 |= USART_Mode_Tx;
	uart_txHead = 0;
	uart_txTail = 0;
#endif
#if defined (UART_MODE_RX)
	UART_PORT->CFGLR &= ~(0xf<<(4*UART_PIN_RX));
	UART_PORT->CFGLR |= (GPIO_Speed_10MHz | GPIO_CNF_IN_PUPD)<<(4*UART_PIN_RX);
	tmp16 |= USART_Mode_Rx | UART_IT_RXC_ENABLE;	// enable TX and rx complete interrupt
	uart_rxHead = 0;
	uart_rxTail = 0;	
#endif
	NVIC_EnableIRQ(USART1_IRQn);
	USART1->CTLR1 =  tmp16;
	USART1->CTLR2 = USART_StopBits_1;
	USART1->CTLR3 = USART_HardwareFlowControl_None;
	USART1->BRR = UART_BRR;
	USART1->CTLR1 |= CTLR1_UE_Set;	
}



#if defined (UART_MODE_RX)
/**
 * @brief  return byte from ringbuffer  
 * 
 * @return uint16_t l	lower byte:  received byte from ringbuffer
          				higher byte: last receive error
 */
uint16_t UART_getc(void)
{    
    uint8_t tmp8, data;

    if ( uart_rxHead == uart_rxTail ) return UART_NO_DATA;

    tmp8 = (uart_rxTail + 1) & UART_RX_BF_MASK;
    uart_rxTail = tmp8; 
    
    data = uart_rx_bf[tmp8];
    
    return (lastRXerrorFlag | data);
}
#endif

extern "C" void USART1_IRQHandler(void)
{
	uint16_t status = USART1->STATR;
	uint16_t lastErr = 0;
	uint8_t tmp8, data;
	
	// check for errors and store the flags
	if (status & UART_IT_ERROR_MASK)
	{
		lastErr = (status & UART_IT_ERROR_MASK)<<8;
	}
#if defined (UART_MODE_RX)
	if (status & UART_IT_RXC_ENABLE)  // byte received, the same bit as in CTRL1
	{
		data = USART1->DATAR;
		tmp8 = (uart_rxHead + 1) & UART_RX_BF_MASK;
		if (tmp8 == uart_rxTail)	lastErr |= UART_ERR_RXBUF_OVERFLOW;
		uart_rxHead = tmp8;
		uart_rx_bf[tmp8] = data;
	}
	lastRXerrorFlag = lastErr & 0xFF00;
#endif
#if defined(UART_MODE_TX)
	if (status & UART_IT_TXE_ENABLE)  // tx empty, the same bit as in CTRL1
	{
		if (uart_txHead != uart_txTail)
		{
			tmp8 = (uart_txTail + 1) & UART_TX_BF_MASK;
			uart_txTail = tmp8;
			USART1->DATAR = uart_tx_bf[tmp8];
		}
		else 		// all sent, disable interrupt
		{
			USART1->CTLR1 &= UART_IT_TXE_DISABLE;
		}
		lastTXerrorFlag = lastErr & 0xFF00;
	}

#endif
}