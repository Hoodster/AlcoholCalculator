#include <Windows.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>
#include "Controls.h"

LRESULT CALLBACK WndProc(HWND hWsnd, UINT message, WPARAM wParam, LPARAM lParam);
WNDCLASSEXW SetWindowOptions(HINSTANCE hInstance, LPCWSTR className);
void DefineFirstWindowControls(HWND hWnd, HINSTANCE hInstance);
void DefineSecondWindowControls(HWND hWnd, HINSTANCE hInstance);
void DefineThirdWindowControls(HWND hWnd, HINSTANCE hInstance);
HWND CreateNewWindow(LPCWSTR className, HINSTANCE hInstance, LPCWSTR windowName);

static TCHAR MainWindow[] = _T("MainWindow");
static TCHAR AlcoholWindow[] = _T("AlcoholWindow");
static TCHAR TimeWindow[] = _T("ConsuptionWindow");

static TCHAR AppName[] = _T("Alcohol calculator");
static TCHAR AlcoholMeasuresName[] = _T("Podaj iloœæ alkoholu");
static TCHAR AlcoholTime[] = _T("Podaj czas spo¿ycia");

struct model {
    bool sex;
    int weight;
    int height;
    int beer;
    int wine;
    int vodka;
    int startHour;
    int endHour;
} data;

HWND secondWindow;
HWND thirdWindow;
int _nCmdShow;
Controls controls;

int CALLBACK WinMain(
	HINSTANCE hInstance,
    HINSTANCE prevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
    _nCmdShow = nCmdShow;

    int ageLimitationState = MessageBox(NULL, _T("Program dla osób pe³noletnich"), _T("Ostrze¿enie"), NULL);

    if (ageLimitationState != IDOK) {
        return 0;
    }

    HWND firstWindow = CreateNewWindow(MainWindow, hInstance, AppName);

    if (!firstWindow) {
       return 1;
    }

    DefineFirstWindowControls(firstWindow, hInstance);
    
    ShowWindow(firstWindow, nCmdShow);
    UpdateWindow(firstWindow);

    secondWindow = CreateNewWindow(AlcoholWindow, hInstance, AlcoholMeasuresName);
    DefineSecondWindowControls(secondWindow, hInstance);
    if (!secondWindow) {
        return 1;
    }

    thirdWindow = CreateNewWindow(TimeWindow, hInstance, AlcoholTime);
    DefineThirdWindowControls(thirdWindow, hInstance);
    if (!thirdWindow) {
        return 1;
    }

    MSG message;

    while (GetMessage(&message, nullptr, 0, 0))
    {
       TranslateMessage(&message);
       DispatchMessage(&message);
    }

    return (int)message.wParam;
}

void DefineFirstWindowControls(HWND hWnd, HINSTANCE hInstance) {
    HWND sexLabel = controls.CreateControl(_T("STATIC"), _T("Podaj p³eæ"), WS_CHILD | WS_VISIBLE, 30, 50, 150, 20, hWnd, hInstance);

    HWND maleRadio = controls.CreateControl(_T("BUTTON"), _T("Mê¿czyzna"), WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,
        150, 50, 100, 20, hWnd, hInstance, ID_SEXMALE);
    HWND femaleRadio = controls.CreateControl(_T("BUTTON"), _T("Kobieta"), WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
        250, 50, 100, 20, hWnd, hInstance, ID_SEXFEMALE);

    HWND ageLabel = controls.CreateControl(_T("STATIC"), _T("Wiek [lata]"), WS_CHILD | WS_VISIBLE, 75, 100, 150, 20,
        hWnd, hInstance);
    HWND ageTextBox = controls.CreateControl(_T("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 175, 100, 150, 20,
        hWnd, hInstance, ID_AGE);
    
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

void DefineSecondWindowControls(HWND hWnd, HINSTANCE hInstance) {

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

void DefineThirdWindowControls(HWND hWnd, HINSTANCE hInstance) {
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

HWND CreateNewWindow(LPCWSTR className, HINSTANCE hInstance, LPCWSTR windowName) {
    WNDCLASSEXW windowOpt = SetWindowOptions(hInstance, className);

    if (!RegisterClassExW(&windowOpt)) {
        MessageBox(NULL, _T("Wyst¹pi³ b³¹d inicjalizacji"), _T("B³¹d"), NULL);
        return NULL;
    }

    return  CreateWindow(
        className,
        windowName,
        WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 350,
        NULL,
        NULL,
        hInstance,
        NULL
    );
}

WNDCLASSEXW SetWindowOptions(HINSTANCE hInstance, LPCWSTR className) {
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = 0;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = className;
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    return wcex;
}

LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
) {
    switch (message) {
        case WM_COMMAND:
            switch (wParam) {
                case ID_CONFIRM1:
                    ShowWindow(secondWindow, _nCmdShow);
                    UpdateWindow(secondWindow);
                    break;
                case ID_CONFIRM2:
                    ShowWindow(thirdWindow, _nCmdShow);
                    UpdateWindow(thirdWindow);
                    break;
                case ID_CONFIRM3:
                    MessageBox(NULL, _T("Wyst¹pi³ b³¹d inicjalizacji"), _T("B³¹d"), NULL);
                    break;
                default:
                    break;
            }
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            //PostQuitMessage(12432);
            break;
        case WM_CTLCOLORSTATIC:
            SetBkMode((HDC)wParam, TRANSPARENT);
            return (LRESULT)GetStockObject(LTGRAY_BRUSH);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
    }
}

