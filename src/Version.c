#include "Version.h"
#include "GpIo.h"

const VersionInfo_t FirmwareVersion = 
{
	.VerMajor	= FW_VER_MAJOR,
	.VerMinor	= FW_VER_MINOR,
};

VersionInfo_t HardwareVersion = 
{
	.VerMajor	= 0,
	.VerMinor	= 2,
};

void VersionInit ( void ) 
{
}