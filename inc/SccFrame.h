#ifndef SCCFRAME_H_
#define SCCFRAME_H_

#include "Types.h"
#include <string.h>

#define	SCC_MAX_FRAME_SIZE			( 1024 + SCC_HEADER_SIZE + SCC_CRC_SIZE )
#define	SCC_HEADER_SIZE				12
#define	SCC_CRC_SIZE				2
#define	SCC_MAX_PAYLOAD_SIZE		( SCC_MAX_FRAME_SIZE - SCC_HEADER_SIZE - SCC_CRC_SIZE )
#define	SCC_MIN_FRAME_SIZE			( SCC_HEADER_SIZE + SCC_CRC_SIZE )

/*!
*	@brief	Header flags and masks
*	@note
*/
#define	SCC_LEADER_FLAG		0x80U	// Always 1
#define	SCC_CMD_FLAG		0x40U	// Command/Response
#define	SCC_EXC_FLAG		0x20U	// Exception

typedef uint32_t			LongAddressType_t;

typedef enum
{
	e_JumperFlag = 0x01,
}DiscoveryFlag_t;

typedef struct SccFrameHdr_tag
{
	uint8_t				Flags;
	uint8_t				Cmd;
	LongAddressType_t	DstAddress;	
	LongAddressType_t	SrcAddress;	
	uint16_t			Length;
}SccFrameHdr;

extern volatile SccFrameHdr* RxFramePtr;

int FrameParse			( SccFrameHdr* Hdr, const uint8_t* Src, int Len );
int FrameWriteHeader	( uint8_t* Dst, int Len, const SccFrameHdr* Hdr );


inline __attribute__((always_inline))
bool FrameIsCmd( uint8_t Flags )
{
	return ( Flags & SCC_LEADER_FLAG ) && 
			( Flags & SCC_CMD_FLAG  );
}

inline __attribute__((always_inline))
bool FrameIsResponse( uint8_t Flags )
{
	return ( Flags & SCC_LEADER_FLAG ) && 
			!( Flags & SCC_CMD_FLAG  );
}

#endif	// SCCFRAME_H_
