#include"ds18b20.h"

#define SINGAL_DATA_INIT_OUT			TEM_ADC_INIT_OUT		
#define SINGAL_DATA_INIT_IN			    TEM_ADC_INIT_IN		
#define SINGAL_DATA_HIGH				TEM_ADC_HIGH		
#define SINGAL_DATA_LOW					TEM_ADC_LOW			
#define SINGAL_DATA_GET					TEM_ADC_GET		


void ds_delay_us(U16 z)
{
	u8 i;
    for(z; z>0; z--)
    {
        nop();   
		nop();
		nop();
    }   
}


U8 DS18B20_init(void)
{
    U8 ack = 1;
	SINGAL_DATA_INIT_OUT;
    SINGAL_DATA_LOW;       		  	//主机拉低总线
    ds_delay_us(500); 	//32	  		//延时495us
    SINGAL_DATA_HIGH;        		//释放总线，同时IO口产生的上升沿能被DS18B20所检测到
    ds_delay_us(68);  	//4	 		//延时大于60us，确保接下来DS18B20能发出60~240us的存在脉冲应答
	SINGAL_DATA_INIT_IN;
	while(ack)
	{
		ack = SINGAL_DATA_GET;    		//在此60~240us之内DQ被DS18B20所占用，若存在，则其会发送一个低电平信号，DQ被DS18B20拉低，则ack为0，反之为1
	}
    ds_delay_us(420);  //15			//延时达240us，让DS18B20释放总线
	SINGAL_DATA_INIT_OUT;
	SINGAL_DATA_HIGH;        
    return(ack);
}



void DS18B20_write_byte(U8 byte)
{
    U8 i;
	SINGAL_DATA_INIT_OUT;
    for(i=0 ; i<8 ; i++)
    {
       	SINGAL_DATA_LOW;          		//拉低总线，产生写时隙
		ds_delay_us(15);            //大于1us的延时
        if(byte & 0x01)
        	SINGAL_DATA_HIGH ; 			//将字节低位写入单总线
        ds_delay_us(50);   //3  			//在15~60us内等待DS18B20来采集信号
        SINGAL_DATA_HIGH;    		//释放总线
        byte >>= 1;       				//每次讲要读取的数据位移至最低位，
    }
}


U8 DS18B20_read_byte(void)
{
    U8 i;
    U8 byte = 0;         //byte为要接收到的数据
	SINGAL_DATA_INIT_OUT;
    for(i=0 ; i<8 ; i++)
    {
        SINGAL_DATA_LOW;         //产生读时序
        ds_delay_us(4);        	//简单延时
        SINGAL_DATA_HIGH;       //释放总线,有从机DS18B20占用
        ds_delay_us(8); 
        byte >>= 1;     		//先进行移位
		SINGAL_DATA_INIT_IN;
        if(SINGAL_DATA_GET)     //让DS18B20占用总线，发出采集到的信号
            byte |= 0x80; 		//若DQ=1，则让当前byte最高位为1，在下次循环中移位至次高位，最后达到从低位到高位接收的目的；若DQ=0，则可跳过此语句，直接在下次循环对byte进行移位补0。以上操作15us以内完成
        ds_delay_us(60);   //3 		//延时60us
		SINGAL_DATA_INIT_OUT;
        SINGAL_DATA_HIGH;       //释放总线
        nop(); 
		nop(); 
    }
	return byte;
}

U8 rev_temper(void)
{
	U8 a = 0;

	if(DS18B20_init() == 1)
	 return 0;
	DS18B20_write_byte(0x33);	 //跳过ROM操作命令
	a=DS18B20_read_byte();	  //先读低八位
	return a;

}



U16 read_temper (void)
{    
   U8 a,b;         
   U16 t=0;
   if(DS18B20_init() == 1)
   	return 0;
   DS18B20_write_byte(0xcc);   //跳过ROM操作命令
   DS18B20_write_byte(0x44);     //发送启动温度转换命令
   DS18B20_init();       
   DS18B20_write_byte(0xcc);    //跳过ROM操作命令
   DS18B20_write_byte(0xbe);      //发送读温度寄存器命令
   a=DS18B20_read_byte();    //先读低八位
   b=DS18B20_read_byte();      //再读高八位
   t=b;        
   t<<=8;      //左移八位
   t=t|a;      //t为16位的数，使高八位为b的值，低八位为a的值  
   return t;    //返回温度值
}


S16 temper_change(void)
{
    S16 temper;
    float tp;
	//DISABLE_INTERRUPT;
    temper=read_temper();
	//ENABLE_INTERRUPT;
    if(temper&0xf000)    //考虑负温度的情况
    {
        temper=temper-1;
        temper=~temper;
        tp=temper*0.0625;  //16位温度转换成10进制的温度
        temper=tp*100+0.5;   //留两个小数点，并四舍五入
    }
    else
    {
        tp=temper*0.0625;  //16位温度转换成10进制的温度
        temper=tp*100+0.5;  //留两个小数点，并四舍五入
    }
    return temper;
}



