/****************************************************************************************************
 * File: 			Main.c
 * 
 * Written by 	: 	JD
 * Project		: 	RSC MSM MeasurementUnit
 * (C) Brunelco Electronic Innovators
 *****************************************************************************************************/
#include "stm32f4xx.h"
#include "SysInit.h"
#include "SysTick.h"
#include "GpIo.h"
#include "Adc.h"
#include "Watchdog.h"
#include "UsbHandler.h"

static void DiUpdateMap( void );

int main(void)
{
	SysInit();
	GpIoInit();
	AdcInit();

	SysTickInit();
	WatchDogInit();
	UsbHandlerInit();

	while (1)
	{		
		WatchDogRefresh();	

		SysTick_t tick  = SysTickGet();

		UsbHandlerRun( tick );

		DiUpdateMap();
		AiUpdateMap();
	}

	return 0;
}

#include "IoMap.h"
void DiUpdateMap()
{
	uint16_t di = GPIO_ReadInputData( GPIOB );

	IoMapDiSet( 0, di & GPIO_Pin_4 );
	IoMapDiSet( 1, di & GPIO_Pin_5 );
	IoMapDiSet( 2, di & GPIO_Pin_6 );
	IoMapDiSet( 3, di & GPIO_Pin_7 );
}
