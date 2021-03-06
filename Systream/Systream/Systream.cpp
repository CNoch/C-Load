// Systream.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SystreamInfo.h"

int main()
{
	SystreamInfo *s = nullptr;
	s = new SystreamInfo();
	SysInfo sysinfo = { 0 };
	while (true)
	{
		s->GetSysInfo(sysinfo);
		printf("CPU使用率:%d%%%,总内存:%dMB,已用内存:%dMB,内存使用率:%d%%\n", sysinfo.Cpu,sysinfo.MemoryTotal,sysinfo.MemoryUsed,sysinfo.MemoryOcp);
		for (auto i = 0;i < sysinfo.NetWork.size(); i++)
		{
			printf("Mac:%s,NetSend:%d,NetRecv:%d\n", sysinfo.NetWork[i].Mac, sysinfo.NetWork[i].SendBytes, sysinfo.NetWork[i].RecvBytes);
		}
		Sleep(1000);
	}
	
    return 0;
}

