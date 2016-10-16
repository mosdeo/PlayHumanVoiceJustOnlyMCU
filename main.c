//*****************Meow Alarm*****************//
//Programmer:Lin Kao-Yuan
//Date:2014/12/21
//
//For play human voice with 8-bit array,
//using built-in MCU's hardware-PWM to driving Speak,
//Don't need any peripherals out of the chip. 
//*******************************************//

#include <REG_MG82FL524-564.H>
#include <stdio.h>
#include "PWM.h"
#include "VoiceData.h"
#define TIMER0_OVERFLOW_INTERVAL (225) //	225/1843200 = 1/8192
#define TH0_NUM (65535-TIMER0_OVERFLOW_INTERVAL)
#define TL0_NUM (65535-TIMER0_OVERFLOW_INTERVAL)

void delay1ms(unsigned int x)
{
	unsigned int i,j;
	
	for(i=0;i<x;i++)
		for(j=0;j<1880;j++);
}

//七段顯示器用的解碼常數
unsigned char code SevenSegmentNum[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x83,0xF8,0x80,0x98};

char i=0;
bit AlarmFlag=0;

int main()
{
	EA=ET0=1; //啟用Timer0中斷
	
	TH0=TH0_NUM;
	TL0=TL0_NUM;
	TMOD|=0x02;// 使用Timer0 mode2
	TR0=1;//啟動Timer0

	PWM_Initial();

	P20=1;//設定P20為輸入
	
	while(1)
	{
		if(!AlarmFlag)
		{
			for(i=9;i>=0;i--)
			{
				delay1ms(1000);
				P0=SevenSegmentNum[i];//把i顯示在七段顯示器
			}
			
			AlarmFlag=1;
		}
		
		//if(P20)//如果P20被按下
		//	AlarmFlag=0;
	}
}


void Timer0_INT(void) interrupt 1
{//Auto Reload, 0.12ms 中斷一次
	static int i=0;
	
	if(AlarmFlag)
	{//如果鬧鐘要響
		PCA_Start();//啟動PCA模組
		
		if(0<=i && i<=7000)
			SetPWM_8bit(0,Voice_GetUp[i]);
		else if(7001<=i && i<=15000)
			SetPWM_8bit(0,Voice_Wow[i-7000]);
		else
		{
			//13001~18000空白
		}
		
		i++;
		if(18000<i)i=0;
	}
	else
	{//如果鬧鐘不響
		PCA_Stop();//關閉PCA模組
		i=0;//聲音播放序列歸零
	}
}