#include "Controls.h"

HWND Controls::CreateControl(LPCWSTR type, LPCWSTR text, DWORD styles, int x, int y, int width, int height, HWND hWnd, HINSTANCE hInstance, int id) {
    return CreateWindowEx(0, type, text, styles, x, y, width, height, hWnd, (HMENU)id, hInstance, NULL);
}