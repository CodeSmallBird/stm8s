#include"EyeHeat.h"
#include"pid.c"

#if defined(__DEBUG__)
	#define __DEBUG_HEAT
#endif

EYE_HEAT_INFOR    EyeHeatMode;


void AppEyeHeatInit(void)
{
	memset(&EyeHeatMode,0,sizeof(EyeHeatMode));
	PID_init();
}



void SetEyeHeatMode(U8 Switch,U8 Param)
{
	EyeHeatMode.Switch = Switch;
	if(EyeHeatMode.Switch == EYE_HEAT_ON)
	{
		SET_TRAGET_TEMPER(((U16)Param)*100);
	}
	else
	{

	}
}


void TemperCtrlPolling(void)
{
	static U8 temper_send_delay = 0;
	static S16 ActualSetTemper = 0;
	SET_REAL_TEMPER(temper_change());

	if(EyeHeatMode.Switch == EYE_HEAT_OFF)
		return;
    if(ActualSetTemper >= GET_REAL_TEMPER)	
    {
		TEM_EN_ON;
	}
	else
	{
		TEM_EN_OFF;
	}
	
	if(GET_HEAT_DETEC_POOLING_TIME)
	{
		GET_HEAT_DETEC_POOLING_TIME--;
		return;
	}
	SET_HEAT_DETEC_POOLING_TIME(1000);	
	if(GET_REAL_TEMPER >(GET_TRAGET_TEMPER -500))
	{
		ActualSetTemper =(S16) PID_realize((float)GET_TRAGET_TEMPER, (float)GET_REAL_TEMPER);
	}
	else
	{
		ActualSetTemper = GET_TRAGET_TEMPER -400;
	}
	temper_send_delay++;
	if(temper_send_delay>1)
	{
		ProtocolSend(CMD_TEMPER_PARA_SEND);
		temper_send_delay = 0;
	}
	EarStimulusPolling();
#if defined(__DEBUG_HEAT)     
	ie_printf("ActualSetTemper:%d\r\n",(U16)ActualSetTemper);
#endif
}


#ifdef __DEBUG_HEAT
	#undef __DEBUG_HEAT
#endif



