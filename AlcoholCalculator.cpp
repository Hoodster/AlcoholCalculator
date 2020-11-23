#include <Windows.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>
#include "Controls.h"
#include "ACCalc.h"
#include "MainWindow.h"
#include "AlcoholTypesWindow.h"
#include "ConsumptionTime.h"

LRESULT CALLBACK WndProc(HWND hWsnd, UINT message, WPARAM wParam, LPARAM lParam);
WNDCLASSEXW SetWindowOptions(HINSTANCE hInstance, LPCWSTR className);
HWND CreateNewWindow(LPCWSTR className, HINSTANCE hInstance, LPCWSTR windowName);

static TCHAR MainWindowClass[] = _T("MainWindow");
static TCHAR AlcoholWindowClass[] = _T("AlcoholWindow");
static TCHAR TimeWindowClass[] = _T("ConsuptionWindow");

static TCHAR AppName[] = _T("Alcohol calculator");
static TCHAR AlcoholMeasuresName[] = _T("Podaj iloœæ alkoholu");
static TCHAR AlcoholTime[] = _T("Podaj czas spo¿ycia");

struct model {
    bool sex;
    int age;
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
MainWindow mainWindow;
AlcoholTypesWindow alcoholTypes;
ConsumptionTime consumptionTime;
ACCalc ac;

int CALLBACK WinMain(
	HINSTANCE hInstance,
    HINSTANCE prevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
    _nCmdShow = nCmdShow;

    int ageLimitationState = MessageBox(NULL, _T("Program dla osób pe³noletnich"), _T("Ostrze¿enie"), MB_ICONWARNING);

    if (ageLimitationState != IDOK) {
        return 0;
    }

    HWND firstWindow = CreateNewWindow(MainWindowClass, hInstance, AppName);

    if (!firstWindow) {
       return 1;
    }

    mainWindow.DefineMainWindowControls(firstWindow, hInstance);
    
    ShowWindow(firstWindow, nCmdShow);
    UpdateWindow(firstWindow);

    secondWindow = CreateNewWindow(AlcoholWindowClass, hInstance, AlcoholMeasuresName);
    alcoholTypes.DefineAlcoholTypesWindowControls(secondWindow, hInstance);
    if (!secondWindow) {
        return 1;
    }

    thirdWindow = CreateNewWindow(TimeWindowClass, hInstance, AlcoholTime);
    consumptionTime.DefineConsumptionTimeWindowControls(thirdWindow, hInstance);
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
                    double alcoholAmount = ac.CalculateAlcoholConcentration(
                        data.sex,
                        data.age,
                        data.weight,
                        data.height,
                        data.beer,
                        data.vodka,
                        data.wine,
                        data.startHour,
                        data.endHour
                    );
                    break;
                default:
                    break;
            }
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
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

