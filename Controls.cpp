#include "Controls.h"

HWND Controls::CreateControl(LPCWSTR type, LPCWSTR text, DWORD styles, int x, int y, int width, int height, HWND hWnd, HINSTANCE hInstance, int id) {
    return CreateWindowEx(0, type, text, styles, x, y, width, height, hWnd, (HMENU)id, hInstance, NULL);
}

int Controls::GetNumberFromTextbox(HWND control) {
    wchar_t text[5];
    GetWindowTextW(control, text, 5);
    return _wtoi(text);
}

bool Controls::GetOptionsFromRadioButtonGroup(HWND window, int positiveOption, int negativeOption)
{
    if (IsDlgButtonChecked(window, positiveOption)) 
    {
        return true;
    }
    else if (IsDlgButtonChecked(window, negativeOption)) 
    {
        return false;
    }
}
