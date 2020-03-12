#include <stdio.h>
#include <windows.h>
#include <tchar.h>

#define MAX_THREADS (1024*10)

DWORD WINAPI ThreadProc( LPVOID lpParam ) 
{ 
	DWORD threadNum = (DWORD) lpParam;

	while(1)
	{
		_tprintf(_T("thread num: %d \n"), threadNum);
		Sleep(5000);
	}

    return 0; 
} 

DWORD cntOfThread = 0;

int _tmain(int argc, TCHAR* argv[])
{
    DWORD dwThreadId[MAX_THREADS];
	// 쓰레드들이 반환하는 핸들 배열
    HANDLE hThread[MAX_THREADS];


    while(1)
    {

        hThread[cntOfThread] = 
			CreateThread ( 
				NULL,					  
				0,				          // 스택크기
				ThreadProc,				  //thread_main()
				(LPVOID)cntOfThread,      //param 
				0,						  
				&dwThreadId[cntOfThread]   // thread id 반환
		    );			                
 
        if (hThread[cntOfThread] == NULL) 
        {
			_tprintf(_T("MAXIMUM THREAD SIZE: %d \n"), cntOfThread);
			break;
        }

		cntOfThread++;
    }

    for(DWORD i=0; i<cntOfThread; i++)
    {
        CloseHandle(hThread[i]);
    }

	return 0;
}

