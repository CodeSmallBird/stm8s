#ifndef _MAIN_H_
#define _MAIN_H_

#ifndef _COMMON_H_
	#include "..\Common\Common.h"
#endif

//#define _DEBUG_
typedef struct{
	U8 SysTickeCount;
	U8 SysTickeCount4Ms;
	U8 SysTickeCount8Ms;
	U8 SysTickeCount16Ms;
	U8 SysTickeCount32Ms;
	U8 SysTickeCount64Ms;
}PROJECT;


EXTERN PROJECT Project;


#endif /* _MAIN_H_ */
