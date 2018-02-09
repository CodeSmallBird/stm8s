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
EXTERN void AndriodUartInterrupt_Rx_Func(void);
EXTERN void AndriodUartInterrupt_Tx_Func(void);
EXTERN char DebugToUart(char c);

#endif
#endif

