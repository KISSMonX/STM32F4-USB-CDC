#include "IoMap.h"
#include "Util.h"

#define IO_DI_START		0
#define IO_DI_LENGTH	2
#define IO_AI_START		2
#define IO_AI_LENGTH	32
#define IO_DO_START		34
#define IO_DO_LENGTH	2
#define IO_AO_START		36
#define IO_AO_LENGTH	32


typedef struct
{
	uint16_t Ports[ IO_DI_LENGTH + IO_AI_LENGTH + IO_DO_LENGTH + IO_AO_LENGTH ];
}IoMap_t;

static IoMap_t	IoMap;

void IoMapDiSet( int channel, bool value )
{
	int port = channel / 16;
	int line = channel % port;

	IoMap.Ports[  port ] = 
		BitSet16( IoMap.Ports[ IO_DI_START + port ], line, value );
}

void IoMapDiSetPort( int port, uint16_t value )
{
	IoMap.Ports[ IO_DI_START + port ] = value;
}


bool IoMapDiGet( int channel )
{
	int port = channel / 16;
	int line = channel % port;

	return BitGet16( IoMap.Ports[ IO_DI_START + port ], line );
}

uint16_t IoMapDiGetPort( int port )
{
	return IoMap.Ports[ IO_DI_START + port ];
}

void IoMapAiSetPort( int port, uint16_t value )
{
	IoMap.Ports[ IO_AI_START + port ] = value;
}

uint16_t IoMapAiGetPort( int port )
{
	return IoMap.Ports[ IO_AI_START + port ];
}
