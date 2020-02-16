#include <Windows.h>
#include <stdio.h>

typedef BOOL(*SetHook)();
typedef BOOL(*UnHook)();


int main(int argc,char* argv[]) {

	HMODULE hModule = LoadLibrary(L"GlobalHool.dll");
	SetHook sethook = (SetHook)GetProcAddress(hModule, "SetGlobalHook");
	UnHook unhook = (UnHook)GetProcAddress(hModule, "UnsetGlobalHook");
	printf("GetProcAddress Error[%d]\n", ::GetLastError());
	if (sethook())
	{
		printf("SetGlobalHook OK\n");
	}
	else
	{
		printf("SetGlobalHook Error\n");
		return 1;
	}

	system("pause");

	if (unhook())
	{
		printf("UnSetGlobalHook OK\n");
		system("pause");
	}
	else
	{
		printf("UnSetGlobalHook Error\n");
		return 1;
	}
	return 0;
}