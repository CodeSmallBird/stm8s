#include"uart.h"

ANDROID_UART_FORMAT AndroidUart;

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

/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/

void AndroidUartInit(void)
{
	ie_memset(&AndroidUart, 0, sizeof(AndroidUart));
}
/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/
U8 AndroidUartPushSendByte(U8 Data)
{
	U8 Inter;
	U8 Result;

	Result = FALSE;
	DISABLE_INTERRUPT;
	if(AndroidUart.Send.Length < sizeof(AndroidUart.Send.Data))
	{
		AndroidUart.Send.Data[AndroidUart.Send.Write++] = Data;
		if(AndroidUart.Send.Write >= sizeof(AndroidUart.Send.Data))
			AndroidUart.Send.Write = 0;
		AndroidUart.Send.Length++;
		Result = TRUE;
	}
	ENABLE_INTERRUPT;
	return Result;
}
U8 AndroidUartPopSendByte(U8 *Data)
{
	if(AndroidUart.Send.Length)
	{	
		*Data = AndroidUart.Send.Data[AndroidUart.Send.Read++];
		if(AndroidUart.Send.Read >= sizeof(AndroidUart.Send.Data))
			AndroidUart.Send.Read = 0;
		AndroidUart.Send.Length--;
		return TRUE;
	}
	return FALSE;
}

U8 AndroidUartPushReceiveByte(U8 Data)
{
	if(AndroidUart.Rece.Length < sizeof(AndroidUart.Rece.Data))
	{
		AndroidUart.Rece.Data[AndroidUart.Rece.Write++] = Data;
		if(AndroidUart.Rece.Write >= sizeof(AndroidUart.Rece.Data))
			AndroidUart.Rece.Write = 0;
		AndroidUart.Rece.Length++;
		return TRUE;
	}
	return FALSE;
}
U8 AndroidUartPopReceiveByte(U8 *Data)
{
	U8 Inter;
	U8 Result;

	Result = FALSE;
	DISABLE_INTERRUPT;
	if(AndroidUart.Rece.Length)
	{	
		*Data = AndroidUart.Rece.Data[AndroidUart.Rece.Read++];
		if(AndroidUart.Rece.Read >= sizeof(AndroidUart.Rece.Data))
			AndroidUart.Rece.Read = 0;
		AndroidUart.Rece.Length--;
		Result = TRUE;
	}
	ENABLE_INTERRUPT;
	return Result;
}




