#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include <tchar.h>

int _tmain(int argc, TCHAR * argv[])
{
	SetEnvironmentVariable(_T("Good"), _T("morning"));
	SetEnvironmentVariable(_T("Hey"), _T("Ho!"));
	SetEnvironmentVariable(_T("Big"), _T("Boy"));
	
	STARTUPINFO si={0,};
	PROCESS_INFORMATION pi={0,};
	si.cb = sizeof(si);

	CreateProcess ( 
		NULL, _T("EnvChild"), NULL, NULL, FALSE,     
		CREATE_NEW_CONSOLE|CREATE_UNICODE_ENVIRONMENT,
		NULL,  
		NULL, &si, &pi    
	);

	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
	return 0; 
}
