#include <Windows.h>
#include <tchar.h>

class MainWindow
{
	public:
		WNDCLASSEX GetDefaultWindow(
			_In_ WNDPROC wndProc,
			_In_ TCHAR szWindowClass[],
			_In_ HINSTANCE hInstance
		);
};

