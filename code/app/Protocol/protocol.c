#include "protocol.h"

#if defined(__DEBUG__)
	#define __DEBUG_Protocol
#endif


ANDROID_UART_FORMAT AndroidUart;

#define COM_ANDROID_HEADER1					0xAA
#define COM_ANDROID_HEADER2					0xAA


#define COM_ANDROID_TAIL1					0x55
#define COM_ANDROID_TAIL2					0x55



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

/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/

void ProRevcData(U8 *CmdData)
{
	switch(CmdData[0])
	{
		case NORMAL_MODE_CMD:
			EyeCureModeSet(EYE_CURE_NORMAL_MODE);
			break;
		
		case ENHANCE_MODE_CMD:
			EyeCureModeSet(EYE_CURE_ENHANCE_MODE);
			break;
		
		case CONTINUE_PLUS_CMD:
			SET_WAVE_FOEM_PARA(CONTINUE_WAVE_FORM); 		  
			EyeCureModeSet(EYE_CURE_CUSTOMER_MODE);
			break;
			
		case INTERMITTENT_PLUS_CMD:
			SET_WAVE_FOEM_PARA(BREAK_WAVE_FORM); 		  
			EyeCureModeSet(EYE_CURE_CUSTOMER_MODE);
			break;
			
		case PLUS_RANGE_CMD:
			SET_PLUS_RANGE_PARA(CmdData[1]);
			EyeCureModeSet(EYE_CURE_CUSTOMER_MODE);
			break;
			
		case TEMPER_RANGE_CMD:
			SET_TEMPER_PARA(CmdData[1]);		  
			EyeCureModeSet(EYE_CURE_CUSTOMER_MODE);
			break;
			
		case SHAKE_RANGE_CMD:
			SET_SHAKE_RANGE_PARA(CmdData[1]);
			EyeCureModeSet(EYE_CURE_CUSTOMER_MODE);
			break;
			
		case TIMING_CMD:
			
			break;
		case RESET_FACTOR_CMD:
			
			EyeCureModeSet(EYE_CURE_FACTORY_MODE);
			break;
		
		case START_MODE_CMD:
			if(GET_SYS_RUN_FLAG == SYS_RUN_OFF)
			{
				OpenEyeCure();
			}
			break;
			
		case PAUSE_MODE_CMD:
		case STOP_MODE_CMD:
			if(GET_SYS_RUN_FLAG == SYS_RUN_ON)
			{
				CloseEyeCure();
			}
			break;

		default:
			break;
	}


	//ÃüÁî´¦Àí
	ie_memset((U8 *)&AndroidUart.ReceFifo,0,sizeof(AndroidUart.ReceFifo));	
}

/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/
void AndriodPolling(void)
{
	U8 Data;
	
#if defined(__DEBUG_Protocol)
		{
			U8 i;
			if(AndroidUart.Rece.Length>0)
			{
				ie_printf("Recv_data:\r\n");
				for(i=0;i<AndroidUart.Rece.Length;i++)
				{
					ie_printf("0x%x ",(U16)AndroidUart.Rece.Data[AndroidUart.Rece.Read+i]);
				}
				ie_printf("--GET_ANDROID_REVC_STATE:%d\r\n",(U16)GET_ANDROID_REVC_STATE);
			}
		}
#endif
	while(AndroidUartPopReceiveByte(&Data))
	{

		switch(GET_ANDROID_REVC_STATE)
		{
			case ANDROID_REVC_STATE_START_CR:
				if(Data == COM_ANDROID_HEADER1)
				{
					SET_ANDROID_REVC_STATE(ANDROID_REVC_STATE_START_LF);
				}
				break;
			case ANDROID_REVC_STATE_START_LF:
				if(Data == COM_ANDROID_HEADER2)
				{
					SET_ANDROID_REVC_STATE(ANDROID_REVC_STATE_DATA);
					AndroidUart.ReceFifo.Length = 0;	
				}
				else SET_ANDROID_REVC_STATE(ANDROID_REVC_STATE_START_CR); 
				break;
			case ANDROID_REVC_STATE_DATA:
				AndroidUart.ReceFifo.Data[AndroidUart.ReceFifo.Length] = Data;
				if(AndroidUart.ReceFifo.Length <(ANDROID_REVC_DATA_SIZE-1))AndroidUart.ReceFifo.Length++;			
				if(AndroidUart.ReceFifo.Length == 2)
					SET_ANDROID_REVC_STATE(ANDROID_REVC_STATE_TAIL1);
				break;
			case ANDROID_REVC_STATE_TAIL1:
				if(Data == COM_ANDROID_TAIL1)
					SET_ANDROID_REVC_STATE(ANDROID_REVC_STATE_TAIL2);
				else SET_ANDROID_REVC_STATE(ANDROID_REVC_STATE_START_CR); 
				break;

			case ANDROID_REVC_STATE_TAIL2:
				SET_ANDROID_REVC_STATE(ANDROID_REVC_STATE_START_CR); 
				if(Data == COM_ANDROID_TAIL2)
				{
					ProRevcData(AndroidUart.ReceFifo.Data);
					return;
				}
				break;
			
		}

	//	AndroidUartPushSendByte(Data);

	}
}



#define SEND_LENGTH          7
#define SEND_CMD			 2
#define SEND_DATA_1          3
#define SEND_DATA_2          4



void ProtocolSend(u8 cmd_send)
{
	U8 SendData[SEND_LENGTH]={0xAA,0xAA,0x00,0x00,0x00,0x55,0x55};
	U8 i;
	switch(cmd_send)
	{
		case CMD_TEMPER_PARA_SEND:
			SendData[SEND_DATA_1] = GET_REAL_TEMPER/100;
			SendData[SEND_DATA_2] = GET_REAL_TEMPER%100/10;
			break;
		case CMD_NORMAL_MODE_SEND:

			break;
		case CMD_ENHANCE_MODE_SEND:

			break;
		case CMD_SYS_RUN_SEND:

			break;
		case CMD_SYS_STOP_SEND:

			break;
		default:
			break;

	}
	SendData[SEND_CMD] = cmd_send;
	for(i=0;i<7;i++)
		AndroidUartPushSendByte(SendData[i]);
}






