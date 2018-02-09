#ifndef _PWM_H_
#define _PWM_H_
#if !defined(_COMMON_H_)
	#include "..\Common\Common.h"
#endif

#define SET_PWM1_DUTY(x)              set_time1_ch3_duty(x)
#define SET_PWM2_DUTY(x)              set_time1_ch2_duty(x)
#define SET_PWM3_DUTY(x)              set_time1_ch1_duty(x)


EXTERN void set_time3_ch1_duty(u16 pwm_duty);
EXTERN void set_time1_ch1_duty(u16 pwm_duty);
EXTERN void set_time1_ch2_duty(u16 pwm_duty);
EXTERN void set_time1_ch3_duty(u16 pwm_duty);
EXTERN void pwm_init(void);
#endif

