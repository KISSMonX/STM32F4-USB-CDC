#ifndef CRC_H_
#define CRC_H_

#include <stdint.h>

uint8_t Crc8Once	( uint8_t Crc, uint8_t Src );
uint8_t Crc8		( const uint8_t* Src, uint8_t Length );

uint16_t Crc16	( const uint8_t* Src, int Length );
uint16_t Crc16_1( uint16_t Crc, uint8_t Src );
uint16_t Crc16_2( uint16_t Crc, const uint8_t* Src, int Length );

uint32_t Crc32( const uint32_t* src, int len );

#endif	// CRC_H_
