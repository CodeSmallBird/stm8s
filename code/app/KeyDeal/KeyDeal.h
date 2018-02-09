#ifndef _KEY_DEAL_H_
#define _KEY_DEAL_H_
#ifndef _COMMON_H_
	#include"Common.h"
#endif



#define INPUT_TIME_POLLING					32
#define INPUT_TIME_MAX						(5000/INPUT_TIME_POLLING)
#define INPUT_VALUE_NULL					(0x00)


#define SHORT_PRESSTIME						(200/INPUT_TIME_POLLING)		
#define LONG_PRESSTIME						(2000/INPUT_TIME_POLLING)		

enum
{
	KEY_SYSTEM_POWER,
	KEY_SYSTEM_CTRL,
	KEY_NORMAL_MODE,
	KEY_ENHANCE_MODE,
	KEY_END
};


enum
{
	KEY_UP ,
	KEY_DOWN
};

typedef struct
{
	U8	State;
	U8	Value;
	U8 	LastValue;
	U8 	NowValue;
	U8 	ValueTime;
	U8	LastTime;
	U8 	Buffer[2];
}KEY_CHECK;

extern KEY_CHECK KeyInput[4];

extern void KeyInit(void);
extern void KeyPolling(void);
extern void OrderPolling(void);


#endif

