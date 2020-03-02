#include <stdio.h>
#include <tchar.h>
#include <windows.h>

// Operation2.exe를 실행시키고나서 "Operation1.exe \n"를 계속 출력한다.
int t_main(int argc, TCHAR* argv[])
{
	// STARTUPINFO : CreateProcess()에 정보전달
	STARTUPINFO si = { 0, };
	// PROCESS_INFORMATION : CreateProcess()로부터 정보받음
	PROCESS_INFORMATION pi;
	
	si.cb = sizeof(si);
	TCHAR command[] = _T("Operation2.exe");

	//프로세스 생성
	CreateProcess(
		NULL, command, NULL, NULL,
		TRUE, 0, NULL, NULL, &si, &pi
	);
	
	while (1)
	{
		for (DWORD i = 0; i < 10000; i++)
		{
			for (DWORD i = 0; i < 10000; i++);
		}
		_fputts(_T("Operation1.exe \n"), stdout);
	}
	return 0;
}