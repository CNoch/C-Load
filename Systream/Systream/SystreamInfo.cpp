#include "stdafx.h"
#include "SystreamInfo.h"
#include <sstream>

uint64_t FileTimeToInt64(const FILETIME &time)
{
	ULARGE_INTEGER tt;
	tt.LowPart = time.dwLowDateTime;
	tt.HighPart = time.dwHighDateTime;
	return static_cast<int64_t>(tt.QuadPart);
}

SystreamInfo::SystreamInfo()
{
	m_Sysinfo = { 0 };
	lastinbytes = 0;
	lastoutbytes = 0;
	pAdpterInfo = nullptr;
	EnumAdapter();
	memStatusex.dwLength = sizeof(MEMORYSTATUSEX);
	GetSystemTimes(&m_fOldCPUKernelTime, &m_fOldCPUIdleTime, &m_fOldCPUUserTime);
	Sleep(1000);
}


SystreamInfo::~SystreamInfo()
{
}

void SystreamInfo::GetSysMemory()
{
	GlobalMemoryStatusEx(&memStatusex);
	m_Sysinfo.MemoryTotal = memStatusex.ullTotalPhys / 1024 / 1024;
	m_Sysinfo.MemoryUsed = (memStatusex.ullTotalPhys - memStatusex.ullAvailPhys) / 1024 / 1024;
	m_Sysinfo.MemoryOcp = memStatusex.dwMemoryLoad;
}


void SystreamInfo::GetSysCpu()
{
	FILETIME idleTime;
	FILETIME kernelTime;
	FILETIME userTime;
	GetSystemTimes(&kernelTime, &idleTime, &userTime);
	int64_t idle = FileTimeToInt64(idleTime) - FileTimeToInt64(m_fOldCPUIdleTime);
	int64_t kernel = FileTimeToInt64(kernelTime) - FileTimeToInt64(m_fOldCPUKernelTime);
	int64_t user = FileTimeToInt64(userTime) - FileTimeToInt64(m_fOldCPUUserTime);

	m_fOldCPUIdleTime = idleTime;
	m_fOldCPUKernelTime = kernelTime;
	m_fOldCPUUserTime = userTime;
	if (kernel + user == 0)
	{
		return;
	}
	//(总时间 - 空闲时间)/总时间 = CPU使用率
	int64_t cpu = (kernel + user - idle) * 100 / (kernel + user);
	m_Sysinfo.Cpu = cpu;
}

void SystreamInfo::GetSysNetWork()
{
	DWORD in_bytes = 0;
	DWORD out_bytes = 0;
	for (auto i = 0;i < m_Index_Net.size();++i)
	{
		NetInfo ninfo = { 0 };
		getNetWorkStatus(i, in_bytes, out_bytes);
		map<int, DWORD>::iterator iDI = m_Id_Index.find(i);
		if (iDI != m_Id_Index.end())
		{
			map<DWORD, NetInfo>::iterator it = m_Index_Net.find(iDI->second);
			if (it != m_Index_Net.end())
			{
				m_Sysinfo.NetWork[it->first].Mac = it->second.Mac;
				m_Sysinfo.NetWork[it->first].RecvBytes = in_bytes - it->second.RecvBytes;
				m_Sysinfo.NetWork[it->first].SendBytes = out_bytes - it->second.SendBytes;
				it->second.SendBytes = out_bytes;
			}
		}
	}
}

bool SystreamInfo::EnumAdapter()
{
	ULONG uloutBufLen = 0;
	DWORD dwRetVal = 0;
	int Id = 0;
	pAdpterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
	uloutBufLen = sizeof(IP_ADAPTER_INFO);
	if (ERROR_SUCCESS != GetAdaptersInfo(pAdpterInfo,&uloutBufLen))
	{
		free(pAdpterInfo);
		pAdpterInfo = (IP_ADAPTER_INFO *)malloc(uloutBufLen);
	}
	if (ERROR_SUCCESS != GetAdaptersInfo(pAdpterInfo,&uloutBufLen))
	{
		return false;
	}
	PIP_ADAPTER_INFO pAdapter = pAdpterInfo;
	while (pAdapter)
	{
		char *Mac = new char[20]();
		int len = 0;
		for (auto i = 0;i<pAdapter->AddressLength;i++)
		{
			char *Mad = new char[3]();
			if (i == pAdapter->AddressLength - 1)
			{
				sprintf_s(Mad, sizeof(Mad), "%.2X", (int)pAdapter->Address[i]);
				memcpy(Mac + len, Mad, sizeof(Mad));
				break;
			}
			sprintf_s(Mad, sizeof(Mad), "%.2X-", (int)pAdapter->Address[i]);
			memcpy(Mac + len, Mad, sizeof(Mad));
			len += strlen(Mad);
		}
		NetInfo NI = { 0 };
		NI.Mac = Mac;
		NI.RecvBytes = 0;
		NI.SendBytes = 0;
		m_Index_Net[pAdapter->Index] = NI;
		m_Id_Index[Id] = pAdapter->Index;
		pAdapter = pAdapter->Next;
		Id++;
	}
	return true;
}

bool SystreamInfo::getNetWorkStatus(ULONG i, DWORD &inBytes, DWORD &outBytes)
{
	MIB_IFROW MibIfRow;
	map<int, DWORD>::iterator iDI = m_Id_Index.find(i);
	if (iDI != m_Id_Index.end())
	{
		map<DWORD, NetInfo>::iterator it = m_Index_Net.find(iDI->second);
		if (it != m_Index_Net.end())
		{
			MibIfRow.dwIndex = it->first;
			if (GetIfEntry(&MibIfRow) == NO_ERROR)
			{
				inBytes = MibIfRow.dwInOctets;
				outBytes = MibIfRow.dwOutOctets;
				return true;
			}
		}
	}
	return false;
}

void SystreamInfo::GetSysInfo(SysInfo & sysinfo)
{
	//memset(&sysinfo, 0, sizeof(sysinfo));
	GetSysCpu();
	GetSysMemory();
	GetSysNetWork();
	sysinfo = m_Sysinfo;
}
