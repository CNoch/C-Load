// Systream.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SystreamInfo.h"

int main()
{
	SystreamInfo *s = nullptr;
	s = new SystreamInfo();
	while (true)
	{
		printf("内存使用率:%d%%\n", s->GetSytMemory());
		printf("CPU使用率:%d%%%\n", s->GetCpuUserRate());
		Sleep(1000);
	}
	
    return 0;
}

