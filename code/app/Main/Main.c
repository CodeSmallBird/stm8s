#include "Main.h"

#if defined(__DEBUG__)
	#define __DEBUG_Main
#endif

PROJECT Project;


void TimerPolling_4Ms(void)
{
	if(Project.SysTickeCount4Ms)
		Project.SysTickeCount4Ms--;
	else
		return;
}

void TimerPolling_8Ms(void)
{
	if(Project.SysTickeCount8Ms)
		Project.SysTickeCount8Ms--;
	else
		return;
	InterruptPolling();
#if defined(_SUPPORT_ANDRIOD_CONNECT_)
	AndriodPolling();
#endif
}

void TimerPolling_16Ms(void)
{
	if(Project.SysTickeCount16Ms)
		Project.SysTickeCount16Ms--;
	else
		return;
	KeyPolling();
}

void TimerPolling_32Ms(void)
{
	if(Project.SysTickeCount32Ms)
		Project.SysTickeCount32Ms--;
	else
		return;


	
}

void TimerPolling_64Ms(void)
{
	if(Project.SysTickeCount64Ms)
		Project.SysTickeCount64Ms--;
	else
		return;

#if defined(__DEBUG_Main)
	{
		//unsigned int	 temper = 0;
		static u8 tick=0;
		tick++;
		if(tick>16)
		{
			tick = 0;
		//	set_time1_ch1_duty(EarStimulusMode.Level);
		//	set_time1_ch2_duty(EarStimulusMode.Level);
		//	set_time1_ch3_duty(EarStimulusMode.Level);
		}	
		
	}
#endif
	EyeCurePolling();
}

void main(void)
{
	Initianize();
	while(1)
	{
		while(TRUE)
		{
			TimerPolling_4Ms();
			TimerPolling_8Ms();
			TimerPolling_16Ms();
			TimerPolling_32Ms();
			TimerPolling_64Ms();
		}			
	}	
}

#ifdef __DEBUG_Main
	#undef __DEBUG_Main
#endif



