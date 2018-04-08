#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_


#ifndef _COMMON_H_
	#include"Common.h"
#endif


/*---------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------*/

#define COM_ANDROID_HEADER1					0xAA
#define COM_ANDROID_HEADER2					0xAA


#define COM_ANDROID_TAIL1					0x55
#define COM_ANDROID_TAIL2					0x55




/*		数据接收状态	*/
enum{
	ANDROID_REVC_STATE_START_CR,
	ANDROID_REVC_STATE_START_LF,
	ANDROID_REVC_STATE_DATA,
	ANDROID_REVC_STATE_TAIL1,
	ANDROID_REVC_STATE_TAIL2
	
};

/*		初始化过程		*/
enum{
	ANDROID_INIT_POWER,
	ANDROID_INIT_USER,
	ANDROID_INIT_PASSWORD,
	ANDROID_INIT_END
};


enum
{
	NORMAL_MODE_CMD,
	ENHANCE_MODE_CMD,
	CONTINUE_PLUS_CMD,
	INTERMITTENT_PLUS_CMD,
	PLUS_RANGE_CMD,
	TEMPER_RANGE_CMD,
	SHAKE_RANGE_CMD,
	TIMING_CMD,
	RESET_FACTOR_CMD,
	START_MODE_CMD,
	PAUSE_MODE_CMD,
	STOP_MODE_CMD
};

enum
{
	CMD_TEMPER_PARA_SEND = 0x01,
	CMD_NORMAL_MODE_SEND,
	CMD_ENHANCE_MODE_SEND,
	CMD_SYS_RUN_SEND,
	CMD_SYS_STOP_SEND,
	CMD_SEND_END
};



//EXTERN ANDROID_UART_FORMAT AndroidUart;
//EXTERN void AndroidUartInit(void);
EXTERN void AndriodPolling(void);
//EXTERN U8 AndroidUartPushReceiveByte(U8 Data);
//EXTERN U8 AndroidUartPopSendByte(U8 *Data);
EXTERN void ProtocolSend(u8 cmd_send);

/*---------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------*/
#define ANDROID_POLLING_TIME							8

#define GET_ANDROID_MODE							(AndroidUart.Mode)
#define SET_ANDROID_MODE(x)						(AndroidUart.Mode = x)

#define GET_ANDROID_TIME							(AndroidUart.Time)
#define SET_ANDROID_TIME(x)						(AndroidUart.Time = x/ANDROID_POLLING_TIME)

#define GET_ANDROID_STATE							(AndroidUart.State)
#define SET_ANDROID_STATE(x)						(AndroidUart.State = x)

#define GET_ANDROID_SEND_STATE					(AndroidUart.SendState)
#define SET_ANDROID_SEND_STATE(x)					(AndroidUart.SendState = x)

#define GET_ANDROID_REVC_STATE					(AndroidUart.RevcState)
#define SET_ANDROID_REVC_STATE(x)					(AndroidUart.RevcState = x)



#endif
