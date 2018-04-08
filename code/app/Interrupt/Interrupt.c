#include "Interrupt.h"

#if defined(__DEBUG__)
	//#define __DEBUG_Interrupt
#endif

/*-----------------------------------------------------------------------------------------------*/
/*-------------------------------------------ÖÐ¶Ï´¦Àí--------------------------------------------*/
/*-----------------------------------------------------------------------------------------------*/
#define TIM4_PERIOD  (124)
//1ms
static void TIM4_Config(void)
{
  /* TIM4 configuration:
   - TIM4CLK is set to 16 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter
   clock used is 16 MHz / 128 = 125 000 Hz
  - With 125 000 Hz we can generate time base:
      max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 125000 = 2.048 ms
      min time base is 0.016 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 125000 = 0.016 ms
  - In this example we need to generate a time base equal to 1 ms
   so TIM4_PERIOD = (0.001 * 125000 - 1) = 124 */

  /* Time base configuration */
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, TIM4_PERIOD);
  /* Clear TIM4 update flag */
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  /* Enable update interrupt */
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  

  /* Enable TIM4 */
  TIM4_Cmd(ENABLE);
}


void Sys_tick_init(void)
{
	TIM4_Config();
}
//1ms
#if 1
void TimerInterrupt_SysTicke_Func(void)
{
	static u8 test = 0;
	static u8 sys_tick = 0;
	sys_tick++;

	if(EarStimulusMode.Switch == EAR_STIMULUS_ON)
	{
		EarStimulusMode.ChangeTick++;
		/*if(EarStimulusMode.ChangeTick % 5 == 0)
		{
			if(test == 0)
			{
					ANDROID_TEST_HIGH;
					test  = 1;
			}
			else
			{
				ANDROID_TEST_LOW;
				test  = 0;
			}
		}*/
		if(EarStimulusMode.ChangeTick == 1)
		{ 
			PWM2_LOW;
			PWM3_HIGH;
			ANDROID_TEST_HIGH;
			SET_PWM1_DUTY(5);
		}
		else if(EarStimulusMode.ChangeTick > 30)
		{
		
			//SET_PWM1_DUTY(0);
			PWM2_HIGH;
			ANDROID_TEST_LOW;
			if(EarStimulusMode.ChangeTick == 1001)
			{
				PWM3_LOW;
				//SET_PWM1_DUTY(5);
			}
			else if(EarStimulusMode.ChangeTick > 1030)
			{
			
				//SET_PWM1_DUTY(0);
				PWM3_HIGH;
				if(EarStimulusMode.ChangeTick > 2000)
				{
					EarStimulusMode.ChangeTick = 0;
				}
			}
		}

	}


	
	if(sys_tick<4)
		return;
	sys_tick = 0;

	Project.SysTickeCount ++;
	//	4MS
	Project.SysTickeCount4Ms ++;
	if(Project.SysTickeCount & _B0_)
	{// 8MS
		Project.SysTickeCount8Ms ++;
	}	
	else if(Project.SysTickeCount & _B1_)
	{// 16MS
		Project.SysTickeCount16Ms ++;	
	}
	else if(Project.SysTickeCount & _B2_)
	{// 32MS
		Project.SysTickeCount32Ms ++;	
	}
	else if(Project.SysTickeCount & _B3_)
	{// 64MS
		Project.SysTickeCount64Ms ++;	
	}
}

#else
void TimerInterrupt_SysTicke_Func(void)
{
static u8 test = 0;
static u8 sys_tick = 0;
	sys_tick++;

	if(EarStimulusMode.Switch == EAR_STIMULUS_ON)
	{
		EarStimulusMode.ChangeTick++;
		/*if(EarStimulusMode.ChangeTick % 5 == 0)
		{
			if(test == 0)
			{
					ANDROID_TEST_HIGH;
					test  = 1;
			}
			else
			{
				ANDROID_TEST_LOW;
				test  = 0;
			}
		}*/
		if(EarStimulusMode.ChangeTick == 1)
		{ 
		
			PWM2_LOW;
			PWM3_HIGH;
			ANDROID_TEST_HIGH;
			SET_PWM1_DUTY(5);
		}
		else if(EarStimulusMode.ChangeTick > 30)
		{
		
			//SET_PWM1_DUTY(0);
			PWM2_HIGH;
			ANDROID_TEST_LOW;
			if(EarStimulusMode.ChangeTick == 1001)
			{
				PWM3_LOW;
				//SET_PWM1_DUTY(5);
			}
			else if(EarStimulusMode.ChangeTick > 1030)
			{
			
				//SET_PWM1_DUTY(0);
				PWM3_HIGH;
				if(EarStimulusMode.ChangeTick > 2000)
				{
					EarStimulusMode.ChangeTick = 0;
				}
			}
		}

	}


	
	if(sys_tick<4)
		return;
	sys_tick = 0;

	Project.SysTickeCount ++;
	//	4MS
	Project.SysTickeCount4Ms ++;
	if(Project.SysTickeCount & _B0_)
	{// 8MS
		Project.SysTickeCount8Ms ++;
	}	
	else if(Project.SysTickeCount & _B1_)
	{// 16MS
		Project.SysTickeCount16Ms ++;	
	}
	else if(Project.SysTickeCount & _B2_)
	{// 32MS
		Project.SysTickeCount32Ms ++;	
	}
	else if(Project.SysTickeCount & _B3_)
	{// 64MS
		Project.SysTickeCount64Ms ++;	
	}
}
#endif


void InterruptPolling(void)
{
#if defined(_SUPPORT_ANDRIOD_CONNECT_)
	u8 Data = 0;
	DISABLE_INTERRUPT;

	AndriodUartInterrupt_Tx_Func();
	//if(AndroidUartPopSendByte(&Data))
	//{
	//	UART1_SendData8(Data);
	//}
	//ENABLE_INTERRUPT;

#endif
}



#ifdef __DEBUG_Interrupt
	#undef __DEBUG_Interrupt
#endif
