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
	// �����غ��� CloseHandle()�� ���� �������� ���μ����� ������ ������
	// Ȯ���� �� �ִ�. ����ڰ� KerObj�� �����ϴ°� �ƴ϶� 
	// �ü���� Ŀ�� ������Ʈ�� �����ϴ°��� �� ���ִ�.
	// CloseHandle()�� �ش� Kerobj�� �ڵ��� ��ȯ�ϸ鼭 Kerobj�� Using Count�� 1 ���ҽ�Ű�� ����� ��

	return 0;
}
