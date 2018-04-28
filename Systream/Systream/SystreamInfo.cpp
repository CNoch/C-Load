#include "stdafx.h"
#include "SystreamInfo.h"


SystreamInfo::SystreamInfo()
{
	memStatusex.dwLength = sizeof(MEMORYSTATUSEX);
}


SystreamInfo::~SystreamInfo()
{
}

int SystreamInfo::GetSytMemory()
{
	return memStatusex.dwMemoryLoad;
}
