#pragma once
#include <Windows.h>
#include <iostream>
#include <gcroot.h>
#include <minwindef.h>
#include <iphlpapi.h>
#include <map>
#include <stdint.h>
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


	void GetSysMemory();
	void GetSysCpu();
	void GetSysNetWork();
	bool EnumAdapter();//获取网卡信息
	bool getNetWorkStatus(ULONG i, DWORD &inBytes, DWORD &outBytes);

	void GetSysInfo(SysInfo & sysinfo);

public:
	IP_ADAPTER_INFO * pAdpterInfo;
	DWORD lastinbytes;
	DWORD lastoutbytes;
private:
	MEMORYSTATUSEX memStatusex;
	FILETIME m_fOldCPUIdleTime;
	FILETIME m_fOldCPUKernelTime;
	FILETIME m_fOldCPUUserTime;

	//CShapeCPUUseRate ^ cpuUseRate = gcnew CShapeCPUUseRate;
	//gcroot<CShapeCPUUseRate^> cpuUseRate;
	SysInfo m_Sysinfo;
	map<int, DWORD> m_Id_Index;
	map<DWORD, NetInfo> m_Index_Net;
};

