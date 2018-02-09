#ifndef _TYPES_H_
#define _TYPES_H_


//typedef bit									BIT;			
typedef unsigned char							U8;
typedef unsigned int							U16;
typedef unsigned long							U32;
typedef signed char							S8;
typedef signed int								S16;
typedef signed long							S32;

#if 0
//typedef unsigned char						BOOL;
typedef bit									BOOL;

typedef unsigned char							BYTE;
typedef unsigned int							WORD;
typedef unsigned long							DWORD;

typedef float									FLOAT;

#define DATA									data
#define BDATA								bdata
#define IDATA								idata
#define PDATA								pdata
#define XDATA								xdata
#define CODE								code			

#define HIGH									1
#define LOW									0

#define OPEN                                				1
#define CLOSE								0

#define TRUE									1
#define FALSE								0

#define UP									1
#define DOWN								0

#define ENABLE								1
#define DISABLE								0

#define ON									1
#define OFF									0
#endif

#define EXTERN								extern
#define CONST								const

#define __NOP								_nop_()

#ifndef NULL
	#define NULL								((void *) 0)
#endif

#define _B0_									(1<<0)
#define _B1_									(1<<1)
#define _B2_									(1<<2)
#define _B3_									(1<<3)
#define _B4_									(1<<4)
#define _B5_									(1<<5)
#define _B6_									(1<<6)
#define _B7_									(1<<7)

#define _B8_									(1<<8)
#define _B9_									(1<<9)
#define _B10_								(1<<10)
#define _B11_								(1<<11)
#define _B12_								(1<<12)
#define _B13_								(1<<13)
#define _B14_								(1<<14)
#define _B15_								(1<<15)

#define _B16_								(1<<16)
#define _B17_								(1<<17)
#define _B18_								(1<<18)
#define _B19_								(1<<19)
#define _B20_								(1<<20)
#define _B21_								(1<<21)
#define _B22_								(1<<22)
#define _B23_								(1<<23)

#define _B24_								(1<<24)
#define _B25_								(1<<25)
#define _B26_								(1<<26)
#define _B27_								(1<<27)
#define _B28_								(1<<28)
#define _B29_								(1<<29)
#define _B30_								(1<<30)
#define _B31_								(1<<31)


/*-----------------------------------------------------------------------------------------------------------*/
										
#define _u8_(x,y)  							(((U8  *)(&(x)))[y])	
#define _u16_(x,y)							(((U16 *)(&(x)))[y])	
#define _u32_(x,y)							(((U32 *)(&(x)))[y])	

#define _au8_(x,y)							(((U8  *)(x))[y])
#define _au16_(x,y)							(((U16 *)(x))[y])
#define _au32_(x,y)							(((U32 *)(x))[y])

/*-----------------------------------------------------------------------------------------------------------*/
#define _u8tou16_(x,y)						((U16)((((U16)(x))<<8) |(U16)(y)))
#define _u16tou32_(x,y)						((U32)((((U32)(x))<<16)|(U32)(y)))
#define _u8tou32_(x,y,z,k)						((U32)((((U32)(x))<<24)|(((U32)(y))<<16)|(((U32)(z))<<8)|(((U32)(k)))))

/*-----------------------------------------------------------------------------------------------------------*/

#define _u16to8h_(x)							_u8_(x,0)			
#define _u16to8l_(x)							_u8_(x,1)

#define _u32to16h_(x)						_u16_(x,0)				
#define _u32to16l_(x)							_u16_(x,1)

#define _u32to8hh_(x)						_u8_(x,0)	
#define _u32to8hl_(x)							_u8_(x,1)	
#define _u32to8lh_(x)							_u8_(x,2)				
#define _u32to8ll_(x)							_u8_(x,3)

/*-----------------------------------------------------------------------------------------------------------*/

#define _setdata_(x,y)						((x)|=(y))
#define _clrdata_(x,y)							((x)&=(~(y)))
#define _testdata_(x,y)						((x)&(y))

/*-----------------------------------------------------------------------------------------------------------*/

typedef void (*V_FUNC_V)(void);
typedef void (*V_FUNC_U)(U8);
typedef U8 (*U_FUNC_V)(void);
typedef U8 (*U_FUNC_U)(U8);




#define ie_memset    memset

		 
#endif /* _TYPES_H_ */

