#ifndef _APP_EYE_CURE_H_
#define _APP_EYE_CURE_H_

#ifndef _COMMON_H_
	#include"Common.h"
#endif


#include"..\EyeShake\EyeShake.h"
#include"..\EyeHeat\EyeHeat.h"
#include"..\EarStimulus\EarStimulus.h"

#define EYE_CURE_POLL_TIME              64

enum
{
	POWER_OFF,
	POWER_ON
};

enum
{
	SYS_RUN_OFF,
	SYS_RUN_ON
};


enum
{
	NULL_WAVE_FORM,
	CONTINUE_WAVE_FORM,
	BREAK_WAVE_FORM
};


enum
{
	EYE_CURE_FACTORY_MODE,
	EYE_CURE_NORMAL_MODE,
	EYE_CURE_ENHANCE_MODE,
	EYE_CURE_CUSTOMER_MODE
};


typedef struct
{
	s8 Temperature;
	u8 ShakeRange;
	u8 PlusRange;
	u8 WaveformMode;
}EYE_CURE_PARAM;

typedef struct
{
	u8 SysPowerFlag;
	u8 SysRunFlag;
	u8 SysWorkMode;
	EYE_CURE_PARAM  EyeCureParam;
}EYE_CURE_INFOR;

EXTERN EYE_CURE_INFOR     EyeCure;



#define SET_SYS_POWER_ON 	do{     	EyeCure.SysPowerFlag = POWER_ON;\
										ANDROID_POWER_ON;}while(0)
#define SET_SYS_POWER_OFF 	do{     	EyeCure.SysPowerFlag = POWER_OFF;\
										ANDROID_POWER_OFF;}while(0)
#define GET_SYS_POWER_STATE	    	     EyeCure.SysPowerFlag

#define SET_SYS_RUN_FLAG(X) 	do{     	EyeCure.SysRunFlag = X;}while(0)
#define GET_SYS_RUN_FLAG               EyeCure.SysRunFlag


#define SET_SYS_WORK_MODE(X) 	do{     	EyeCure.SysWorkMode = X;}while(0)
#define GET_SYS_WORK_MODE  				EyeCure.SysWorkMode 


#define SET_TEMPER_PARA(X)           	do{EyeCure.EyeCureParam.Temperature = X;}while(0)
#define GET_TEMPER_PARA  				EyeCure.EyeCureParam.Temperature 

#define SET_PLUS_RANGE_PARA(X)           	do{EyeCure.EyeCureParam.PlusRange = X;}while(0)
#define GET_PLUS_RANGE_PARA  				EyeCure.EyeCureParam.PlusRange 

#define SET_SHAKE_RANGE_PARA(X)           	do{EyeCure.EyeCureParam.ShakeRange = X;}while(0)
#define GET_SHAKE_RANGE_PARA  				EyeCure.EyeCureParam.ShakeRange 

#define SET_WAVE_FOEM_PARA(X)           	do{EyeCure.EyeCureParam.WaveformMode = X;}while(0)
#define GET_WAVE_FOEM_PARA  				EyeCure.EyeCureParam.WaveformMode 


extern void EyeCureModeSet(u8 CureMode);
extern void OpenEyeCure(void);
extern void CloseEyeCure(void);
extern void EyeCurePolling(void);
extern void EyeCureInit(void);
#endif

