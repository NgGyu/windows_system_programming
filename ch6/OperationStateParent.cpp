#include <stdio.h>
#include <windows.h>
#include <tchar.h>

int _tmain(int argc, TCHAR* argv[])
{
  STARTUPINFO si={0,};
	PROCESS_INFORMATION pi;
	DWORD state; 
	
	si.cb=sizeof(si);
  si.dwFlags=STARTF_USEPOSITION|STARTF_USESIZE;
  si.dwX=100;
  si.dwY=200;
  si.dwXSize=300;
  si.dwYSize=200;

	TCHAR command[]=_T("OperationStateChild.exe");

	CreateProcess(
		NULL, command, NULL, NULL,
		TRUE, 0, NULL, NULL, &si, &pi
	);


	for(int i=0; i<10000; i++)   // Child Process�� ���� ���� ��Ű�� ���ؼ�.
		for(int i=0; i<100000; i++);

	//�ڽ��� ����ɶ����� ��ٸ��� �Լ�
//	WaitForSingleObject(pi.hProcess, INFINITE);

	//�θ����μ����� �ڽ����μ����� �����ڵ带 �˼�����
	GetExitCodeProcess(pi.hProcess, &state);
	if(state == STILL_ACTIVE )
	{
	 _tprintf(_T("STILL_ACTIVE \n\n"));
	}
	else
	_tprintf(_T("state : %d \n\n"), state);

	return 0;
}
