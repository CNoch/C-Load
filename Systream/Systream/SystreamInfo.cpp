#include "stdafx.h"
#include "SystreamInfo.h"


SystreamInfo::SystreamInfo()
{
	memStatusex.dwLength = sizeof(MEMORYSTATUSEX);
	Initialize();
}


SystreamInfo::~SystreamInfo()
{
}

int SystreamInfo::GetSytMemory()
{
	if (GlobalMemoryStatusEx(&memStatusex))
	{
		return memStatusex.dwMemoryLoad;
	}
	return 0;
}

int SystreamInfo::GetAllCpu()
{
	return 0;
}

bool SystreamInfo::Initialize()
{
	FILETIME ftIdle, ftKernel, ftUser;
	double m_fOldCPUIdleTime;
	double m_fOldCPUKernelTime;
	double m_fOldCPUUserTime;
	bool flag = false;
	if (flag = GetSystemTimes(&ftIdle, &ftKernel, &ftUser))
	{
		m_fOldCPUIdleTime = FileTimeToDouble(ftIdle);
		m_fOldCPUKernelTime = FileTimeToDouble(ftKernel);
		m_fOldCPUUserTime = FileTimeToDouble(ftUser);
	}
	return flag;
}

int SystreamInfo::GetCpuUserRate()
{
	int nCPUUseRate = -1;
	FILETIME ftIdle, ftKernel, ftUser;
	if (GetSystemTimes(&ftIdle, &ftKernel, &ftUser))
	{
		double fCPUIdleTime = FileTimeToDouble(ftIdle);
		double fCPUKernelTime = FileTimeToDouble(ftKernel);
		double fCPUUserTime = FileTimeToDouble(ftUser);
		nCPUUseRate = (int)(100.0 - (fCPUIdleTime - m_fOldCPUIdleTime)
			/ (fCPUKernelTime - m_fOldCPUKernelTime + fCPUUserTime - m_fOldCPUUserTime)
			*100.0);
		m_fOldCPUIdleTime = fCPUIdleTime;
		m_fOldCPUKernelTime = fCPUKernelTime;
		m_fOldCPUUserTime = fCPUUserTime;
	}
	return nCPUUseRate;
}

double SystreamInfo::FileTimeToDouble(FILETIME & filetime)
{
	return (double)(filetime.dwHighDateTime * 4.294967296E9) + (double)filetime.dwLowDateTime;
}
