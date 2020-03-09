//아래코드는 싱글코어에서만 의도한대로 작동함
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

int _tmain(int argc, TCHAR* argv[])
{
	SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);

	while(1)
	{
		for(DWORD i=0; i<10000; i++)
			for(DWORD i=0; i<10000; i++);


		_fputts(_T("Priority_low \n"), stdout); 
	}

	return 0;
}
