#include"EyeShake.h"

EYE_SHAKE_INFOR    EyeShakeMode;


void AppEyeShakeInit(void)
{
	memset(&EyeShakeMode,0,sizeof(EyeShakeMode));
}


void SetEyeShakeMode(U8 Switch,U8 Param)
{
	EyeShakeMode.Switch = Switch;
	if(EyeShakeMode.Switch == EYE_SHAKE_ON)
	{
		EyeShakeMode.Level = Param;
		set_time3_ch1_duty(EyeShakeMode.Level);
	}
	else
		set_time3_ch1_duty(0);

}




