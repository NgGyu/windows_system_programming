#include <stdio.h>
#include <tchar.h>
#include <windows.h>

// Operation2.exe�� �����Ű���� "Operation1.exe \n"�� ��� ����Ѵ�.
int t_main(int argc, TCHAR* argv[])
{
	// STARTUPINFO : CreateProcess()�� ��������
	STARTUPINFO si = { 0, };
	// PROCESS_INFORMATION : CreateProcess()�κ��� ��������
	PROCESS_INFORMATION pi;
	
	si.cb = sizeof(si);
	TCHAR command[] = _T("Operation2.exe");

	//���μ��� ����
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