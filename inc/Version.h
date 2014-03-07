#ifndef VERSION_H_
#define VERSION_H_

#include "Types.h"

typedef struct VersionInfo_t_tag
{
	uint8_t	VerMajor;
	uint8_t	VerMinor;
}VersionInfo_t;

extern const VersionInfo_t FirmwareVersion;
extern VersionInfo_t HardwareVersion;

#define FW_VER_MAJOR		0
#define FW_VER_MINOR		1

void VersionInit ( void );

#endif	// VERSION_H_
