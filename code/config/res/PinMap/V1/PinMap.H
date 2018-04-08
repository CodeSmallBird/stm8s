#ifndef _PIN_MAP_H_
#define _PIN_MAP_H_

#include "stm8s_gpio.h"

/*-----------------------------------------------------------------------------
PWM1_PIN ---PC3--28
------------------------------------------------------------------------------*/
#define PWM1_PIN				_B3_
//推挽输出，10MHZ
#define PWM1_INIT				do{GPIOC->DDR |= PWM1_PIN;\
									GPIOC->CR1 |= PWM1_PIN;\
									GPIOC->CR2 |= PWM1_PIN;\
									}\
									while(0)	
										
#define PWM1_HIGH				(GPIOC->ODR |= PWM1_PIN)
#define PWM1_LOW				(GPIOC->ODR &= ~PWM1_PIN)


/*-----------------------------------------------------------------------------
PWM2_PIN ---PC2--27
------------------------------------------------------------------------------*/
#define PWM2_PIN				_B2_
//推挽输出，10MHZ
#define PWM2_INIT				do{GPIOC->DDR |= PWM2_PIN;\
									GPIOC->CR1 |= PWM2_PIN;\
									GPIOC->CR2 |= PWM2_PIN;\
									}\
									while(0)	
										
#define PWM2_HIGH				(GPIOC->ODR |= PWM2_PIN)
#define PWM2_LOW				(GPIOC->ODR &= ~PWM2_PIN)


/*-----------------------------------------------------------------------------
PWM3_PIN ---PC1--26
------------------------------------------------------------------------------*/
#define PWM3_PIN				_B1_
//推挽输出，10MHZ
#define PWM3_INIT				do{GPIOC->DDR |= PWM3_PIN;\
									GPIOC->CR1 |= PWM3_PIN;\
									GPIOC->CR2 |= PWM3_PIN;\
									}\
									while(0)	
										
#define PWM3_HIGH				(GPIOC->ODR |= PWM3_PIN)
#define PWM3_LOW				(GPIOC->ODR &= ~PWM3_PIN)



/*-----------------------------------------------------------------------------
TEM_EN_PIN ---PC4--29
------------------------------------------------------------------------------*/
#define TEM_EN_PIN				_B4_
//推挽输出，10MHZ
#define TEM_EN_INIT				do{GPIOC->DDR |= TEM_EN_PIN;\
									GPIOC->CR1 |= TEM_EN_PIN;\
									GPIOC->CR2 |= TEM_EN_PIN;\
									}\
									while(0)	
										
#define TEM_EN_HIGH				(GPIOC->ODR |= TEM_EN_PIN)
#define TEM_EN_LOW				(GPIOC->ODR &= ~TEM_EN_PIN)

#define TEM_EN_ON			TEM_EN_HIGH
#define TEM_EN_OFF          TEM_EN_LOW

/*-----------------------------------------------------------------------------
UART_EN_PIN ---PC7--34
------------------------------------------------------------------------------*/
#define UART_EN_PIN				_B7_
//推挽输出，10MHZ
#define UART_EN_INIT			do{GPIOC->DDR |= UART_EN_PIN;\
									GPIOC->CR1 |= UART_EN_PIN;\
									GPIOC->CR2 |= UART_EN_PIN;\
									}\
									while(0)	
										
#define UART_EN_HIGH				(GPIOC->ODR |= UART_EN_PIN)
#define UART_EN_LOW					(GPIOC->ODR &= ~UART_EN_PIN)

#define UART_EN_BOARD_TO_ANDROID					UART_EN_LOW
#define UART_EN_ANDROID_TO_BOARD					UART_EN_HIGH


/*-----------------------------------------------------------------------------
KEY1_PIN ---PE0--40
------------------------------------------------------------------------------*/
#define KEY1_PIN				_B0_
#define KEY1_INIT				do{GPIOE->DDR &= ~KEY1_PIN;\
									GPIOE->CR1 &= ~KEY1_PIN;\
									GPIOE->CR2 &= ~KEY1_PIN;\
									}\
									while(0)	
										
#define KEY1_INPUT				((GPIOE->IDR&KEY1_PIN)?0:1)	

/*-----------------------------------------------------------------------------
KEY2_PIN ---PE1--39
------------------------------------------------------------------------------*/
#define KEY2_PIN				_B1_
#define KEY2_INIT				do{GPIOE->DDR &= ~KEY2_PIN;\
									GPIOE->CR1 &= ~ KEY2_PIN;\
									GPIOE->CR2 &= ~KEY2_PIN;\
									}\
									while(0)	
										
#define KEY2_INPUT				((GPIOE->IDR&KEY2_PIN)?0:1)	

/*-----------------------------------------------------------------------------
KEY3_PIN ---PE2--38
------------------------------------------------------------------------------*/
#define KEY3_PIN				_B2_
#define KEY3_INIT				do{GPIOE->DDR &= ~KEY3_PIN;\
									GPIOE->CR1 &= ~ KEY3_PIN;\
									GPIOE->CR2 &= ~KEY3_PIN;\
									}\
									while(0)	
										
#define KEY3_INPUT				((GPIOE->IDR&KEY3_PIN)?0:1)	

