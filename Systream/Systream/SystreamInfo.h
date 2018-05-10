#pragma once
#include <Windows.h>
#include <iostream>
#include <gcroot.h>
#include <minwindef.h>
#include <iphlpapi.h>
#include <map>
#pragma comment(lib,"Iphlpapi")
using namespace std;

//#using "bin/Debug/CPU.dll"
//#using "bin/Release/CPU.dll"

//using namespace CPUDLL;
//using namespace System;
//using namespace System::Text;

typedef struct _NetInfo
{
	char *Mac;
	ULONG SendBytes;
	ULONG RecvBytes;
}NetInfo;

typedef struct _SysInfo
{
	int64_t Cpu;
	int64_t MemoryTotal;
	int64_t MemoryUsed;
	int64_t MemoryOcp;
	map<DWORD, NetInfo> NetWork;
}SysInfo;

class SystreamInfo
{
public:
	SystreamInfo();
	~SystreamInfo();

	//获取内存使用率
	void GetSytMemory();
	//获取总CPU使用率
	void GetCpuUserRate();
	//获取单核CPU使用率
	string GetCpuUsageRateList();
	//获取总网络速率
	//获取单个网卡网络速率

	//CPU功能函数
	bool Initialize();
	double FileTimeToDouble(FILETIME &filetime);

private:
	MEMORYSTATUSEX memStatusex;
	double m_fOldCPUIdleTime;
	double m_fOldCPUKernelTime;
	double m_fOldCPUUserTime;

	//CShapeCPUUseRate ^ cpuUseRate = gcnew CShapeCPUUseRate;
	//gcroot<CShapeCPUUseRate^> cpuUseRate;
	SysInfo m_Sysinfo;

};

