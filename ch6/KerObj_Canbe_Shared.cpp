#include <stdio.h>
#include <windows.h>
#include <tchar.h>

// 결론: 프로세스는 다른 프로세스의 커널오브젝트에 접근할 수 있.
// 즉, 커널오브젝트는 프로세스종속이 아니라 운영체제 종속적이다.

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;

	si.cb = sizeof(si);

	TCHAR command[] = _T("process_priority2.exe");
	// 프로세스 생성.
	CreateProcess(
		NULL,command,NULL,NULL,
		TRUE,0,NULL,NULL,&si,&pi
	); 

	DWORD timing = 0;
	while (1)
	{
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++); 
		_fputts(_T("Parent \n"), stdout);

		timing += 1;
		// 자식 프로세스의 우선순위를 원래대로 되돌린다.
		//pi의 hProcess는 프로세스의 핸들이다.
		if (timing == 2)
			SetPriorityClass(pi.hProcess, NORMAL_PRIORITY_CLASS);
	}

	return 0;
}
