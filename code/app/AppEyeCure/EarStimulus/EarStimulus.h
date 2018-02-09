#ifndef _EAR_STIMULUS_H_
#define _EAR_STIMULUS_H_
#ifndef _COMMON_H_
	#include"Common.h"
#endif

#define  STIMULUS_MAX          160

enum
{
	EAR_STIMULUS_OFF,
	EAR_STIMULUS_ON
};


typedef struct
{
	U8 Switch;		//开关
	U8 Mode;
	U16 DelayTime;
	U16 Level;		//输入等级
	U16 ChangeTick;
}EAR_STIMULUS_INFOR;

EXTERN EAR_STIMULUS_INFOR    EarStimulusMode;
EXTERN void AppEarStimulusInit(void);
EXTERN void SetEarStimulusMode(U8 Switch,U8 *Param);
EXTERN void EarStimulusPolling(void);


#endif

