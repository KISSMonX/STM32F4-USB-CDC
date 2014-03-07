#include "SccFrame.h"
#include "Util.h"
#include "Crc.h"

#include <string.h>

int FrameParse( SccFrameHdr* Hdr, const uint8_t* Src, int Len )
{
	if( !Len )
		return 0;

	if( Len < (int) SCC_HEADER_SIZE )
		return 1;

	int R = 0;

	Hdr->Flags	= Src[ R++ ];
	if( !( Hdr->Flags & SCC_LEADER_FLAG ) )
	   return -1;	
	
	Hdr->Cmd	= Src[ R++ ];
	Hdr->DstAddress = MakeDoubleWord_1( Src[ R + 0 ], Src[ R + 1 ], Src[ R + 2 ], Src[ R + 3 ] );
	R += 4;
	
	Hdr->SrcAddress = MakeDoubleWord_1( Src[ R + 0 ], Src[ R + 1 ], Src[ R + 2 ], Src[ R + 3 ] );
	R += 4;
	

	Hdr->Length = MakeWord( Src[ R + 0 ], Src[ R + 1 ] );
	R += 2;

	if( Hdr->Length > SCC_MAX_PAYLOAD_SIZE )
		return -1;
	
	if( Len < SCC_HEADER_SIZE + Hdr->Length + SCC_CRC_SIZE )
		return 1;

	R += Hdr->Length;

	uint16_t Crc = Crc16( Src, R );

	if( Crc != MakeWord( Src[ R + 0 ], Src[ R + 1 ] ) )
		return -1;
	R += SCC_CRC_SIZE;

	return R;
}

int FrameWriteHeader( uint8_t* Dst, int Len, const SccFrameHdr* Hdr )
{
	if( Len < (int)SCC_MIN_FRAME_SIZE )
		return -1;

	int R = 0;

	Dst[ R++ ] = Hdr->Flags;
	Dst[ R++ ] = Hdr->Cmd;

	SplitDoubleWord( &Dst[ R ], Hdr->DstAddress );
	R += 4;
	
	SplitDoubleWord( &Dst[ R ], Hdr->SrcAddress );
	R += 4;

	SplitWord( &Dst[ R ], Hdr->Length );
	R += 2;
	
	return R;
}

