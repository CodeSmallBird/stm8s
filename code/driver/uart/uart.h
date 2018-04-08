#ifndef _UART_H_
#define _UART_H_
//#include "stm8s_uart1.h"
//#include "stm8s_uart3.h"


#ifndef _COMMON_H_
	#include"Common.h"
#endif


#if defined(DEBUG_USE_UART)
#define ie_printf		printf
#else
#define ie_printf		/##/
#endif

EXTERN  void uart_init(void);
#if defined(_SUPPORT_ANDRIOD_CONNECT_)
#define ANDROID_UART_SEND_LENGTH			30
#define ANDROID_UART_REVC_LENGTH			30
#define ANDROID_REVC_DATA_SIZE				20

#define ANDROID_UART_REVC_FIFO_LENGTH		20



typedef struct{
	U8 Mode;
	U8 Time;
	U8 State;
	U8 SendState;
	U8 RevcState;
	struct{
		U8 	Data[ANDROID_UART_SEND_LENGTH];
		U8	Read;
		U8	Write;
		U8 	Length;
	}Send;
	struct{
		U8 	Data[ANDROID_UART_REVC_LENGTH];
		U8	Read;
		U8	Write;
		U8 	Length;
	}Rece;	
	struct{
		U8 	Data[ANDROID_UART_REVC_FIFO_LENGTH];
		U8 	Length;
	}ReceFifo;

}ANDROID_UART_FORMAT;


EXTERN void AndriodUartInterrupt_Rx_Func(void);
EXTERN void AndriodUartInterrupt_Tx_Func(void);
EXTERN char DebugToUart(char c);




EXTERN ANDROID_UART_FORMAT AndroidUart;
EXTERN void AndroidUartInit(void);
EXTERN void AndriodPolling(void);
EXTERN U8 AndroidUartPushReceiveByte(U8 Data);
EXTERN U8 AndroidUartPushSendByte(U8 Data);

EXTERN U8 AndroidUartPopSendByte(U8 *Data);
EXTERN U8 AndroidUartPopReceiveByte(U8 *Data);

EXTERN void ProtocolSend(u8 cmd_send);


#endif
#endif

