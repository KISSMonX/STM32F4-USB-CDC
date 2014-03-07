#ifndef IOMAP_H
#define IOMAP_H

#include "Types.h"

void		IoMapDiSet		( int channel, bool value );
void		IoMapDiSetPort	( int port, uint16_t value );
bool		IoMapDiGet		( int channel );
uint16_t	IoMapDiGetPort	( int port );

void		IoMapAiSetPort	( int port, uint16_t value );
uint16_t	IoMapAiGetPort	( int port );

#endif	// IOREG_H

