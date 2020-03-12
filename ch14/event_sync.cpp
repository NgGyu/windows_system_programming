#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>    


unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);

TCHAR string[100];
HANDLE hEvent;

int _tmain(int argc, TCHAR* argv[])
{	
	HANDLE  hThread;
	DWORD dwThreadID;
// event object
	hEvent = CreateEvent(	
				NULL,		
				TRUE,		//manual reset mode
				FALSE,		//non-signaled로 생성
				NULL		
			 );	
	if(hEvent==NULL){
		_fputts(_T("Event object creation error \n"), stdout); 
		return -1;
	}
	
	hThread = (HANDLE)_beginthreadex (
						NULL, 0, 
						OutputThreadFunction, 
						NULL, 0, 
						(unsigned *)&dwThreadID
					);

	if(hThread==0) {
		_fputts(_T("Thread creation error \n"), stdout); 
		return -1;
	}	

	_fputts(_T("Insert string: "), stdout); 
	_fgetts(string, 30, stdin); //입력 받음, 버퍼에 채워짐

	SetEvent(hEvent);	// event를 signaled로 바꿔줌(출력 쓰레드에 입력 끝났다고 알림)

	WaitForSingleObject(hThread, INFINITE); //쓰레드 반환대기
		
 	CloseHandle(hEvent);	// event object 삭ㅈ
	CloseHandle(hThread);

    return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{

  WaitForSingleObject(hEvent, INFINITE); // event를 signaled로 바뀌는걸 기다림

  _fputts(_T("output string: "), stdout); 
  _fputts(string, stdout); 

  return 0;
}

