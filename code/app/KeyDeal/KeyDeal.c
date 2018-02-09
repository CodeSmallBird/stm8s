#include "KeyDeal.h"
#if defined(__DEBUG__)
	#define __DEBUG_KeyDeal
#endif

#define CMD_POWER_KEY        		KEY1_INPUT
#define CMD_NORMAL_KEY        		KEY2_INPUT
#define CMD_ENHANCE_KEY        		KEY3_INPUT
#define CMD_SYSCTRL_KEY        		KEY4_INPUT
KEY_CHECK KeyInput[4];


void CmdPower(void)
{
	if(GET_SYS_POWER_STATE == POWER_OFF)
	{
		SET_SYS_POWER_ON;
	}
	else
	{
		SET_SYS_POWER_OFF;
	}
#if defined(__DEBUG_KeyDeal)
	ie_printf("CmdPower:%d\r\n",(U16)GET_SYS_POWER_STATE);
#endif
	
}

void CmdSysCtrl(void)
{
	if(GET_SYS_RUN_FLAG == SYS_RUN_OFF)
	{
		SET_SYS_RUN_FLAG(SYS_RUN_ON);
		ProtocolSend(CMD_SYS_RUN_SEND);
		OpenEyeCure();
	}
	else
	{
		SET_SYS_RUN_FLAG(SYS_RUN_OFF);
		ProtocolSend(CMD_SYS_STOP_SEND);
		CloseEyeCure();
	}
	
#if defined(__DEBUG_KeyDeal)
		ie_printf("CmdSysCtrl:%d\r\n",(U16)GET_SYS_RUN_FLAG);
#endif
}

void CmdNormalMode(void)
{
	if(GET_SYS_RUN_FLAG == SYS_RUN_ON)
		return;
	
	EyeCureModeSet(EYE_CURE_NORMAL_MODE);
	ProtocolSend(CMD_NORMAL_MODE_SEND);
	
#if defined(__DEBUG_KeyDeal)
	ie_printf("CmdNormalMode\r\n");
#endif
}


void CmdEnhanceMode(void)
{
	if(GET_SYS_RUN_FLAG == SYS_RUN_ON)
		return;

	EyeCureModeSet(EYE_CURE_ENHANCE_MODE);
	ProtocolSend(CMD_ENHANCE_MODE_SEND);
#if defined(__DEBUG_KeyDeal)
	ie_printf("CmdEnhanceMode\r\n");
#endif
	
}


void KeyInit(void)
{
	ie_memset(KeyInput,0,sizeof(KeyInput));
}

U8 GetInput(KEY_CHECK     *Type)
{
	Type->Buffer[1] = Type->Buffer[0];
	Type->Buffer[0] = Type->Value;

	if(Type->Buffer[1] != Type->Buffer[0])
	{
		return FALSE;
	}

	if(Type->Value == Type->NowValue)
	{
		if(Type->ValueTime < INPUT_TIME_MAX)
		{
			Type->ValueTime++;	
		}
	}
	else
	{
		Type->LastTime 	= Type->ValueTime;
		Type->ValueTime = 0;
		Type->LastValue	= Type->NowValue;
		Type->NowValue	= Type->Value;
	}

	if(Type->LastValue != INPUT_VALUE_NULL && Type->NowValue  != INPUT_VALUE_NULL )
		return FALSE;	

	
	if(Type->LastValue == INPUT_VALUE_NULL)
	{
		Type->Value = Type->NowValue;
		Type->State = KEY_DOWN;
	}
	else 
	{
		Type->Value = Type->LastValue;
		Type->State = KEY_UP;
	}
	return TRUE;		
}


void OrderPolling(void)
{
	if((KeyInput[KEY_SYSTEM_POWER].State == KEY_UP)
		&&(KeyInput[KEY_SYSTEM_POWER].Value == 1)
		&&(KeyInput[KEY_SYSTEM_POWER].LastTime > LONG_PRESSTIME))
	{
		CmdPower();
		//memset(&KeyInput[KEY_SYSTEM_POWER],0,sizeof(KEY_CHECK));
		
		memset(KeyInput,0,4*sizeof(KEY_CHECK));
	}

	//if(GET_SYS_POWER_STATE == POWER_OFF)
	//	return;

	if((KeyInput[KEY_SYSTEM_CTRL].State == KEY_UP)
		&&(KeyInput[KEY_SYSTEM_CTRL].Value == 1)
		&&(KeyInput[KEY_SYSTEM_CTRL].LastTime > SHORT_PRESSTIME))
	{
		CmdSysCtrl();
	//	memset(&KeyInput[KEY_SYSTEM_CTRL],0,sizeof(KEY_CHECK));
		memset(KeyInput,0,4*sizeof(KEY_CHECK));
	}

	if((KeyInput[KEY_NORMAL_MODE].State == KEY_UP)
		&&(KeyInput[KEY_NORMAL_MODE].Value == 1)
		&&(KeyInput[KEY_NORMAL_MODE].LastTime >SHORT_PRESSTIME))
	{
		CmdNormalMode();
	//	memset(&KeyInput[KEY_NORMAL_MODE],0,sizeof(KEY_CHECK));
		memset(KeyInput,0,4*sizeof(KEY_CHECK));
	}

	if((KeyInput[KEY_ENHANCE_MODE].State == KEY_UP)
		&&(KeyInput[KEY_ENHANCE_MODE].Value == 1)
		&&(KeyInput[KEY_ENHANCE_MODE].LastTime > SHORT_PRESSTIME))
	{
		CmdEnhanceMode();
	//	memset(&KeyInput[KEY_ENHANCE_MODE],0,sizeof(KEY_CHECK));
		memset(KeyInput,0,4*sizeof(KEY_CHECK));
	}

}


void KeyPolling(void)
{
	u8 i;
	u8 pin_state = 0;
	pin_state |= (CMD_POWER_KEY<<KEY_SYSTEM_POWER);
	pin_state |= (CMD_SYSCTRL_KEY<<KEY_SYSTEM_CTRL);
	pin_state |= (CMD_NORMAL_KEY<<KEY_NORMAL_MODE);
	pin_state |= (CMD_ENHANCE_KEY<<KEY_ENHANCE_MODE);
	
	for(i=0;i<KEY_END;i++)
	{
		KeyInput[i].Value = ((pin_state&(1<<i))?1:0);
		GetInput(&(KeyInput[i]));
	}
	OrderPolling();
}




