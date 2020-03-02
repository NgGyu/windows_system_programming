#include <stdio.h>
#include <windows.h>
#include <tchar.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;

	si.cb = sizeof(si);

	TCHAR command[] = _T("close_handle2.exe");

	CreateProcess(
		NULL, command, NULL, NULL,
		TRUE, 0, NULL, NULL, &si, &pi
	);

	CloseHandle(pi.hProcess);
	// 실행해보면 CloseHandle()을 실행 했음에도 프로세스가 끝나지 않음을
	// 확인할 수 있다. 사용자가 KerObj를 관리하는게 아니라 
	// 운영체제가 커널 오브젝트를 관리하는것을 볼 수있다.
	// CloseHandle()은 해당 Kerobj의 핸들을 반환하면서 Kerobj의 Using Count를 1 감소시키는 기능을 함

	return 0;
}
