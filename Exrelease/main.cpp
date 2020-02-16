#include <Windows.h>
#include <stdio.h>

typedef BOOL(*SetHook)();
typedef BOOL(*UnHook)();


BOOL HookAndUnhook() {
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
		return FALSE;
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
		return FALSE;
	}
	system("pause");
	return TRUE;
}
int main(int argc, char* argv[]) {

	HRSRC hRsrc = FindResource(0, (LPCWSTR)101, L"MYDLL");
	DWORD dw = GetLastError();
	DWORD dwSize = SizeofResource(NULL, hRsrc);
	HGLOBAL hGlobal = LoadResource(NULL, hRsrc);
	LPVOID lpVoid = LockResource(hGlobal);
	FILE* fp = NULL;
	fopen_s(&fp, "GlobalHool.dll", "wb+");
	fwrite(lpVoid, sizeof(char), dwSize, fp);
	fclose(fp);
	HookAndUnhook();
	return 0;

}