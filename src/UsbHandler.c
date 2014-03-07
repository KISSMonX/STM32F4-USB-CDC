#include "UsbHandler.h"
#include "SccFrame.h"
#include "Crc.h"
#include "Util.h"
#include "SccProtocol.h"
#include "IoMap.h"

#include "usbd_conf.h"
#include "usbd_cdc_vcp.h"

static SysTick_t rxStartTick;

static void HandleFrame( const SccFrameHdr* Hdr, const uint8_t* Src, int Len );

void UsbHandlerInit()
{
	VCP_ModuleInit();
	rxStartTick = 0;
}

void UsbHandlerRun( SysTick_t tick )
{
	SccFrameHdr RxHdr;

	int RxLen = VCP_DataRxLength();
	uint8_t* RxBuffer = VCP_RxBuffer();

	switch( FrameParse( &RxHdr, RxBuffer, RxLen ) )
	{
		case -1:
			VCP_RxFlush();
			rxStartTick = 0;
			break;
		case 0:
			rxStartTick = 0;
			break;
		case 1:
			if( !rxStartTick )
				rxStartTick = tick;
			else
			if( SysTickDiff( rxStartTick, tick ) > SysTickToMs( 250 ) )
			{
				VCP_RxFlush();
				rxStartTick = 0;
			}
			break;

		default:
			rxStartTick = 0;
			HandleFrame( &RxHdr, RxBuffer, RxLen );
			VCP_RxFlush();
			break;
	}
}

void HandleFrame( const SccFrameHdr* Hdr, const uint8_t* Src, int Len )
{
	if( !FrameIsCmd( Hdr->Flags ) )
		return;

	SccFrameHdr txHdr = 
	{
		.Flags = SCC_LEADER_FLAG,
		.Cmd = Hdr->Cmd,
		.DstAddress = Hdr->SrcAddress,
		.SrcAddress = 0x12345678,
		.Length = 0
	};

	const uint8_t* rxData = Src + SCC_HEADER_SIZE;

	uint8_t* txBuffer = VCP_TxBuffer();
	uint8_t* txData = txBuffer + SCC_HEADER_SIZE;

	switch( Hdr->Cmd )
	{
		case Discovery:
			memcpy( txData, Src + SCC_HEADER_SIZE, Hdr->Length );
			txData += Hdr->Length;
			break;

		case ReadDigitalIn:
		{
			uint16_t start = MakeWord( rxData[ 0 ], rxData[ 1 ] );
			uint16_t length = MakeWord( rxData[ 2 ], rxData[ 3 ] );

			txData = SplitWord( txData, start );
			txData = SplitWord( txData, length );

			for( int i = 0; i < length; ++i )
			{
				uint16_t p = IoMapDiGetPort( start + i );
				txData = SplitWord( txData, p );
			}

			break;
		}
		
		case ReadAnalogIn:
		{
			uint16_t start = MakeWord( rxData[ 0 ], rxData[ 1 ] );
			uint16_t length = MakeWord( rxData[ 2 ], rxData[ 3 ] );

			txData = SplitWord( txData, start );
			txData = SplitWord( txData, length );

			for( int i = 0; i < length; ++i )
			{
				uint16_t p = IoMapAiGetPort( start + i );
				txData = SplitWord( txData, p );
			}

			break;
		}

		default:
			txHdr.Flags |= SCC_EXC_FLAG;
			break;
	}
	
	txHdr.Length = txData - ( txBuffer + SCC_HEADER_SIZE );
	
	FrameWriteHeader( txBuffer, APP_TX_DATA_SIZE, &txHdr );
	
	uint16_t crc =  Crc16( txBuffer, txData - txBuffer );

	*txData++ = MsbGet( crc );
	*txData++ = LsbGet( crc );

	VCP_StartTx( txData - txBuffer );
}
