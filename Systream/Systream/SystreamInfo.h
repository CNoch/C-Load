#pragma once
#include <Windows.h>
#include <stdint.h>
#include <vector>
#include <iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib")

typedef struct _NetInfo
{
	char *Mac;
	uint64_t RecvBytes;
	uint64_t SendBytes;
}NetInfo;

typedef struct _SysInfo
{
	int Cpu;
	uint64_t MemoryTotal;
	uint64_t MemoryAvail;
	uint64_t MemoryOcp;
	std::vector<NetInfo> NetWork;
}SysInfo;

class SystreamInfo
{
public:
	SystreamInfo();
	~SystreamInfo();

	//获取内存使用率
	void GetSytMemory();
	//获取CPU使用率
	void GetSysCpu();
	//获取网络
	void GetNetWork();

	double FileTimeToDouble(FILETIME & filetime);
	bool Initialize();
	void GetCpuUserRate();

private:
	MEMORYSTATUSEX memStatusex;
	double m_fOldCPUIdleTime;
	double m_fOldCPUKernelTime;
	double m_fOldCPUUserTime;

	SysInfo c_SysInfo;
};

