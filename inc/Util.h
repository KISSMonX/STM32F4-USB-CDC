#ifndef UTIL_H_
#define UTIL_H_

#include "Types.h"

#include "stm32f4xx.h" // needed for the __REV and __REV16 intrinsics

static inline
int max( int A, int B ) { return A < B ? B : A; }
static inline
int min( int A, int B ) { return A < B ? A : B; }
static inline
uint32_t minU32( uint32_t A, uint32_t B ) { return A < B ? A : B; }
static inline
uint32_t maxU32( uint32_t A, uint32_t B ) { return A < B ? B : A; }

static inline
uint8_t NibbleGet8( uint8_t V, uint8_t B )
{
	return (V >> (B*4))&0x0F;
}

static inline
bool BitGet8( uint8_t V, uint8_t B )
{
	return ( V & ( 0x01U << B ) ) != 0;
}

static inline
uint8_t BitSet8( uint8_t V, uint8_t B, bool S )
{
	return S ? V | ( 0x01U << B ) : V & ~( 0x01U << B );
}

static inline
bool BitGet16( uint16_t V, uint8_t B )
{
	return ( V & ( 0x0001U << B ) ) != 0;
}

static inline
uint8_t MskGet8( uint8_t Src, uint8_t Msk )
{
	return Src & Msk;
}

static inline
uint8_t MskSet8( uint8_t Src, uint8_t Msk, bool Value )
{
	return Value ? Src | Msk : Src & ~( Msk );
}


static inline
uint16_t BitSet16( uint16_t V, uint8_t B, bool S )
{
	return S ? V | ( 0x0001U << B ) : V & ~( 0x0001U << B );
}

static inline
bool BitGet32( uint32_t V, uint8_t B )
{
	return ( V & ( 0x00000001U << B ) ) != 0;
}

static inline
uint32_t BitSet32( uint32_t V, uint8_t B, bool S )
{
	return S ? V | ( 0x00000001U << B ) : V & ~( 0x00000001U << B );
}

static inline
bool BitGet64( uint64_t V, uint8_t B )
{
	return ( V & ( 0x01ULL << B ) ) != 0;
}

static inline
uint64_t BitSet64( uint64_t V, uint8_t B, bool S )
{
	return S ? V | ( 0x01ULL << B ) : V & ~( 0x01ULL << B );
}

static inline
uint8_t NibbleSet8( uint8_t V, uint8_t B, uint8_t S)
{
	V &= ~( 0x0F << ( B * 4 ) );
	V |= B << ( S * 4 ) ;
	return V;
}

static inline
uint16_t ByteSet16( uint16_t V, uint8_t B, uint16_t S)
{
	V &= ~( 0x0F << ( B * 8 ) );
	V |= B << ( S * 8 ) ;
	return V;
}

static inline
uint8_t ByteGet16( uint16_t V, uint8_t B )
{
	return (V >> (B*8))&0x00FF;
}

static inline
uint8_t ByteReverse(uint8_t V)
{
	V = ( ( ( V & 0xAA ) >> 1 ) | ( ( V & 0x55 ) << 1 ) );
    V = ( ( ( V & 0xCC ) >> 2 ) | ( ( V & 0x33 ) << 2 ) );
    return( ( V >> 4 ) | ( V << 4 ) );
}

static inline
uint16_t MakeWord( uint8_t Msb, uint8_t Lsb )
{
	return ( ( (uint16_t) Msb ) << 8 ) | Lsb;
}


static inline
uint8_t MakeByte( uint8_t Msn, uint8_t Lsn )
{
	return  ( ( (uint8_t) Msn ) << 4 ) | Lsn;
}

static inline
uint8_t LsbGet( uint16_t Src )
{
	return Src & 0x00FFU;
}


static inline
uint8_t MsbGet( uint16_t Src )
{
	return ( Src >> 8U ) & 0x00FFU;
}

static inline
uint16_t LswGet( uint32_t Src )
{
	return Src & 0x0000FFFFU;
}

static inline
uint16_t MswGet( uint32_t Src )
{
	return ( Src >> 16U ) & 0x0000FFFFUL;
}

static inline
uint8_t* SplitWord( uint8_t* Dst, uint16_t Src )
{
	Dst[ 0 ] = MsbGet( Src );
	Dst[ 1 ] = LsbGet( Src );
	return Dst + 2;
}

static inline
uint8_t* SplitDoubleWord( uint8_t* Dst, uint32_t Src )
{
	Dst[ 0 ] = MsbGet( MswGet( Src ) );
	Dst[ 1 ] = LsbGet( MswGet( Src ) );
	Dst[ 2 ] = MsbGet( LswGet( Src ) );
	Dst[ 3 ] = LsbGet( LswGet( Src ) );
	return Dst + 4;
}

static inline 
uint32_t MakeDoubleWord( uint8_t* Src )
{
	uint32_t val = 0;
	for( int i = 0; i < 4; ++i )
	{
		val <<= 8;
		val |= (*Src++ & 0xff);		
	}
	return val;
}

static inline 
uint32_t MakeDoubleWord_1( uint8_t MswMsb, uint8_t MswLsb, uint8_t LswMsb, uint8_t LswLsb )
{
	uint32_t val = 0;
	val |= 0xFF000000 & ( MswMsb << 24 );
	val |= 0x00FF0000 & ( MswLsb << 16 );
	val |= 0x0000FF00 & ( LswMsb << 8 );
	val |= 0x000000FF & ( LswLsb << 0 );
	return val;
}

static inline
uint32_t DoubleWordReverseEndianness ( uint32_t Src )
{
	return __REV( Src );
}

#endif	// UTIL_H_
