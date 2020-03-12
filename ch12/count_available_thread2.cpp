#include <stdio.h>
#include <windows.h>
#include <process.h> //_beginthreaadex
#include <tchar.h>

#define MAX_THREADS (1024*10)

unsigned int WINAPI ThreadProc( LPVOID lpParam ) 
{ 
	DWORD threadNum = (DWORD) lpParam;

	while(1)
	{
		_tprintf(_T("thread num: %d \n"), threadNum);
		Sleep(1000);
	}

    return 0; 
} 

DWORD cntOfThread = 0;

int _tmain(int argc, TCHAR* argv[])
{
    DWORD dwThreadId[MAX_THREADS];
    HANDLE hThread[MAX_THREADS];

    while(1)
    {

        hThread[cntOfThread] = (HANDLE)
		// CrateThread와 같음
			_beginthreadex ( 
				NULL,					  
				0,				          
				ThreadProc,				  
				(LPVOID)cntOfThread,       
				0,						   
				(unsigned *)&dwThreadId[cntOfThread]   
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

