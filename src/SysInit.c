#include "SysInit.h"

#ifdef __GNUC__
#include "stm32f4xx.h"
#endif

// Module definition
#define _MODULE_NAME	"SysInit"

static void SysInitRCC	( void );
static void SysInitNVIC	( void );

void SysInit( void )
{
	SysInitRCC();
	SysInitNVIC();
}

void SysInitRCC( void )
{
	// System clock is set by the SystemInit-function, called by the startup-file before main is called. 
	// So, when correctly configured in system_stm32f40x.c, the system runs at HSE 8 MHz, using PLL to create 168 MHz SystemClock	

	// Enable AHB1 periphs
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOA, ENABLE );		
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOB, ENABLE );		
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOC, ENABLE );
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOD, ENABLE );
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOE, ENABLE );
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOF, ENABLE );
	RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOG, ENABLE );
}

void SysInitNVIC( void )
{
	// Configure the NVIC Preemption Priority Bits
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_1 );// 1 bit for Priority, 3bits for subpriority

/*
	NVIC_InitTypeDef NVICCfg;
	NVICCfg.NVIC_IRQChannel						= USART2_IRQn;
	NVICCfg.NVIC_IRQChannelPreemptionPriority	= 1;
	NVICCfg.NVIC_IRQChannelSubPriority			= 0;
	NVICCfg.NVIC_IRQChannelCmd					= ENABLE;
	NVIC_Init( &NVICCfg );
*/
}
