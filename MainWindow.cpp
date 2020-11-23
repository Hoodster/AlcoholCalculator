#include "MainWindow.h"
#include "Controls.h"
#include <tchar.h>

Controls controls;

void MainWindow::DefineMainWindowControls(HWND hWnd, HINSTANCE hInstance) {
    HWND sexLabel = controls.CreateControl(_T("STATIC"), _T("Podaj p³eæ"), WS_CHILD | WS_VISIBLE, 30, 50, 150, 20, hWnd, hInstance);

    HWND maleRadio = controls.CreateControl(_T("BUTTON"), _T("Mê¿czyzna"), WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,
        150, 50, 100, 20, hWnd, hInstance, ID_SEXMALE);
    HWND femaleRadio = controls.CreateControl(_T("BUTTON"), _T("Kobieta"), WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
        250, 50, 100, 20, hWnd, hInstance, ID_SEXFEMALE);

    HWND ageLabel = controls.CreateControl(_T("STATIC"), _T("Wiek [lata]"), WS_CHILD | WS_VISIBLE, 75, 100, 150, 20,
        hWnd, hInstance);


    HWND weightLabel = controls.CreateControl(_T("STATIC"), _T("Waga [kg]"), WS_CHILD | WS_VISIBLE, 75, 150, 150, 20,
        hWnd, hInstance);
    HWND weightTextBox = controls.CreateControl(_T("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 175, 150, 150, 20,
        hWnd, hInstance, ID_WEIGHT);

    HWND heightLabel = controls.CreateControl(_T("STATIC"), _T("Wzrost [cm]"), WS_CHILD | WS_VISIBLE, 75, 200, 150, 20,
        hWnd, hInstance);
    HWND heightTextBox = controls.CreateControl(_T("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 175, 200, 150, 20,
        hWnd, hInstance, ID_HEIGHT);

    HWND confirmButton = controls.CreateControl(_T("BUTTON"), _T("Dalej"), WS_CHILD | WS_VISIBLE | WS_BORDER, 125, 250, 150, 20,
        hWnd, hInstance, ID_CONFIRM1);
}