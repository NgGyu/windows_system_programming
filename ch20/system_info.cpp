#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include <tchar.h>

int _tmain(int argc, TCHAR* argv[]) 
{
	SYSTEM_INFO si;
	DWORD allocGranularity;
	DWORD pageSize;

	GetSystemInfo(&si);
	pageSize = si.dwPageSize;
	allocGranularity = si.dwAllocationGranularity;

	_tprintf( _T("Page size: %u Kbyte \n"), pageSize/1024);
	_tprintf( _T("Allocation granularity: %u Kbyte \n"), allocGranularity/1024);

	return 1; 
} 

