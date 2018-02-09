#ifndef _USER_INIT_H_
#define _USER_INIT_H_



#define __FIRM_INFO__								"DEMO"
#define __PRODUCT_INFO__							"DEMO"
#define __PRODUCT_DEMO_DEMO__	


/*
	系统功能支持
*/
#define _SUPPORT_ANDRIOD_CONNECT_

//#define _SUPPORT_DEBUG_

/*---------------------------------------------------
	系统
---------------------------------------------------*/

#if defined (_SUPPORT_DEBUG_)
	#define DEBUG_USE_UART
	#define __DEBUG__
#endif




/*---------------------------------------------------
	引脚选择
---------------------------------------------------*/
#define PIN_MAP_NAME					V1




/*---------------------------------------------------
	特殊功能配置
---------------------------------------------------*/






#endif /* _USER_INIT_H_ */

