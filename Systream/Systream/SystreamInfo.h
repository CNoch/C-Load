#pragma once
#include <Windows.h>
class SystreamInfo
{
public:
	SystreamInfo();
	~SystreamInfo();

	//获取内存使用率
	int GetSytMemory();
	//获取总CPU使用率
	int GetAllCpu();
	//获取单核CPU使用率
	//获取总网络速率
	//获取单个网卡网络速率

	//CPU功能函数
	bool Initialize();
	int GetCpuUserRate();
	double FileTimeToDouble(FILETIME &filetime);

private:
	MEMORYSTATUSEX memStatusex;
	double m_fOldCPUIdleTime;
	double m_fOldCPUKernelTime;
	double m_fOldCPUUserTime;
};

