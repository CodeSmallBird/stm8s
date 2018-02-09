#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#if !defined(_COMMON_H_)
	#include "..\Common\Common.h"
#endif


#define DISABLE_INTERRUPT                  disableInterrupts()
#define ENABLE_INTERRUPT                   enableInterrupts()



EXTERN void TimerInterrupt_SysTicke_Func(void);
EXTERN void InterruptInit(void);
EXTERN void InterruptPolling(void);

EXTERN void Sys_tick_init(void);





#endif /* _INTERRUPT_H_ */