/*-----------------------------------------------------------------------------
KEY4_PIN ---PE3--37
------------------------------------------------------------------------------*/
#define KEY4_PIN				_B3_
#define KEY4_INIT				do{GPIOE->DDR &= ~KEY4_PIN;\
									GPIOE->CR1 &= ~ KEY4_PIN;\
									GPIOE->CR2 &= ~KEY4_PIN;\
									}\
									while(0)	
										
#define KEY4_INPUT				((GPIOE->IDR&KEY4_PIN)?0:1)	

/*-----------------------------------------------------------------------------
KEY5_PIN ---PE5--25
------------------------------------------------------------------------------*/
#define KEY5_PIN				_B5_
#define KEY5_INIT				do{GPIOE->DDR &= ~KEY5_PIN;\
									GPIOE->CR1 |= KEY5_PIN;\
									GPIOE->CR2 &= ~KEY5_PIN;\
									}\
									while(0)	
										
#define KEY5_INPUT				((GPIOE->IDR&KEY5_PIN)?0:1)	

/*-----------------------------------------------------------------------------
KEY6_PIN ---PE6--24
------------------------------------------------------------------------------*/
#define KEY6_PIN				_B6_
#define KEY6_INIT				do{GPIOE->DDR &= ~KEY6_PIN;\
									GPIOE->CR1 |= KEY6_PIN;\
									GPIOE->CR2 &= ~KEY6_PIN;\
									}\
									while(0)	
										
#define KEY6_INPUT				((GPIOE->IDR&KEY6_PIN)?0:1)	




/*-----------------------------------------------------------------------------
MOTO_EN_PIN ---PD2--43
------------------------------------------------------------------------------*/
#define MOTO_EN_PIN					_B2_
//推挽输出，10MHZ
#define MOTO_EN_INIT				do{GPIOD->DDR |= MOTO_EN_PIN;\
									GPIOD->CR1 |= MOTO_EN_PIN;\
									GPIOD->CR2 |= MOTO_EN_PIN;\
									}\
									while(0)	
										
#define MOTO_EN_HIGH				(GPIOD->ODR |= MOTO_EN_PIN)
#define MOTO_EN_LOW					(GPIOD->ODR &= ~MOTO_EN_PIN)


/*-----------------------------------------------------------------------------
TEM_ADC_PIN ---PD3--44
------------------------------------------------------------------------------*/
#define TEM_ADC_PIN					_B3_
//推挽输出，10MHZ
#define TEM_ADC_INIT_OUT			do{GPIOD->DDR |= TEM_ADC_PIN;\
									GPIOD->CR1 |= TEM_ADC_PIN;\
									GPIOD->CR2 |= TEM_ADC_PIN;\
									}\
									while(0)	

#define TEM_ADC_INIT_IN			   do{GPIOD->DDR &= ~TEM_ADC_PIN;\
									GPIOD->CR1 &= ~TEM_ADC_PIN;\
									GPIOD->CR2 &= ~TEM_ADC_PIN;\
									}\
									while(0)	
									
										
#define TEM_ADC_HIGH				(GPIOD->ODR |= TEM_ADC_PIN)
#define TEM_ADC_LOW					(GPIOD->ODR &= ~TEM_ADC_PIN)

#define TEM_ADC_GET					((GPIOD->IDR&TEM_ADC_PIN)?1:0)	


/*-----------------------------------------------------------------------------
SYS_POWER_PIN ---PD4--21
------------------------------------------------------------------------------*/
#define ANDROID_POWER_PIN				_B0_ //_B4_ --暂时用D0替代
//推挽输出，10MHZ
#define ANDROID_POWER_INIT				do{GPIOD->DDR |= ANDROID_POWER_PIN;\
										GPIOD->CR1 |= ANDROID_POWER_PIN;\
										GPIOD->CR2 |= ANDROID_POWER_PIN;\
										}\
										while(0)	
										
#define ANDROID_POWER_HIGH				(GPIOD->ODR |= ANDROID_POWER_PIN)
#define ANDROID_POWER_LOW				(GPIOD->ODR &= ~ANDROID_POWER_PIN)

#define  ANDROID_POWER_ON				ANDROID_POWER_HIGH
#define  ANDROID_POWER_OFF				ANDROID_POWER_LOW


/*-----------------------------------------------------------------------------
SYS_TEST_PIN ---PD4--21
------------------------------------------------------------------------------*/
#define ANDROID_TEST_PIN				_B4_
//推挽输出，10MHZ
#define ANDROID_TEST_INIT				do{GPIOD->DDR |= ANDROID_TEST_PIN;\
										GPIOD->CR1 |= ANDROID_TEST_PIN;\
										GPIOD->CR2 |= ANDROID_TEST_PIN;\
										}\
										while(0)	
										
#define ANDROID_TEST_HIGH				(GPIOD->ODR |= ANDROID_TEST_PIN)
#define ANDROID_TEST_LOW				(GPIOD->ODR &= ~ANDROID_TEST_PIN)

#define  ANDROID_TEST_ON				ANDROID_TEST_HIGH
#define  ANDROID_TEST_OFF				ANDROID_TEST_LOW



#endif /* _PIN_MAP_H_ */


