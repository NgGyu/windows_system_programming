//아래코드는 싱글코어에서만 의도한대로 작동함
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

int _tmain(int argc, TCHAR* argv[])
{
	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);

	while(1)
	{

		Sleep(10); //이 프로세스가 Blocked상태로 바뀜 => 대기중이던 낮은우선순위의 프로세스가 실행가능해진다

		_fputts(_T("Priority_normal \n"), stdout); 
	}

	return 0;
}

