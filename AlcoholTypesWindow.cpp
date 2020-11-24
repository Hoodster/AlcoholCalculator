#include "AlcoholTypesWindow.h"
#include <tchar.h>

void AlcoholTypesWindow::DefineAlcoholTypesWindowControls(HWND hWnd, HINSTANCE hInstance) {

    HWND beerLabel = controls.CreateControl(_T("STATIC"), _T("Piwo (500ml) 5% [ml]"), WS_CHILD | WS_VISIBLE, 105, 50, 150, 20,
        hWnd, hInstance);
    HWND beerTextBox = controls.CreateControl(_T("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 50, 50, 20,
        hWnd, hInstance, ID_BEER);

    HWND vodkatLabel = controls.CreateControl(_T("STATIC"), _T("Wódka (40ml) 40% [ml]"), WS_CHILD | WS_VISIBLE, 105, 100, 150, 20,
        hWnd, hInstance);
    HWND vodkaTextBox = controls.CreateControl(_T("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 100, 50, 20,
        hWnd, hInstance, ID_VODKA);

    HWND wineLabel = controls.CreateControl(_T("STATIC"), _T("Wino (100ml) 11% [ml]"), WS_CHILD | WS_VISIBLE, 105, 150, 150, 20,
        hWnd, hInstance);
    HWND wineTextBox = controls.CreateControl(_T("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 150, 50, 20,
        hWnd, hInstance, ID_WINE);

    HWND confirmButton = controls.CreateControl(_T("BUTTON"), _T("Dalej"), WS_CHILD | WS_VISIBLE | WS_BORDER, 105, 250, 150, 20,
        hWnd, hInstance, ID_CONFIRM2);
}