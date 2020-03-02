#include <stdio.h>
#include <windows.h>
#include <tchar.h>

// process_priority1.cpp를 실행을 시키면 아래의 프로세스를 만들어 실행한다. 우선순위를 
// 높게 설정하므로 process_priority1의 프로세스는 낮은 우선순위를 갖게된다.  
int _tmain(int argc, TCHAR* argv[])
{
	// GetCurrentProcess() : 함수를 호출한 프로세스의 핸들을 반환한다.
	// SetPriorityClass(handle, priority) : 프로세스의 우선순위를 설정한다.
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

	while (1)
	{
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++);

		_fputts(_T("process_priority2.exe \n"), stdout);
	}

	return 0;
}