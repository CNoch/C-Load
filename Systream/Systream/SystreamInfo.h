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

	//��ȡ�ڴ�ʹ����
	void GetSytMemory();
	//��ȡ��CPUʹ����
	void GetCpuUserRate();
	//��ȡ����CPUʹ����
	string GetCpuUsageRateList();
	//��ȡ����������
	//��ȡ����������������

	//CPU���ܺ���
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

