#include <stdio.h>
#include <windows.h>
#include <tchar.h>

// ���: ���μ����� �ٸ� ���μ����� Ŀ�ο�����Ʈ�� ������ �� ��.
// ��, Ŀ�ο�����Ʈ�� ���μ��������� �ƴ϶� �ü�� �������̴�.

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;

	si.cb = sizeof(si);

	TCHAR command[] = _T("process_priority2.exe");
	// ���μ��� ����.
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
		// �ڽ� ���μ����� �켱������ ������� �ǵ�����.
		//pi�� hProcess�� ���μ����� �ڵ��̴�.
		if (timing == 2)
			SetPriorityClass(pi.hProcess, NORMAL_PRIORITY_CLASS);
	}

	return 0;
}
