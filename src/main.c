#include <stdio.h>
#include <stdlib.h>

#include <windef.h>
#include <basetsd.h>
#include <winbase.h>
#include <winuser.h>
#include <shellapi.h>

const LPCWSTR class = L"nD3D8Server window class";
const LPCWSTR name = L" Nomads";

void message(LPCWSTR text, UINT type) {
	MessageBoxW(NULL, text, L"Project Nomads Cursor Fix", type);
}

int main(void) {
	// unbuffer stdout
	setvbuf(stdout, NULL, _IONBF, 0);

	HWND nomads = FindWindowW(class, name);

	if (!nomads) {
		HINSTANCE exeStatus = ShellExecuteW(NULL, NULL, L"nomads.exe", NULL, NULL, 0);

		if (exeStatus < (HINSTANCE)32) {
			printf("Failed to start nomads.exe: %d\n", exeStatus);
		} else {
			printf("Found nomads.exe and started it\n");
		}
	}

	for (int i = 10; i > 0 && !nomads; i--) {
		nomads = FindWindowW(class, name);
		printf("Couldn't find nomads :(\nTrying again %d more times\n", i);
		Sleep(1000);
	}

	if (!nomads) {
		printf("Couldn't find nomads :(\n");
		message(L"Couldn't find Project Nomads.", MB_ICONERROR);
		return -1;
	} else {
		printf("Found nomads :D\n");
	}

	RECT oldClip;
	GetClipCursor(&oldClip);

	WINDOWINFO wininfo;
	wininfo.cbSize = sizeof(WINDOWINFO);
	RECT newClip;

	while ((nomads = FindWindowW(class, name))) {
		if (!GetWindowInfo(nomads, &wininfo)) {
			printf("Couldn't get the window's infos\n");
			return -2;
		}
	
		newClip = wininfo.rcClient;

		if (wininfo.dwWindowStatus) {
			ClipCursor(&newClip);
		} else {
			ClipCursor(&oldClip);
		}
	
		Sleep(500);
	}

	printf("Nomads is gone! Shutting down\n");

	ClipCursor(&oldClip);

	return EXIT_SUCCESS;
}

