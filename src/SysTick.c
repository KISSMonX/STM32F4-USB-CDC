#include "stm32f4xx.h"
#include "SysTick.h"

// Module definition
#define _MODULE_NAME	"SysTick"

#define SYSTICK_START_VAL			1

#define SYSTICK_INTERNAL_PER_S	( SystemCoreClock )
#define	SYSTICK_INTERNAL_PER_MS	( SYSTICK_INTERNAL_PER_S / 10000 )

volatile static SysTick_t cSysTick = SYSTICK_START_VAL;
volatile static bool sysTickChanged = false;

void SysTickInit( void )
{
	SysTick_Config( SYSTICK_INTERNAL_PER_MS );
}

void SysTickExit( void )
{
}


/*!
*	@brief
*/
SysTick_t SysTickGet( void )
{
    static SysTick_t R = SYSTICK_START_VAL;

	if( sysTickChanged )
	{
		SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk);

		R = cSysTick;
		sysTickChanged = false;
			
		SysTick->CTRL |= (SysTick_CTRL_TICKINT_Msk);
	}
	if( !R )
		R = SYSTICK_START_VAL;

	return R;
}

/*!
*	@brief	Difference between two system ticks
*	@param	Earlier tick
*	@param	Later tick
*/
SysTick_t SysTickDiff( SysTick_t Earlier, SysTick_t Later )
{
	if( !Earlier || !Later )
		return UINT64_MAX;
	
	return Later >= Earlier ? 
		Later - Earlier :
		UINT64_MAX - Earlier + Later;
}

/*!
*	@brief	Systick interrupt handler
*/
void SysTick_Handler(void)
{	
    ++cSysTick;
	sysTickChanged = true;
}

