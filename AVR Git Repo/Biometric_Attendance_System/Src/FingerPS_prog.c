/*
 * FingerPS_prog.c
 *
 *  Created on: Nov 4, 2023
 *      Author: Ebram Habib
 */

#include "std_types.h"
#include "FingerPS_config.h"
#include "FingerPS_int.h"
#include "FingerPS_priv.h"
#include "UART_int.h"
#include "TIMER0_int.h"


TIMER0_INIT_CONFIG config = {
		TIMER0_COMPARE_OUTPUT_NON_PWM_MODE_OC0_DISCONNECTED,
		TIMER0_COMPARE_OUTPUT_FAST_PWM_MODE_OC0_CLEAR,
		TIMER0_COMPARE_OUTPUT_PHASE_CORRECT_PWM_MODE_OC0_DISCONNECTED,
		TIMER0_FCPU_DIVIDED_BY_1024,
		TIMER0_NORMAL_MODE,
		0,
		0 };

u8 flag=0;
u8 ACK[50]={0};
u8 ACKCounter = 0;
u8 UsersCounter = 1;

u8 FingerPS_handShake(void)
{
	u8 i,ACKFRAMESIZE=12;

	/*							start		add
	/* Handshake Package Format  (EF 01) (FF FF FF FF) 01 00 03 40 00 44 */
	u8 HandShake[]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x40,0x00,0x44};

	for(i=0;i<sizeof(HandShake);i++)
	{
		UART_sendByte(HandShake[i]);
	}
	UART_receiveByteAsynchCallBack(getByte);

	delayMilliSec(5);

	if(ACKCounter == ACKFRAMESIZE)
	{
		if((ACK[ACKFRAMESIZE-2] == 0x00) && (ACK[ACKFRAMESIZE-1] == 0x0A))
		{
			if(ACK[ACKFRAMESIZE-3] == 0x00)
			{
				return SUCCESS;
			}
		}
	}
	return ERROR;
}

