#include "ConsumptionTime.h"
#include <tchar.h>

void ConsumptionTime::DefineConsumptionTimeWindowControls(HWND hWnd, HINSTANCE hInstance)
{
    HWND drinkStartLabel = controls.CreateControl(_T("STATIC"), _T("Zacz¹³em/am piæ o [h]"), WS_CHILD | WS_VISIBLE, 70, 50, 170, 20,
        hWnd, hInstance);
    HWND drinkStartTextBox = controls.CreateControl(_T("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 50, 50, 20,
        hWnd, hInstance, ID_STARTDRINK);

    HWND drinkEndLabel = controls.CreateControl(_T("STATIC"), _T("Skoñczy³em/am piæ o [h]"), WS_CHILD | WS_VISIBLE, 70, 100, 170, 20,
        hWnd, hInstance);
    HWND drinkEndTextBox = controls.CreateControl(_T("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 100, 50, 20,
        hWnd, hInstance, ID_ENDDRINK);

    HWND confirmButton = controls.CreateControl(_T("BUTTON"), _T("Podsumuj"), WS_CHILD | WS_VISIBLE | WS_BORDER, 105, 150, 150, 20,
        hWnd, hInstance, ID_CONFIRM3);
}
