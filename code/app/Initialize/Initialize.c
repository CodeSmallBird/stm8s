#include "Initialize.h"

#if defined(__DEBUG__)
	#define __DEBUG_Initialize
#endif

void McuIoInit(void)
{
	PWM1_INIT;
	PWM1_HIGH;
	PWM2_INIT;
	PWM2_HIGH;
	PWM3_INIT;
	PWM2_HIGH;
	
	TEM_EN_INIT;
	TEM_EN_OFF;
	
	UART_EN_INIT;
	UART_EN_ANDROID_TO_BOARD;
	
	KEY1_INIT;
	KEY2_INIT;
	KEY3_INIT;
	KEY4_INIT;
	KEY5_INIT;
	KEY6_INIT;
	
	MOTO_EN_INIT;
	MOTO_EN_LOW;

	
	TEM_ADC_INIT_IN;
	//TEM_ADC_LOW;

	
	ANDROID_POWER_INIT;
	ANDROID_POWER_LOW;

	ANDROID_TEST_INIT;
	ANDROID_TEST_LOW;
}


void McuInit(void)
{
	CLK_DeInit();
	CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE,
					   CLK_CURRENTCLOCKSTATE_ENABLE);
	
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

	McuIoInit();

	DISABLE_INTERRUPT;

	Sys_tick_init();
	
	ENABLE_INTERRUPT;
}


void DriverInit(void)
{
	DISABLE_INTERRUPT;

	uart_init();
	pwm_init();
	
	ENABLE_INTERRUPT;
}	


void AppInit(void)
{
#if defined(_SUPPORT_ANDRIOD_CONNECT_)
	AndroidUartInit();
#endif
	KeyInit();
	EyeCureInit();
	//OpenEyeCure();
}

#if defined(GET_MCU_VERSION)

#if defined(CUT_VERSION_FA4)
CODE CONST U8 VisionTab[]=
{
	"FA1:"__PRODUCT_INFO__"\r\n"
	"FA2:"__DATE2__"\r\n"
	"FA3:"__TIME__"\r\n"
};
#else
CODE CONST U8 VisionTab[]=
{
	"FA1:"__PRODUCT_INFO__"\r\n"
	"FA2:"__DATE2__"\r\n"
	"FA3:"__TIME__"\r\n"
	"FA4:"
};

U8 NumChange(U8 Num)
{
	Num &= 0x0F;
	if (Num<10)
	{
		return Num + '0';
	}
	else
	{
		return (Num-10) + 'A';
	}
}
#endif

void GetMcuVision()
{	
	U8 Length;
	U8 TimeOver;

#if !defined(CUT_VERSION_FA4)
	U8  CODE *CodePointCheck;
	U16 SumTemp;
	U16 i;
	U8 SumBuffer[5];

	SumTemp = 0;
	CodePointCheck = 0;
	for(i = 0; i < 0x8000; i++)
	{
		SumTemp += (*CodePointCheck++);	
	}

	SumBuffer[0] = NumChange(SumTemp>>12);
	SumBuffer[1] = NumChange(SumTemp>>8);
	SumBuffer[2] = NumChange(SumTemp>>4);
	SumBuffer[3] = NumChange(SumTemp);
#endif
	VersionUartEnable();

	for(Length = 0;Length < sizeof(VisionTab); Length++)
	{
		USI0DR = VisionTab[Length];
		TimeOver = 250;
		while(!(USI0ST1 & 0x80))
		{
			if (TimeOver)
			{
				TimeOver--;
			}
			else
			{
				break;
			}
		}
	}

#if !defined(CUT_VERSION_FA4)	
	for(Length = 0;Length < sizeof(SumBuffer); Length++)
	{
		USI0DR = SumBuffer[Length];
		TimeOver = 250;
		while(!(USI0ST1 & 0x80))
		{
			if (TimeOver)
			{
				TimeOver--;
			}
			else
			{
				break;
			}
		}
	}
#endif
	VersionUartDisable();
}
#endif

void Initianize(void)
{
	McuInit();
	DriverInit();
	AppInit();
	

#if defined(__DEBUG_Initialize)
	ie_printf("/*----------------------------------*/\n");
	ie_printf("程序初始化完成!\n");
	ie_printf("设计公司:\n");
	ie_printf("设计人:luli\n");
	ie_printf("编译时间:%s,%s\n",__DATE__,__TIME__);
	ie_printf("/*----------------------------------*/\n");
#endif
}


#ifdef __DEBUG_Initialize
	#undef __DEBUG_Initialize
#endif


