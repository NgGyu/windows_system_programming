#include <stdio.h>
#include <windows.h>
#include <tchar.h>

// process_priority1.cpp�� ������ ��Ű�� �Ʒ��� ���μ����� ����� �����Ѵ�. �켱������ 
// ���� �����ϹǷ� process_priority1�� ���μ����� ���� �켱������ ���Եȴ�.  
int _tmain(int argc, TCHAR* argv[])
{
	// GetCurrentProcess() : �Լ��� ȣ���� ���μ����� �ڵ��� ��ȯ�Ѵ�.
	// SetPriorityClass(handle, priority) : ���μ����� �켱������ �����Ѵ�.
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

	while (1)
	{
		for (DWORD i = 0; i < 10000; i++)
			for (DWORD i = 0; i < 10000; i++);

		_fputts(_T("process_priority2.exe \n"), stdout);
	}

	return 0;
}