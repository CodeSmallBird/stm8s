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
    SINGAL_DATA_LOW;       		  	//������������
    ds_delay_us(500); 	//32	  		//��ʱ495us
    SINGAL_DATA_HIGH;        		//�ͷ����ߣ�ͬʱIO�ڲ������������ܱ�DS18B20����⵽
    ds_delay_us(68);  	//4	 		//��ʱ����60us��ȷ��������DS18B20�ܷ���60~240us�Ĵ�������Ӧ��
	SINGAL_DATA_INIT_IN;
	while(ack)
	{
		ack = SINGAL_DATA_GET;    		//�ڴ�60~240us֮��DQ��DS18B20��ռ�ã������ڣ�����ᷢ��һ���͵�ƽ�źţ�DQ��DS18B20���ͣ���ackΪ0����֮Ϊ1
	}
    ds_delay_us(420);  //15			//��ʱ��240us����DS18B20�ͷ�����
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
       	SINGAL_DATA_LOW;          		//�������ߣ�����дʱ϶
		ds_delay_us(15);            //����1us����ʱ
        if(byte & 0x01)
        	SINGAL_DATA_HIGH ; 			//���ֽڵ�λд�뵥����
        ds_delay_us(50);   //3  			//��15~60us�ڵȴ�DS18B20���ɼ��ź�
        SINGAL_DATA_HIGH;    		//�ͷ�����
        byte >>= 1;       				//ÿ�ν�Ҫ��ȡ������λ�������λ��
    }
}


U8 DS18B20_read_byte(void)
{
    U8 i;
    U8 byte = 0;         //byteΪҪ���յ�������
	SINGAL_DATA_INIT_OUT;
    for(i=0 ; i<8 ; i++)
    {
        SINGAL_DATA_LOW;         //������ʱ��
        ds_delay_us(4);        	//����ʱ
        SINGAL_DATA_HIGH;       //�ͷ�����,�дӻ�DS18B20ռ��
        ds_delay_us(8); 
        byte >>= 1;     		//�Ƚ�����λ
		SINGAL_DATA_INIT_IN;
        if(SINGAL_DATA_GET)     //��DS18B20ռ�����ߣ������ɼ������ź�
            byte |= 0x80; 		//��DQ=1�����õ�ǰbyte���λΪ1�����´�ѭ������λ���θ�λ�����ﵽ�ӵ�λ����λ���յ�Ŀ�ģ���DQ=0�������������䣬ֱ�����´�ѭ����byte������λ��0�����ϲ���15us�������
        ds_delay_us(60);   //3 		//��ʱ60us
		SINGAL_DATA_INIT_OUT;
        SINGAL_DATA_HIGH;       //�ͷ�����
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
	DS18B20_write_byte(0x33);	 //����ROM��������
	a=DS18B20_read_byte();	  //�ȶ��Ͱ�λ
	return a;

}



U16 read_temper (void)
{    
   U8 a,b;         
   U16 t=0;
   if(DS18B20_init() == 1)
   	return 0;
   DS18B20_write_byte(0xcc);   //����ROM��������
   DS18B20_write_byte(0x44);     //���������¶�ת������
   DS18B20_init();       
   DS18B20_write_byte(0xcc);    //����ROM��������
   DS18B20_write_byte(0xbe);      //���Ͷ��¶ȼĴ�������
   a=DS18B20_read_byte();    //�ȶ��Ͱ�λ
   b=DS18B20_read_byte();      //�ٶ��߰�λ
   t=b;        
   t<<=8;      //���ư�λ
   t=t|a;      //tΪ16λ������ʹ�߰�λΪb��ֵ���Ͱ�λΪa��ֵ  
   return t;    //�����¶�ֵ
}


S16 temper_change(void)
{
    S16 temper;
    float tp;
	//DISABLE_INTERRUPT;
    temper=read_temper();
	//ENABLE_INTERRUPT;
    if(temper&0xf000)    //���Ǹ��¶ȵ����
    {
        temper=temper-1;
        temper=~temper;
        tp=temper*0.0625;  //16λ�¶�ת����10���Ƶ��¶�
        temper=tp*100+0.5;   //������С���㣬����������
    }
    else
    {
        tp=temper*0.0625;  //16λ�¶�ת����10���Ƶ��¶�
        temper=tp*100+0.5;  //������С���㣬����������
    }
    return temper;
}



