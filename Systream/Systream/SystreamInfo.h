#pragma once
#include <Windows.h>
class SystreamInfo
{
public:
	SystreamInfo();
	~SystreamInfo();

	//��ȡ�ڴ�ʹ����
	int GetSytMemory();
	//��ȡ��CPUʹ����
	int GetAllCpu();
	//��ȡ����CPUʹ����
	//��ȡ����������
	//��ȡ����������������

	//CPU���ܺ���
	bool Initialize();
	int GetCpuUserRate();
	double FileTimeToDouble(FILETIME &filetime);

private:
	MEMORYSTATUSEX memStatusex;
	double m_fOldCPUIdleTime;
	double m_fOldCPUKernelTime;
	double m_fOldCPUUserTime;
};

