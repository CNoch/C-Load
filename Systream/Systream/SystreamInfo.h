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
	//��ȡ����CPUʹ����
	//��ȡ����������
	//��ȡ����������������

private:
	MEMORYSTATUSEX memStatusex;
};

