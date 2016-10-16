// ************************************
// 針對MG82FE(L)564硬體PWM模組所寫的HAL
// 作者:林高遠(Lin Kao-Yuan)
// 日期:2014/12/19
// ************************************

#include "BIT.h"

void PWM_Initial(void)
{
	//***Step1:選擇要使用PCA功能的腳位, 不用的comment掉***//
	P1M0&=~BIT[2],P1M1|=BIT[2]; //P12, Set 01
	P1M0&=~BIT[3],P1M1|=BIT[3]; //P13, Set 01
	P1M0&=~BIT[4],P1M1|=BIT[4]; //P14, Set 01
	P1M0&=~BIT[5],P1M1|=BIT[5]; //P15, Set 01
	P1M0&=~BIT[6],P1M1|=BIT[6]; //P16, Set 01
	P1M0&=~BIT[7],P1M1|=BIT[7]; //P17, Set 01
	
	//***Step2: 選擇PCA時脈來源, 不用的comment掉***///
	//CMOD|=0x00; //系統頻率/12
	CMOD|=0x02; //系統頻率/2
	//CMOD|=0x04; //Timer 0 overflow
	//CMOD|=0x06; //外部輸入(P11)
	
	//***Step3: 選擇要反向輸出的腳位, 不用的comment掉***//
	//PCAPWM0|=0x04; //Set PWM0 Invert out
	//PCAPWM1|=0x04; //Set PWM1 Invert out
	//PCAPWM2|=0x04; //Set PWM2 Invert out
	//PCAPWM3|=0x04; //Set PWM3 Invert out
	//PCAPWM4|=0x04; //Set PWM4 Invert out
	//PCAPWM5|=0x04; //Set PWM5 Invert out
	
	//***Step4: 設定PWM duty cycle, 不用的comment掉***//
	//CCAP0H=(~0x00)&0xFF; //Auto Load to CCAPnL
	//CCAP1H=(~0x00)&0xFF; //Auto Load to CCAPnL
	//CCAP2H=(~0x00)&0xFF; //Auto Load to CCAPnL
	//CCAP3H=(~0x00)&0xFF; //Auto Load to CCAPnL
	//CCAP4H=(~0x00)&0xFF; //Auto Load to CCAPnL
	//CCAP5H=(~0x00)&0xFF; //Auto Load to CCAPnL
	
	
	CCAPM0=CCAPM1=CCAPM2=CCAPM3=CCAPM4=CCAPM5=0x42; //table 14.4建議為0x42, why?
}

void PCA_Start(void)
{
	CR=1;//啟動PCA
}

void PCA_Stop(void)
{
	CR=0;//停止PCA
}

void SetPWM_8bit(unsigned char Channel,unsigned char u)
{
	switch(Channel)
	{
		case 0:
			if(u>0){PCAPWM0 = 0x00;CCAP0H  = 0x100-u;}
			else if(0==u){PCAPWM0=0x03,CCAP0H=0x00;}
			break;
		case 1:
			if(u>0){PCAPWM1 = 0x00;CCAP1H  = 0x100-u;}
			else if(0==u){PCAPWM1=0x03,CCAP1H=0x00;}
			break;
		case 2:
			if(u>0){PCAPWM2 = 0x00;CCAP2H  = 0x100-u;}
			else if(0==u){PCAPWM2=0x03,CCAP2H=0x00;}
			break;
		case 3:
			if(u>0){PCAPWM3 = 0x00;CCAP3H  = 0x100-u;}
			else if(0==u){PCAPWM3=0x03,CCAP3H=0x00;}
			break;
		case 4:
			if(u>0){PCAPWM4 = 0x00;CCAP4H  = 0x100-u;}
			else if(0==u){PCAPWM4=0x03,CCAP4H=0x00;}
			break;
		case 5:
			if(u>0){PCAPWM5 = 0x00;CCAP5H  = 0x100-u;}
			else if(0==u){PCAPWM5=0x03,CCAP5H=0x00;}
			break;
		}
}