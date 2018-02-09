#ifndef _EYE_SHAKE_H_
#define _EYE_SHAKE_H_
#ifndef _COMMON_H_
	#include"Common.h"
#endif

#define SHAKE_MAX			180

enum
{
	EYE_SHAKE_OFF,
	EYE_SHAKE_ON
};


typedef struct
{
	U8 Switch;		//开关
	U16 Level;		//输入等级

}EYE_SHAKE_INFOR;

EXTERN EYE_SHAKE_INFOR    EyeShakeMode;
EXTERN void AppEyeShakeInit(void);

EXTERN void SetEyeShakeMode(U8 Switch,U8 Param);



#endif

