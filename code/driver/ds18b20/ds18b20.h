#ifndef _DS18B20_H_
#define _DS18B20_H_

#ifndef _COMMON_H_
	#include"Common.h"
#endif

extern S16 temper_change(void);

extern void ds_delay_us(U16 z);

extern U16 read_temper (void);



#endif

