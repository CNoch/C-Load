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

void SystreamInfo::GetSytMemory()
{
	if (GlobalMemoryStatusEx(&memStatusex))
	{
		c_SysInfo.MemoryTotal = memStatusex.ullTotalPhys;
		c_SysInfo.MemoryAvail = memStatusex.ullTotalPhys;
		c_SysInfo.MemoryOcp = memStatusex.dwMemoryLoad;
	}
}

void SystreamInfo::GetSysCpu()
{

}



void SystreamInfo::GetNetWork()
{

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

void SystreamInfo::GetCpuUserRate()
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
