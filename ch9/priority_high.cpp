//아래코드는 싱글코어에서만 의도한대로 작동함
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO siNORMAL={0,};
	PROCESS_INFORMATION piNORMAL;
	TCHAR commandOne[]=_T("NORMAL_PRIORITY_CLASS.exe");

	STARTUPINFO siBELOW={0,};
	PROCESS_INFORMATION piBELOW;
	TCHAR commandTwo[]=_T("BELOW_NORMAL_PRIORITY_CLASS.exe");
	
	siNORMAL.cb=sizeof(siNORMAL);
	siBELOW.cb=sizeof(siBELOW);

	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);

	CreateProcess(NULL, commandOne,
				  NULL, NULL, TRUE, 
				  0, NULL, NULL, 
				  &siNORMAL, &piNORMAL
	);  

	CreateProcess(NULL, commandTwo,
				  NULL, NULL, TRUE, 
				  0, NULL, NULL, 
				  &siBELOW, &piBELOW
	); 

	while(1)
	{
		Sleep(10); //이 프로세스가 Blocked상태로 바뀜 => 대기중이던 낮은우선순위의 프로세스가 실행가능해진다
		_fputts(_T("Priority_high \n"), stdout); 
	}

	return 0;
}
