#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <tchar.h>

#define NUM_OF_GATE		6

LONG gTotalCount = 0;

CRITICAL_SECTION   hCriticalSection;


void IncreaseCount()
{
	//유저모드 기반
	//1. Critical Section기반의 동기화 
	EnterCriticalSection (&hCriticalSection); // 사용중(잠금)
	gTotalCount++;
	LeaveCriticalSection (&hCriticalSection); // 잠금해제

	//2. Interlocked Function기반 동기화
	//InterlockedIncrement(&gTotalCount);
}


unsigned int WINAPI ThreadProc( LPVOID lpParam ) 
{ 
	for(DWORD i=0; i<1000; i++)
	{
		IncreaseCount();
	}

	return 0;
} 


int _tmain(int argc, TCHAR* argv[])
{
    DWORD dwThreadId[NUM_OF_GATE];
    HANDLE hThread[NUM_OF_GATE];

	//CriticalSectionObject(CSO) 초기화
	InitializeCriticalSection(&hCriticalSection);

	for(DWORD i=0; i<NUM_OF_GATE; i++)
	{
        hThread[i] = (HANDLE)
		    _beginthreadex ( 
			    NULL,
			    0,				        
			    ThreadProc,				  
			    NULL,                    
			    CREATE_SUSPENDED,		   
			    (unsigned *)&dwThreadId[i]   
	        );

	    if(hThread[i] == NULL)
	    {
	        _tprintf(_T("Thread creation fault! \n"));
	        return -1;
	    }
	}

	for(DWORD i=0; i<NUM_OF_GATE; i++)
	{
		ResumeThread(hThread[i]);
	}


	WaitForMultipleObjects(NUM_OF_GATE, hThread, TRUE, INFINITE);

	_tprintf(_T("total count: %d \n"), gTotalCount);

	for(DWORD i=0; i<NUM_OF_GATE; i++)
	{
		CloseHandle(hThread[i]);
	}
	
	//리소스 반납
	DeleteCriticalSection(&hCriticalSection);

	return 0;
}
