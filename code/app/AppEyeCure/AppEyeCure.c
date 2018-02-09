#include"AppEyeCure.h"

#include"..\AppEyeCure\EyeShake\EyeShake.c"
#include"..\AppEyeCure\EyeHeat\EyeHeat.c"
#include"..\AppEyeCure\EarStimulus\EarStimulus.c"

EYE_CURE_INFOR EyeCure;




void EyeCureInit(void)
{
	ie_memset(&EyeCure,0,sizeof(EYE_CURE_INFOR));
	AppEyeShakeInit();
	AppEyeHeatInit();
	AppEarStimulusInit();
}


void FactoryParaSet(void)
{
	memset(&EyeCure.EyeCureParam,0,sizeof(EYE_CURE_PARAM));
}

void NormalParaSet(void)
{
	SET_TEMPER_PARA(40);          
	SET_PLUS_RANGE_PARA(120);
	SET_SHAKE_RANGE_PARA(120);
	SET_WAVE_FOEM_PARA(CONTINUE_WAVE_FORM);           
}

void EnhanceParaSet(void)
{
	SET_TEMPER_PARA(40);          
	SET_PLUS_RANGE_PARA(160);
	SET_SHAKE_RANGE_PARA(180);
	SET_WAVE_FOEM_PARA(CONTINUE_WAVE_FORM);           
}

void CustomerParaSet(void)
{


}



void EyeCureModeSet(u8 CureMode)
{
	SET_SYS_WORK_MODE(CureMode);
	switch(GET_SYS_WORK_MODE)
	{
		case EYE_CURE_FACTORY_MODE:
			FactoryParaSet();
			break;
		case EYE_CURE_NORMAL_MODE:
			NormalParaSet();
			break;
		case EYE_CURE_ENHANCE_MODE:
			EnhanceParaSet();
			break;
		case EYE_CURE_CUSTOMER_MODE:
			CustomerParaSet();
			break;
		default:
			break;
	}
}

void OpenEyeCure(void)
{
	U8 StimulusPara[2] = {0,0};
	SET_SYS_RUN_FLAG(SYS_RUN_ON);
	SetEyeShakeMode(EYE_SHAKE_ON,GET_SHAKE_RANGE_PARA);
	SetEyeHeatMode(EYE_HEAT_ON,GET_TEMPER_PARA);

	StimulusPara[0] = GET_PLUS_RANGE_PARA;
	StimulusPara[1] = GET_WAVE_FOEM_PARA;
	SetEarStimulusMode(EAR_STIMULUS_ON,StimulusPara);
}


void CloseEyeCure(void)
{
	SET_SYS_RUN_FLAG(SYS_RUN_OFF);
	SetEyeShakeMode(EYE_SHAKE_OFF,0);
	SetEyeHeatMode(EYE_HEAT_OFF,0);
	SetEarStimulusMode(EAR_STIMULUS_OFF,0);
}



void EyeCurePolling(void)
{
	TemperCtrlPolling();
}












