#include <Windows.h>
#define ID_SEXMALE 101
#define ID_SEXFEMALE 102
#define ID_WEIGHT 104
#define ID_HEIGHT 105
#define ID_CONFIRM1 106
#define ID_BEER 107
#define ID_VODKA 108
#define ID_WINE 109
#define ID_CONFIRM2 110
#define ID_STARTDRINK 111
#define ID_ENDDRINK 112
#define ID_CONFIRM3 113

#pragma once
class Controls
{
	public:
		HWND CreateControl(LPCWSTR type, LPCWSTR text, DWORD styles, int x, int y, int width, int height, HWND hWnd, HINSTANCE hInstance, int id = NULL);
		int GetNumberFromTextbox(HWND control);
		bool GetOptionsFromRadioButtonGroup(HWND window, int positiveOption, int negativeOption);
};

