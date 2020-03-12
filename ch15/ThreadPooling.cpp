#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>

#define WORK_MAX  10000
#define THREAD_MAX      50

typedef void (*WORK) (void);

DWORD AddWorkToPool(WORK work);
WORK GetWorkFromPool(void);
DWORD MakeThreadToPool(DWORD numOfThread);
void WorkerThreadFunction(LPVOID pParam);

typedef struct __WorkerThread
{
	HANDLE hThread;
	DWORD idThread;
} WorkerThread;


// Work와 Thread관리를 위한 구조체
struct __ThreadPool
{
	// Work 등록배열
	WORK workList[WORK_MAX];

	// Thread의 리스트, Thread별 이벤트 동기화 오브젝트
	WorkerThread workerThreadList[THREAD_MAX];
	HANDLE workerEventList[THREAD_MAX];
	
	// Work에 관한정보 
	DWORD idxOfCurrentWork;  // 대기1순위 Work의 index
	DWORD idxOfLastAddedWork; // 새로추가될 Work의 index

	// # of Thread;
	DWORD threadIdx; //Pool에 존재하는 thread갯수
} gThreadPool;


//************************************************************//
//gThreadPool도 동시에 메모리에 접근해서 에러날 수 있으므로
// mutex로 동기화해준다.
//************************************************************//
static HANDLE mutex = NULL;

void InitMutex(void)
{
	mutex = CreateMutex(NULL, FALSE, NULL);
}

void DeInitMutex(void)
{
	BOOL ret = CloseHandle(mutex);
}

void AcquireMutex(void)
{
	DWORD ret = WaitForSingleObject(mutex, INFINITE);

	if(ret == WAIT_FAILED)
	{
		_tprintf( _T("Error Occur! \n") );
	}
}

void ReleaseMutex(void)
{
	BOOL ret = ReleaseMutex(mutex);

	if(ret == 0)
	{
		_tprintf( _T("Error Occur! \n") );
	}
}


//************************************************************//
// Thread Pool에 Work등록
// 
//************************************************************//
DWORD AddWorkToPool(WORK work)
{
	AcquireMutex();
	if(gThreadPool.idxOfLastAddedWork >= WORK_MAX)
	{
		_tprintf( _T("AddWorkToPool fail! \n"));
		return NULL;
	}

	
	gThreadPool.workList[gThreadPool.idxOfLastAddedWork++] = work;


	//대기중인 thread를 깨워 일시작 일 할당받은 thread제외하고는 다시 sleep
	for(DWORD i=0; i<gThreadPool.threadIdx; i++)
		SetEvent(gThreadPool.workerEventList[i]);

	ReleaseMutex();

	return 1;
}


//Thread에서 Work를 가져옴
WORK GetWorkFromPool()
{
	WORK work = NULL; 

	AcquireMutex();
	
	if(!(gThreadPool.idxOfCurrentWork < gThreadPool.idxOfLastAddedWork))
	{
		ReleaseMutex();
		return NULL;
	}
	
	work = gThreadPool.workList[gThreadPool.idxOfCurrentWork++];
	ReleaseMutex();

	return work;
}


//************************************************************//
// Thread Pool 생성
//************************************************************//
DWORD MakeThreadToPool(DWORD numOfThread)
{
	InitMutex();

	DWORD capacity = WORK_MAX - (gThreadPool.threadIdx);

	if (capacity < numOfThread)
		numOfThread = capacity;

	for(DWORD i = 0; i < numOfThread; i++)
	{
		DWORD idThread;
		HANDLE hThread;

		gThreadPool.workerEventList[gThreadPool.threadIdx] 
		= CreateEvent (NULL, FALSE, FALSE, NULL);

		hThread = CreateThread (
			NULL, 0,
			(LPTHREAD_START_ROUTINE) WorkerThreadFunction,
			(LPVOID)gThreadPool.threadIdx,
			0, &idThread
		);
		
		gThreadPool.workerThreadList[gThreadPool.threadIdx].hThread = hThread;
		gThreadPool.workerThreadList[gThreadPool.threadIdx].idThread = idThread;

		gThreadPool.threadIdx++;
	}
	
	return numOfThread; 
}


// 쓰레드의 main함수
void WorkerThreadFunction(LPVOID pParam)
{
	WORK workFunction;
	HANDLE event = gThreadPool.workerEventList[(DWORD)pParam];

	while(1)
	{
		workFunction = GetWorkFromPool();

		if(workFunction == NULL)
		{
			WaitForSingleObject(event, INFINITE);
			continue;
		}

		workFunction();
	}
}


// 각 thread가 할 일
void TestFunction()
{
	static int i = 0;
	i++;
	
	_tprintf( _T("Good Test --%d : Processing thread: %d--\n\n"), i, GetCurrentThreadId());
}

int _tmain(int argc, TCHAR* argv[])
{
	MakeThreadToPool(3);

	for(int i = 0; i<100; i++)
	{
		AddWorkToPool(TestFunction);
	}
	
	Sleep(50000);  //main thread가 먼저 없어지는 현상을 방지하기위한 장치

	return 0;
}

