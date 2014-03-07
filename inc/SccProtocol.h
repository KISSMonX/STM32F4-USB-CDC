#ifndef SCCPROTOCOL_H_
#define SCCPROTOCOL_H_

#include "SysTick.h"

#define	SCC_BOARD_BROADCAST			0xFFFFFFFFUL
#define	SCC_INVALID_LONG_ADDRESS	SCC_BOARD_BROADCAST

typedef enum BoardCmdId_e
{
	Discovery		= 0x00,
	ReadDigitalIn	= 0x01,
	ReadAnalogIn 	= 0x02,
	ReadDigitalOut	= 0x03,
	WriteDigitalOut	= 0x04,
	ReadAnalogOut	= 0x05,
	WriteAnalogOut	= 0x06,
}BoardCmdId;

typedef enum
{
	e_RscOk	= 0,
	e_RscError = 1,
	e_RscBusy = 2,
}ResultCode;

static inline __attribute__((always_inline))
bool ProtocolIsDiscoveryCmd( BoardCmdId Cmd )
{
	return Cmd == Discovery;
}

static inline __attribute__((always_inline))
bool ProtocolIsBroadcast( LongAddressType_t Address )
{
	return Address == SCC_BOARD_BROADCAST;
}

static inline __attribute__((always_inline))
bool ProtocolIsValidAddress( LongAddressType_t Address )
{
	return Address != SCC_INVALID_LONG_ADDRESS && Address != (LongAddressType_t)0;
}

/*!
	@brief
	@par	Handle command if:
			- Its for us
			- AND our address is valid			
*/
static inline __attribute__((always_inline))
bool ProtocolShouldHandleCmd( LongAddressType_t OwnAddress, LongAddressType_t DstAddress, BoardCmdId Cmd )
{		
	bool R = (DstAddress == SCC_BOARD_BROADCAST) || (DstAddress == OwnAddress); // its for us
	R &= ProtocolIsValidAddress( OwnAddress ); // AND our DstAddress is valid (regardless the received command, sort that out in HandleCommand)	
	
	return R;
}

#endif	// SCCPROTOCOL_H_
