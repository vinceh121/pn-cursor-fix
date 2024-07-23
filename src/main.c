#include <stdio.h>
#include <stdlib.h>

#include <windef.h>
#include <basetsd.h>
#include <winbase.h>
#include <winuser.h>

const LPCWSTR class = L"nD3D8Server window class";
const LPCWSTR name = L" Nomads";

int main(void) {
	HWND nomads = FindWindowW(class, name);

	if (!nomads) {
		printf("Couldn't find nomads :(\n");
		return -1;
	}

	WINDOWINFO wininfo;
	wininfo.cbSize = sizeof(WINDOWINFO);

	if (!GetWindowInfo(nomads, &wininfo)) {
		printf("Couldn't get the window's infos\n");
		return -2;
	}

	RECT newClip = wininfo.rcClient;

	printf("Nomads window: %d, %d, %d, %d\n", newClip.left, newClip.top, newClip.right, newClip.bottom);

	RECT oldClip;
	GetClipCursor(&oldClip);

	while ((nomads = FindWindowW(class, name))) {
		ClipCursor(&newClip);
		Sleep(500);
	}

	printf("Nomads is gone! Shutting down\n");

	ClipCursor(&oldClip);

	return EXIT_SUCCESS;
}

