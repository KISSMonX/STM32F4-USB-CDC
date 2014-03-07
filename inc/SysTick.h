#ifndef SYSTICK_H
#define SYSTICK_H

#include "Types.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef uint64_t	SysTick_t;

#define			SYSTICK_PER_MS			10
#define			SysTickFromMs10(A)		((A))
#define			SysTickFromMs(A)		((A) * SYSTICK_PER_MS)
#define			SysTickFromS(A)			((A) * SYSTICK_PER_MS * 1000 )
#define			SysTickFromMin(A)		((A) * SYSTICK_PER_MS * 60000 )
#define			SysTickToMs(A)			((A) / SYSTICK_PER_MS )
#define			SysTickToS(A)			((A) / (SYSTICK_PER_MS * 1000) )
#define			SysTickToMin(A)			((A) / (SYSTICK_PER_MS * 60000) )
#define			SysTickToHours(A)		((A) / (SYSTICK_PER_MS * 3600000) )

void 			SysTickInit				( void );
void 			SysTickRun				( SysTick_t Tick );
void 			SysTickExit				( void );
SysTick_t		SysTickGet				( void );

#ifdef	__GNUC__
SysTick_t		SysTickDiff				( SysTick_t Earlier, SysTick_t Later );
#endif

//static inline void WaitMs( int8_t Ms ) //Bad function
//{
//	SysTick_t T = SysTickGet();
//	while( SysTickGet() < T + Ms );
//}

#ifndef NDEBUG
int	SysTickTest( void );
#endif	// NDEBUG

#ifdef __cplusplus
}
#endif

#endif	// SYSTICK_H
