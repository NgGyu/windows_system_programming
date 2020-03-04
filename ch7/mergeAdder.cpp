#include <stdio.h>
#include <windows.h>
#include <tchar.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si1={0,};
	STARTUPINFO si2={0,};
	
	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;
	
	DWORD return_val1;
	DWORD return_val2;

	TCHAR command1[]=_T("PartAdder.exe 1 5");
	TCHAR command2[]=_T("PartAdder.exe 6 10");

  DWORD sum=0;

	si1.cb=sizeof(si1);
	si2.cb=sizeof(si2);

	CreateProcess(
        NULL,command1,NULL,NULL,TRUE, 
		0, NULL, NULL, &si1, &pi1
	);  

	CreateProcess(
        NULL,command2,NULL,NULL,TRUE, 
		0, NULL, NULL, &si2, &pi2
	);  

	CloseHandle(pi1.hThread);
	CloseHandle(pi2.hThread);	

    //WaitForSingleObject()을 하지않으면 프로세스가 종료되지않았다면
    //상수 STILL_ACTIVE(259)를 얻게되서 sum은 518이 될것이다. 
    //이것이 WaitForSingleObject()이 필요한 이유이다.
    HANDLE* handles = (HANDLE*)malloc(2*sizeof(HANDLE));
    handles[0] = pi1.hProcess;
    handles[1] = pi2.hProcess;
    WaitForMultipleObjects(
        2, handles,TRUE, INFINITE
    );

    /*
	WaitForSingleObject(pi1.hProcess, INFINITE);
    _tprintf(_T("Got return_value1\n"));
	WaitForSingleObject(pi2.hProcess, INFINITE);
    _tprintf(_T("Got return_value2\n"));
    */

    free(handles);

	//프로그램이 종료되면서 exitcode를 자신의 Kerobj에 전달한다.
  
    //GetExitCodeProcess(): exitcode를 Kerobj에서 가져오는 함수
	GetExitCodeProcess(pi1.hProcess, &return_val1);
	GetExitCodeProcess(pi2.hProcess, &return_val2);
    //정상적으로 종료되었다면
    //범위내의 합이 -1이 되는 경우는 없다고 가정
	if(return_val1==-1 || return_val2==-1)	
		return -1; 
	
	sum+=return_val1;
	sum+=return_val2;

	_tprintf(_T("total : %d \n"), sum);
	
	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	return 0;
}