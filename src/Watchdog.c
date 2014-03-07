#include "Watchdog.h"

#include "stm32f4xx.h"

#ifndef WATCHDOG_DISABLED
/*!
*	@brief
*	@note
		LSI clock between 30 and 60kHz
		WDTimeOut = 75 ms
		Prescaler = 64
		Tlsi = 1 / (LSI / prescaler) = 1 / (60kHz / 64) = 0.001067
		ReloadValue = WDTimeOut / Tlsi = 75ms / 0.001067 = 70

		this equals the minimum WDG-timeout!
		max. timeout occurs when LSI is @30 kHz (minimum): 2 * 75 ms = 150 ms
*/
void WatchDogInit( void )
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

	IWDG_SetPrescaler( IWDG_Prescaler_64 );
	IWDG_SetReload(70);// max value 4095 (0xFFF)

	IWDG_Enable();
	IWDG_ReloadCounter();
}

void WatchDogRefresh( void )
{
	IWDG_ReloadCounter();
}

#endif	// WATCHDOG_DISABLED
