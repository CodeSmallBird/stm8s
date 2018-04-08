#include"EarStimulus.h"

EAR_STIMULUS_INFOR    EarStimulusMode;


void AppEarStimulusInit(void)
{
	memset(&EarStimulusMode,0,sizeof(EarStimulusMode));
}

void SetEarStimulusMode(U8 Switch,U8 *Param)
{
	EarStimulusMode.Switch = Switch;
	if(EarStimulusMode.Switch == EAR_STIMULUS_ON)
	{
		EarStimulusMode.Level = Param[0];
		EarStimulusMode.Mode = Param[1];
		if(EarStimulusMode.Mode == CONTINUE_WAVE_FORM)
		{
			//SET_PWM1_DUTY(5);
			//set_time1_ch1_duty(0);
			//set_time1_ch2_duty(EarStimulusMode.Level);
			//set_time1_ch3_duty(0);
		}
		else
		{
			//SET_PWM1_DUTY(5);
			//set_time1_ch2_duty(EarStimulusMode.Level);
			//set_time1_ch3_duty(0);
		}
	}
	else
	{
	//	set_time1_ch1_duty(0);
	//	set_time1_ch2_duty(0);
	//	set_time1_ch3_duty(0);
	}
	
}

void open_ear_pwm(void)
{
	//TIM1_CCxCmd(TIM1_CHANNEL_1, ENABLE);	
	//TIM1_CCxCmd(TIM1_CHANNEL_2, ENABLE);   
	TIM1_CCxCmd(TIM1_CHANNEL_3, ENABLE);   
	TIM1_Cmd(ENABLE);	
}

void close_ear_pwm(void)
{
	TIM1_SetCounter(0);
	//TIM1_CCxCmd(TIM1_CHANNEL_1, DISABLE);	
	//TIM1_CCxCmd(TIM1_CHANNEL_2, DISABLE);	
	TIM1_CCxCmd(TIM1_CHANNEL_3, DISABLE);	
	TIM1_Cmd(DISABLE);	
}


void EarStimulusPolling(void)
{
	EarStimulusMode.DelayTime++;
	if(EarStimulusMode.Mode == CONTINUE_WAVE_FORM)
	{
		if(EarStimulusMode.DelayTime <5)
		{
		//	TIM1_Cmd(ENABLE);	
		}
		else if(EarStimulusMode.DelayTime <6)
		{
			close_ear_pwm();
			//ANDROID_TEST_LOW;
		}
		else
		{
			EarStimulusMode.DelayTime = 0;
			open_ear_pwm();
			//ANDROID_TEST_HIGH;
		}
		
	}
	else
	{
		if(EarStimulusMode.DelayTime <3)
		{
		//	TIM1_Cmd(ENABLE);	
		}
		else if(EarStimulusMode.DelayTime <4)
		{
			close_ear_pwm();
			
			//ANDROID_TEST_LOW;
		}
		else
		{
			EarStimulusMode.DelayTime = 0;
			open_ear_pwm();
			//ANDROID_TEST_HIGH;
		}
	}

	


}