void FingerPS_init(void)
{
	UART_init();
}
u8 FingerPS_genImg(void)
{
	u8 i,ACKFRAMESIZE=12;
	u8 GenImg[]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x01,0x00,0x05};

	FingerPS_AuraNormal();
	delayMilliSec(2000);

	for(i=0;i<sizeof(GenImg);i++)
	{
		UART_sendByte(GenImg[i]);
	}
	UART_receiveByteAsynchCallBack(getByte);

	delayMilliSec(5);

	if(ACKCounter == ACKFRAMESIZE)
	{
		if((ACK[ACKFRAMESIZE-2] == 0x00) && (ACK[ACKFRAMESIZE-1] == 0x0A))
		{
			if(ACK[ACKFRAMESIZE-3] == 0x00)
			{
				FingerPS_AuraSuccess();
				return SUCCESS;
			}
		}
	}
	FingerPS_AuraError();
	return ERROR;

}
u8 FingerPS_convertImg2CharFile(u8 buffID)
{
	u8 i,ACKFRAMESIZE=12;

	u8 Img2Tz []={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x04,0x02,0x00,0x00,0x08};

	/* insert the number of the chosen character file inside the frame */
	Img2Tz[sizeof(Img2Tz)-3] = buffID;

	for(i=0;i<sizeof(Img2Tz);i++)
	{
		UART_sendByte(Img2Tz[i]);
	}
	UART_receiveByteAsynchCallBack(getByte);

	delayMilliSec(5);

	if(ACKCounter == ACKFRAMESIZE)
	{
		if((ACK[ACKFRAMESIZE-2] == 0x00) && (ACK[ACKFRAMESIZE-1] == 0x0A))
		{
			if(ACK[ACKFRAMESIZE-3] == 0x00)
			{

				return SUCCESS;
			}
		}
	}
	return ERROR;
}
u8 FingerPS_genTemplate(void)
{
	u8 i,ACKFRAMESIZE=12;

	u8 RegModel[]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x05,0x00,0x09};

	for(i=0;i<sizeof(RegModel);i++)
	{
		UART_sendByte(RegModel[i]);
	}
	UART_receiveByteAsynchCallBack(getByte);

	delayMilliSec(5);

	if(ACKCounter == ACKFRAMESIZE)
	{
		if((ACK[ACKFRAMESIZE-2] == 0x00) && (ACK[ACKFRAMESIZE-1] == 0x0A))
		{
			if(ACK[ACKFRAMESIZE-3] == 0x00)
			{

				return SUCCESS;
			}
		}
	}
	return ERROR;
}
u8 FingerPS_strTemplate(u8 ID)
{

	u8 i,ACKFRAMESIZE=12;

	u8 Store[]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x06,0x06,0x01,0x00,0x01,0x00,0x0F};

	Store[sizeof(Store)-3] = ID;

	for(i=0;i<sizeof(Store);i++)
	{
		UART_sendByte(Store[i]);
	}
	UART_receiveByteAsynchCallBack(getByte);

	delayMilliSec(5);

	if(ACKCounter == ACKFRAMESIZE)
	{
		if((ACK[ACKFRAMESIZE-2] == 0x00) && (ACK[ACKFRAMESIZE-1] == 0x0A))
		{
			if(ACK[ACKFRAMESIZE-3] == 0x00)
			{
				UsersCounter++;
				return SUCCESS;
			}
		}
	}
	return ERROR;

}
u8 FingerPS_searchFinger(void)
{
	u8 i,ACKFRAMESIZE=16;

	u8 Search[]={0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x08, 0x04, 0x01, 0x00, 0x01 ,0x00 ,0x01 ,0x00,0x0E};

	for(i=0;i<sizeof(Search);i++)
	{
		UART_sendByte(Search[i]);
	}
	UART_receiveByteAsynchCallBack(getByte);

	delayMilliSec(5);

	if(ACKCounter == ACKFRAMESIZE)
	{
		/* We can't count on the checksum here since the MatchScore cannot be pre-determined */
//		if((ACK[ACKFRAMESIZE-2] == 0x00) && (ACK[ACKFRAMESIZE-1] == 0x0A))
//		{
			if(ACK[ACKFRAMESIZE-7] == 0x00)
			{
				return SUCCESS;
			}
//		}
	}
	return ERROR;
}
u8 FingerPS_emptyLibrary(void);
u8 FingerPS_deleteFinger(void);
u8 FingerPS_LoadCharFile(void);
static u16 FingerPS_calcCheckSum(u8* frame);
u8 FingerPS_match(void);
u8 FingerPS_AuraNormal(void)
{
	u8 i,ACKFRAMESIZE=12;

	u8 AuraLedConfigPurple[]={0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x07, 0x35, 0x01, 0xF0, 0x03 ,0x00 ,0x01 ,0x31};

	for(i=0;i<sizeof(AuraLedConfigPurple);i++)
	{
		UART_sendByte(AuraLedConfigPurple[i]);
	}
	UART_receiveByteAsynchCallBack(getByte);

	delayMilliSec(5);

	if(ACKCounter == ACKFRAMESIZE)
	{
		if((ACK[ACKFRAMESIZE-2] == 0x00) && (ACK[ACKFRAMESIZE-1] == 0x0A))
		{
			if(ACK[ACKFRAMESIZE-3] == 0x00)
			{
				return SUCCESS;
			}
		}
	}
	return ERROR;
}
u8 FingerPS_AuraSuccess(void)
{

	u8 i,ACKFRAMESIZE=12;

	u8 AuraLedConfigBlue[]={0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x07, 0x35, 0x01, 0xF0, 0x02 ,0x00 ,0x01 ,0x30};

	for(i=0;i<sizeof(AuraLedConfigBlue);i++)
	{
		UART_sendByte(AuraLedConfigBlue[i]);
	}
	UART_receiveByteAsynchCallBack(getByte);

	delayMilliSec(5);

	if(ACKCounter == ACKFRAMESIZE)
	{
		if((ACK[ACKFRAMESIZE-2] == 0x00) && (ACK[ACKFRAMESIZE-1] == 0x0A))
		{
			if(ACK[ACKFRAMESIZE-3] == 0x00)
			{
				return SUCCESS;
			}
		}
	}
	return ERROR;

}
u8 FingerPS_AuraError(void)
{
	u8 i,ACKFRAMESIZE=12;

	u8 AuraLedConfigBlue[]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x07,0x35,0x02,0x80,0x01,0x80,0x01,0x3F};

	for(i=0;i<sizeof(AuraLedConfigBlue);i++)
	{
		UART_sendByte(AuraLedConfigBlue[i]);
	}
	UART_receiveByteAsynchCallBack(getByte);

	delayMilliSec(5);

	if(ACKCounter == ACKFRAMESIZE)
	{
		if((ACK[ACKFRAMESIZE-2] == 0x00) && (ACK[ACKFRAMESIZE-1] == 0x0A))
		{
			if(ACK[ACKFRAMESIZE-3] == 0x00)
			{
				return SUCCESS;
			}
		}
	}
	return ERROR;
}

void delayCallBack(void)
{
	flag = 1;
}

void delayMilliSec(u32 millisec)
{

	Timer0_SetCallBack(delayCallBack);
	TIMER0_clearTimerValue();
	Timer0_SetDelayTimeMilliSec(&config,millisec);
	while(flag == 0);
	flag = 0;
}

void getByte(u8 byte)
{
	ACK[ACKCounter] = byte;
	ACKCounter++;
}
