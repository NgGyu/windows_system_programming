#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <tchar.h>

#define NUM_OF_GATE		6

LONG gTotalCount = 0;

/* 유저모드의 Critical Section과 다른 것*/

// CRITICAL_SECTION   gCriticalSection;
HANDLE hMutex;

DWORD AcquireMutex(HANDLE mutex)
{
	return WaitForSingleObject(mutex, INFINITE);
}

void IncreaseCount()
{
//	EnterCriticalSection (&gCriticalSection);
	AcquireMutex(hMutex); //가독성을 위해 래핑해서 사용한다.

	gTotalCount++;

//	LeaveCriticalSection (&gCriticalSection);
	ReleaseMutex(hMutex);  //위함수와 같은 역할
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
    DWORD dwThreadIDs[NUM_OF_GATE];
    HANDLE hThreads[NUM_OF_GATE];

//	InitializeCriticalSection(&gCriticalSection);
//위함수와 같은 역할
    hMutex = CreateMutex (
		           NULL,    
                   FALSE,    
                   NULL      
		     );

    if (hMutex == NULL) 
    {
        _tprintf(_T("CreateMutex error: %d\n"), GetLastError());
    }

	for(DWORD i=0; i<NUM_OF_GATE; i++)
	{
        hThreads[i] = (HANDLE)
		    _beginthreadex ( 
			    NULL,
			    0,				        
			    ThreadProc,				  
			    NULL,                    
			    CREATE_SUSPENDED,		   
			    (unsigned *)&dwThreadIDs[i]   
	        );

	    if(hThreads[i] == NULL)
	    {
	        _tprintf(_T("Thread creation fault! \n"));
	        return -1;
	    }
	}

	for(DWORD i=0; i<NUM_OF_GATE; i++)
	{
		ResumeThread(hThreads[i]);
	}


	WaitForMultipleObjects(NUM_OF_GATE, hThreads, TRUE, INFINITE);

	_tprintf(_T("total count: %d \n"), gTotalCount);

	for(DWORD i=0; i<NUM_OF_GATE; i++)
	{
		CloseHandle(hThreads[i]);
	}
  
//	DeleteCriticalSection(&gCriticalSection);
	CloseHandle(hMutex);  //위함수와 같은 역할

	return 0;
}
