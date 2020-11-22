#include "MainWindow.h"

class MainWindow {
	WNDCLASSEX GetDefaultWindow(
		_In_ WNDPROC wndProc,
		_In_ TCHAR szWindowClass[],
		_In_ HINSTANCE hInstance
	) {
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = wndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
		wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = szWindowClass;

		return wcex;
	}
};
