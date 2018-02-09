#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#ifndef _COMMON_H_
	#include"Common.h"
#endif


/*---------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------*/


#define ANDROID_UART_SEND_LENGTH			30
#define ANDROID_UART_REVC_LENGTH			30
#define ANDROID_REVC_DATA_SIZE				20

#define ANDROID_UART_REVC_FIFO_LENGTH		20


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

/*		蓝牙工作模式	*/
enum{
	ANDROID_MODE_DISCONNECT,
	ANDROID_MODE_PAIRING,
	ANDROID_MODE_CONNECT,
	ANDROID_MODE_WORKING
};

/*		蓝牙电话状态	*/
enum{
	TEL_STATE_DIALED_CALLS,
	TEL_STATE_RECIVED_CALLS,
	TEL_STATE_HOST_CALL,
	TEL_STATE_HOST_MUSIC,
	TEL_STATE_PHONEBOOK
};


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



EXTERN ANDROID_UART_FORMAT AndroidUart;
EXTERN void AndroidUartInit(void);
EXTERN void AndriodPolling(void);
EXTERN U8 AndroidUartPushReceiveByte(U8 Data);
EXTERN U8 AndroidUartPopSendByte(U8 *Data);
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
