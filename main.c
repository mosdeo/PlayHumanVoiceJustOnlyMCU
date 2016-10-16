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

//�C�q��ܾ��Ϊ��ѽX�`��
unsigned char code SevenSegmentNum[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x83,0xF8,0x80,0x98};

char i=0;
bit AlarmFlag=0;

int main()
{
	EA=ET0=1; //�ҥ�Timer0���_
	
	TH0=TH0_NUM;
	TL0=TL0_NUM;
	TMOD|=0x02;// �ϥ�Timer0 mode2
	TR0=1;//�Ұ�Timer0

	PWM_Initial();

	P20=1;//�]�wP20����J
	
	while(1)
	{
		if(!AlarmFlag)
		{
			for(i=9;i>=0;i--)
			{
				delay1ms(1000);
				P0=SevenSegmentNum[i];//��i��ܦb�C�q��ܾ�
			}
			
			AlarmFlag=1;
		}
		
		//if(P20)//�p�GP20�Q���U
		//	AlarmFlag=0;
	}
}


void Timer0_INT(void) interrupt 1
{//Auto Reload, 0.12ms ���_�@��
	static int i=0;
	
	if(AlarmFlag)
	{//�p�G�x���n�T
		PCA_Start();//�Ұ�PCA�Ҳ�
		
		if(0<=i && i<=7000)
			SetPWM_8bit(0,Voice_GetUp[i]);
		else if(7001<=i && i<=15000)
			SetPWM_8bit(0,Voice_Wow[i-7000]);
		else
		{
			//13001~18000�ť�
		}
		
		i++;
		if(18000<i)i=0;
	}
	else
	{//�p�G�x�����T
		PCA_Stop();//����PCA�Ҳ�
		i=0;//�n������ǦC�k�s
	}
}