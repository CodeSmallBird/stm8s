#include"pwm.h"

#define TIM3_PERIOD  (124)
#define TIM1_PERIOD  (2560)//1.6ms
#define TIM1_PRESCALER_128	            0x07


//pwm_duty--百分比*100
void set_time3_ch1_duty(u16 pwm_duty)
{
	u16 temp_duty = 0;
	if(pwm_duty == 0)
	{
		TIM3_CCxCmd(TIM1_CHANNEL_1, DISABLE);   
	}
	else
	{
		temp_duty = (pwm_duty*TIM3_PERIOD)/SHAKE_MAX;
		if(temp_duty >= TIM3_PERIOD)
		{
			temp_duty = TIM3_PERIOD+1;
		}
		
		TIM3-> CCR1H = (temp_duty>>8);  
		TIM3-> CCR1L = temp_duty&0xff; 
		
		TIM3_CCxCmd(TIM1_CHANNEL_1, ENABLE);   
	}
}


void timer3_pwm_init(void)
{
	TIM3_DeInit();

	TIM3->PSCR = TIM3_PRESCALER_128;
	TIM3->CCMR1 = 0X68;	//0110 1000  --pwm1模式,开启预装载功能
	/* Set the Autoreload value */
	TIM3->ARRH = (uint8_t)(TIM3_PERIOD >> 8);
	TIM3->ARRL = (uint8_t)(TIM3_PERIOD);

	//比较器的写入值
	TIM3-> CCR1H = 0;  
	TIM3-> CCR1L = 0; 
	
    TIM3->CR1 |= TIM3_CR1_ARPE;      //预装载
    TIM3->CR1 |= TIM3_CR1_CEN;      //使能  计数器  
    //TIM3->CCER1 |= TIM3_CCER1_CC1E; //使能  捕获/比较寄存器1  
   
}




//pwm_duty--百分比*100
void set_time1_ch1_duty(u16 pwm_duty)
{
	u16 temp_duty = 0;
	
	if(pwm_duty == 0)
	{
		TIM1_CCxCmd(TIM1_CHANNEL_1, DISABLE);   
	}
	else
	{
		temp_duty = 10;//(pwm_duty*TIM1_PERIOD)/STIMULUS_MAX;
		if(temp_duty >= TIM1_PERIOD)
		{
			temp_duty = TIM1_PERIOD+1;
		}
		
		TIM1-> CCR1H = (temp_duty>>8);  
		TIM1-> CCR1L = temp_duty&0xff; 
		TIM1_CCxCmd(TIM1_CHANNEL_1, ENABLE);   
	}
}


//pwm_duty--百分比*100
void set_time1_ch2_duty(u16 pwm_duty)
{
	u16 temp_duty = 0;
	
	if(pwm_duty == 0)
	{
		TIM1_CCxCmd(TIM1_CHANNEL_2, DISABLE);   
	}
	else
	{
		temp_duty = (pwm_duty*TIM1_PERIOD)/STIMULUS_MAX;
		if(temp_duty >= TIM1_PERIOD)
		{
			temp_duty = TIM1_PERIOD+1;
		}
		TIM1-> CCR2H = (temp_duty>>8);  
		TIM1-> CCR2L = temp_duty&0xff; 
		TIM1_CCxCmd(TIM1_CHANNEL_2, ENABLE);   
	}
}

//pwm_duty--百分比*100
void set_time1_ch3_duty(u16 pwm_duty)
{
	u16 temp_duty = 0;
	if(pwm_duty == 0)
	{
		TIM1_CCxCmd(TIM1_CHANNEL_3, DISABLE);   
	}
	else
	{
		temp_duty = pwm_duty;//(pwm_duty*TIM1_PERIOD)/100;//STIMULUS_MAX;
		if(temp_duty >= TIM1_PERIOD)
		{
			temp_duty = TIM1_PERIOD+1;
		}
		TIM1-> CCR3H = (temp_duty>>8);  
		TIM1-> CCR3L = temp_duty&0xff; 
		TIM1_CCxCmd(TIM1_CHANNEL_3, ENABLE);   
	}
}

void timer1_pwm_init(void)
{  

//  GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);	 //输出推拉，低电平，10MHz  
  TIM1_DeInit();   
  TIM1_TimeBaseInit(TIM1_PRESCALER_128, TIM1_COUNTERMODE_UP, TIM1_PERIOD, 0x00);//	  

#if 0  
  TIM1_OC1Init(TIM1_OCMODE_PWM1, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,
  				0x00, TIM1_OCPOLARITY_HIGH,TIM1_OCNPOLARITY_LOW, TIM1_OCIDLESTATE_RESET 
  				,TIM1_OCNIDLESTATE_RESET); 
  
  TIM1_OC2Init(TIM1_OCMODE_PWM1, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,
  				0x00, TIM1_OCPOLARITY_HIGH,TIM1_OCNPOLARITY_LOW, TIM1_OCIDLESTATE_RESET 
  				,TIM1_OCNIDLESTATE_RESET); 
#endif  
  TIM1_OC3Init(TIM1_OCMODE_PWM1, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,
  				0x00, TIM1_OCPOLARITY_LOW,TIM1_OCNPOLARITY_LOW, TIM1_OCIDLESTATE_RESET 
  				,TIM1_OCNIDLESTATE_RESET); 
#if 0
  TIM1_CCxCmd(TIM1_CHANNEL_1, DISABLE);	 
  TIM1_CCxCmd(TIM1_CHANNEL_2, DISABLE);	 
#endif
  TIM1_CCxCmd(TIM1_CHANNEL_3, DISABLE);	 
#if 0
  TIM1_OC1PreloadConfig(ENABLE);   
  TIM1_OC2PreloadConfig(ENABLE);  
#endif
  TIM1_OC3PreloadConfig(ENABLE);   

  TIM1_CtrlPWMOutputs(ENABLE);	 
  TIM1_ARRPreloadConfig(ENABLE);
  TIM1_Cmd(ENABLE);   
}  



//1ms 1个周期
void pwm_init(void)
{
	timer3_pwm_init();
	timer1_pwm_init();
}










