#include"uart.h"


#if defined(DEBUG_USE_UART)
char DebugToUart(char c)
{
	while((UART3->SR&0x80)==0x00); 
	UART3->DR = ((u8)c);
    return c;
}


char putchar (char Char)
{
	while((UART3->SR&0x80)==0x00); 
	UART3->DR = ((u8)Char);
    return Char;
}

void debug_uart_init(void)
{
	UART3_Init(115200, UART3_WORDLENGTH_8D, 
					UART3_STOPBITS_1, UART3_PARITY_NO, 
	                UART3_MODE_TX_ENABLE);
	
	UART3_Cmd(ENABLE);
	ie_printf("debug_uart_inint_success!!");
}

#endif


#if defined(_SUPPORT_ANDRIOD_CONNECT_)
void AndriodUartInterrupt_Rx_Func(void)
{
	u8 RecvData = 0;
	RecvData  = UART1_ReceiveData8();
	AndroidUartPushReceiveByte(RecvData);
}


void AndriodUartInterrupt_Tx_Func(void)
{
	u8 Data = 0;
	UART_EN_BOARD_TO_ANDROID;
	while(AndroidUartPopSendByte(&Data))
	{
		UART1_SendData8(Data);
	}	
	UART_EN_ANDROID_TO_BOARD;
}
#endif



void uart_init(void)
{
#if defined(DEBUG_USE_UART)
	debug_uart_init();
#endif
#if 1
	UART1_DeInit();

	UART1_Init(9600, UART1_WORDLENGTH_8D, 
					UART1_STOPBITS_1, UART1_PARITY_NO, 
					UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);

	UART1_ITConfig(UART1_IT_RXNE, ENABLE);
	UART1_Cmd(ENABLE);
#endif

}





