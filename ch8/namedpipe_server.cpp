#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include <tchar.h>

#define BUF_SIZE 1024

int CommToClient(HANDLE);

int _tmain(int argc, TCHAR* argv[]) 
{
	LPTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe"); 

	HANDLE hPipe;
	
	while(1)
	{
		hPipe = CreateNamedPipe ( 
			pipeName,           //이름
			PIPE_ACCESS_DUPLEX,  //읽기쓰기가능    
			PIPE_TYPE_MESSAGE |   
			PIPE_READMODE_MESSAGE | PIPE_WAIT, //메시지주고받음(not binary)
			PIPE_UNLIMITED_INSTANCES,	//최대파이프갯수
			BUF_SIZE,                  //출력버퍼사이즈
			BUF_SIZE,                  //입력버퍼사이즈
			20000, //클라이언트 타임아웃
			NULL //보안속성
			);
	
		if (hPipe == INVALID_HANDLE_VALUE) 
		{
			_tprintf( _T("CreatePipe failed")); 
			return -1;
		}
  
		BOOL isSuccess; 
		isSuccess = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED); 
	
		if (isSuccess) 
			CommToClient(hPipe);
		else 
			CloseHandle(hPipe); 
		}
		return 1; 
} 

int CommToClient(HANDLE hPipe)
{ 
	TCHAR fileName[MAX_PATH];
	TCHAR dataBuf[BUF_SIZE];

	BOOL isSuccess;
	DWORD fileNameSize;

	isSuccess = ReadFile ( 
		hPipe,        //파이프핸들
		fileName,    //클라이언트가 열어달라고 요청한 파일이름
		MAX_PATH * sizeof(TCHAR), //버퍼사이즈
		&fileNameSize, //수신한 데이터 크기
		NULL);       

	if (!isSuccess || fileNameSize == 0) 
	{
		_tprintf( _T("Pipe read message error! \n") );
		return -1; 
	}

	FILE * filePtr = _tfopen(fileName, _T("r") );

	if(filePtr == NULL)
	{
		_tprintf( _T("File open fault! \n") );
		return -1; 
	}

	DWORD bytesWritten = 0;
	DWORD bytesRead = 0;

	while( !feof(filePtr) )
	{
		bytesRead = fread(dataBuf, 1, BUF_SIZE, filePtr);

		WriteFile ( 
			hPipe,			//파이프핸들
			dataBuf,			  //전송할 데이터 버퍼(파일의 내용이 담겨있다)
			bytesRead,		//전송할 데이처크기
			&bytesWritten,	//전송된 데이터크기
			NULL);	
		//크기가 다르면 에러
       if (bytesRead != bytesWritten)
		{
		    _tprintf( _T("Pipe write message error! \n") );
		    break; 
		}
	}

	FlushFileBuffers(hPipe); 
	DisconnectNamedPipe(hPipe); 
	CloseHandle(hPipe); 
	return 1;
}
