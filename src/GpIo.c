/****************************************************************************************************
 * File: 			GpIo.c
 * 
 * Written by : JD
 * Project: 	Template		
 * (C) Brunelco Electronic Innovators
 *****************************************************************************************************/

#include "GpIo.h"

static void GpIoDisableUnused( void );
static void GpIoInitDigital( void );
static void GpIoInitAnalog( void );

void GpIoInit (void)
{
	GpIoInitDigital();
	GpIoInitAnalog();
	GpIoDisableUnused();
}

void GpIoInitDigital( void )
{
	GPIO_InitTypeDef GpIoCfg;

	// GPIO DigitalIn
	GpIoCfg.GPIO_Speed	= GPIO_Speed_100MHz;
	GpIoCfg.GPIO_OType	= GPIO_OType_OD;
	GpIoCfg.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GpIoCfg.GPIO_Mode	= GPIO_Mode_IN;

	GpIoCfg.GPIO_Pin	= GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init( GPIOB, &GpIoCfg );	

	GpIoCfg.GPIO_Pin	= GPIO_Pin_7;
	GPIO_Init( GPIOC, &GpIoCfg );	

	// GPIO DigitalOut
	GpIoCfg.GPIO_Speed	= GPIO_Speed_100MHz;
	GpIoCfg.GPIO_OType	= GPIO_OType_OD;
	GpIoCfg.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GpIoCfg.GPIO_Mode	= GPIO_Mode_OUT;

	GpIoCfg.GPIO_Pin	= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
							GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |
							GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |
							GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_14;

	GPIO_Init( GPIOD, &GpIoCfg );	
	GPIO_Init( GPIOE, &GpIoCfg );	
}

void GpIoInitAnalog( void )
{
	GPIO_InitTypeDef GpIoCfg;

	// GPIO DigitalIn
	GpIoCfg.GPIO_Speed	= GPIO_Speed_100MHz;
	GpIoCfg.GPIO_OType	= GPIO_OType_OD;
	GpIoCfg.GPIO_PuPd 	= GPIO_PuPd_NOPULL;
	GpIoCfg.GPIO_Mode	= GPIO_Mode_AN;

	GpIoCfg.GPIO_Pin	= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
							GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;

	GPIO_Init( GPIOA, &GpIoCfg );	

	GpIoCfg.GPIO_Pin	= GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init( GPIOB, &GpIoCfg );	

	GpIoCfg.GPIO_Pin	= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
							GPIO_Pin_4 | GPIO_Pin_5;

	GPIO_Init( GPIOC, &GpIoCfg );	
}

void GpIoDisableUnused( void )
{	
	GPIO_InitTypeDef GpIoCfg;

	GpIoCfg.GPIO_OType	= GPIO_OType_PP;
	GpIoCfg.GPIO_Speed	= GPIO_Speed_100MHz;
	GpIoCfg.GPIO_PuPd 	= GPIO_PuPd_NOPULL;	
	GpIoCfg.GPIO_Mode	= GPIO_Mode_IN;
	
	#ifdef IOPINS_UNUSED_PORTA
		GpIoCfg.GPIO_Pin	= IOPINS_UNUSED_PORTA;
		GPIO_Init( GPIOA, &GpIoCfg );
	#endif
	
	#ifdef IOPINS_UNUSED_PORTB
		GpIoCfg.GPIO_Pin	= IOPINS_UNUSED_PORTB;
		GPIO_Init( GPIOB, &GpIoCfg );
	#endif
	
	#ifdef IOPINS_UNUSED_PORTC
		GpIoCfg.GPIO_Pin	= IOPINS_UNUSED_PORTC;
		GPIO_Init( GPIOC, &GpIoCfg );
	#endif
	
	#ifdef IOPINS_UNUSED_PORTD
		GpIoCfg.GPIO_Pin	= IOPINS_UNUSED_PORTD;		
		GPIO_Init( GPIOD, &GpIoCfg );	
	#endif
}
