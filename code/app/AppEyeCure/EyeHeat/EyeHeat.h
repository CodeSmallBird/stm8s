#ifndef _EYE_HEAT_H_
#define _EYE_HEAT_H_
#ifndef _COMMON_H_
	#include"Common.h"
#endif

enum
{
	EYE_HEAT_OFF,
	EYE_HEAT_ON
};


typedef struct
{
	U8 Switch;		//开关
	S16 TragetTemper;		//目标温度
	S16 ActureTemper;		//实际温度
	U16 polltime;

}EYE_HEAT_INFOR;

#define GET_HEAT_DETEC_POOLING_TIME				     EyeHeatMode.polltime
#define SET_HEAT_DETEC_POOLING_TIME(x)			(GET_HEAT_DETEC_POOLING_TIME = (x)/EYE_CURE_POLL_TIME)


#define SET_REAL_TEMPER(X)   (        EyeHeatMode.ActureTemper = X)  
#define GET_REAL_TEMPER				EyeHeatMode.ActureTemper

#define SET_TRAGET_TEMPER(X)   (        EyeHeatMode.TragetTemper = X)  
#define GET_TRAGET_TEMPER				EyeHeatMode.TragetTemper


EXTERN EYE_HEAT_INFOR    EyeHeatMode;
EXTERN void AppEyeHeatInit(void);
EXTERN void SetEyeHeatMode(U8 Switch,U8 Param);
EXTERN void TemperCtrlPolling(void);

EXTERN U8 rev_temper(void);



#endif

