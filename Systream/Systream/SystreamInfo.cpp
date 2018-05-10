#include "stdafx.h"
#include "SystreamInfo.h"
#include <sstream>

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
	GlobalMemoryStatusEx(&memStatusex);
	m_Sysinfo.MemoryTotal = memStatusex.ullTotalPhys / 1024 / 1024;
	m_Sysinfo.MemoryUsed = (memStatusex.ullTotalPhys - memStatusex.ullAvailPhys) / 1024 / 1024;
	m_Sysinfo.MemoryOcp = memStatusex.dwMemoryLoad;
}

void ConvertToString(System::String^ str, std::string& text)
{
	//const char * chars = (const char*)(Marshal::StringToHGlobalAnsi(str)).ToPointer();
}

//bool To_string(String ^source, string &target)
//{
//	
//}

//string SystreamInfo::GetCpuUsageRateList()
//{
//	System::String ^ a = cpuUseRate->GetCPUEveryCoreUseRate();
//	auto utf8 = Encoding::UTF8->GetBytes(a);
//	auto chars = new char[utf8->Length + 1];
//
//	return NULL;
//}

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

string SystreamInfo::GetCpuUsageRateList()
{
	return string();
}

double SystreamInfo::FileTimeToDouble(FILETIME & filetime)
{
	return (double)(filetime.dwHighDateTime * 4.294967296E9) + (double)filetime.dwLowDateTime;
}
