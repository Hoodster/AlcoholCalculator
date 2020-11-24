# AlcoholCalculator

# Uruchomienie
Do uruchomienia potrzebne jest Visual Studio. Można pobrać za darmo community edition. Dodatkowo trzeba doinstalować narzędzia do budowy aplikacji desktopowych C++.
![image](https://cis-linux2.temple.edu/~sallyk/cis1057/00_IDE/VSC_setup_files/Tutorial-Installing-C.png)

Po uruchomieniu projektu wystarczy wcisnąć debugowanie (zielona strzałka) na górnej belce aplikacji.

### Dosyć istotne. W folderze projektu usuń ukryty folder `.git`

# Pliki
- `AlcoholCalculator.cpp` - plik wykonywalny programu, zawiera definicje okien oraz zarządzanie ich stanem
- `Controls.cpp/.h` - klasa do obsługi tworzenia kontrolek
- `ACCalc.cpp/.h` - klasa do obsługi liczenia promili we krwi
- `(MainWindow/AlcoholTypes/ConsumptionTime).cpp/.h` - klasy do definicji kontrolek

## AlcoholCalculator.cpp

1. Pobranie zależności
```
#include ...
...
#include "Controls.h" - zależności stworzone przez nas pobieramy z pliku nagłówkowego
```

2. Zdefiniowanie wartości tekstowych
```
static TCHAR MainWindowClass[] = _T("MainWindow");
static TCHAR AlcoholWindowClass[] = _T("AlcoholWindow");
static TCHAR TimeWindowClass[] = _T("ConsuptionWindow"); // nazwy klas (nie muszą się pokrywać z zależnościami wobec tych klas, służą do rozróżniania procesów przez procesor)

static TCHAR AppName[] = _T("Alcohol calculator");
static TCHAR AlcoholMeasuresName[] = _T("Podaj ilość alkoholu");
static TCHAR AlcoholTime[] = _T("Podaj czas spożycia"); // tytuły okna
```

3. Stworzenie struktury modelu gdzie przypisywane są wartości
```
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
```

4. Zmienne globalne przypisywane w WinMain() a które będziemy też wykorzystywać w innych funkcjach
```
HWND secondWindow;
HWND thirdWindow;
int _nCmdShow;
```

5. Tworzenie wystąpień pobranych klas z plików nagłówkowych (invoking)
```
Controls controls;
MainWindow mainWindow;
AlcoholTypesWindow alcoholTypes;
ConsumptionTime consumptionTime;
ACCalc ac;
```

### WinMain - funkcja budująca aplikację i będąca jej głównym procesem
```
int CALLBACK WinMain(
	HINSTANCE hInstance,
    HINSTANCE prevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
    _nCmdShow = nCmdShow; //przypisanie wartości do zmiennej globalnej
    
```
Tworzenie monitu o ograniczeniu wiekowym, makro `_T()` pozwala nam obsługiwać kodowanie UNICODE, bez tego zamiast tekstu pojawiłyby się chińskie znaczki. 
Dodatkowo dodany `MB_ICONWARNING` tak że obok tekstu mamy żółty trójkąt z wykrzyknikiem.
```
    int ageLimitationState = MessageBox(NULL, _T("Program dla osób pełnoletnich"), _T("Ostrzeżenie"), MB_ICONWARNING);

    if (ageLimitationState != IDOK) { //jeśli wciśnięto coś innego niż ok, zamknięcie aplikacji
        return 0;
    }
```
Przykład tworzenia i zdefiniowania okna.
```
    HWND firstWindow = CreateNewWindow(MainWindowClass, hInstance, AppName); // tworzenie instancji nowego okna

    if (!firstWindow) { // sprawdzanie czy okno jest różne od NULL
       return 1;
    }

    mainWindow.DefineMainWindowControls(firstWindow, hInstance); //zdefiniowanie kontrolek przy użyciu funkcji z `MainWindow.cpp/.h`
    
    ShowWindow(firstWindow, nCmdShow);
    UpdateWindow(firstWindow); // funkcje budujące i pokazujące okno
```
Tworzymy kolejkę sygnałów, aplikacja odpowiada na każdą akcję którą będziemy obsługiwać przez `WinProc`. Bardzo ważne żeby była w pętli WHILE tak aby działa bez przerwy w tle.
```
    MSG message;

    while (GetMessage(&message, nullptr, 0, 0))
    {
       TranslateMessage(&message);
       DispatchMessage(&message);
    }

    return (int)message.wParam;
}
```

### CreateNewWindow - tworzy ustawienia okna i jego model
```
HWND CreateNewWindow(LPCWSTR className, HINSTANCE hInstance, LPCWSTR windowName) {
    WNDCLASSEXW windowOpt = SetWindowOptions(hInstance, className); // zbudowanie ustawień okna (funkcja własna opisana poniżej)

    if (!RegisterClassExW(&windowOpt)) { // sprawdzamy czy przyjęto wszystkie wartości jako poprawne, jeśli nie wyświetlamy monit o błędzie i zamykamy
        MessageBox(NULL, _T("Wystąpił błąd inicjalizacji"), _T("Błąd"), NULL);
        return NULL;
    }

    return  CreateWindow(
        className,
        windowName,
        WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, // style okna, zablokowanie rozszerzania okna, ma stałą wartość
        CW_USEDEFAULT, CW_USEDEFAULT, // domyślne ułożenie okna na ekranie
        400, 350, // szerokość i wysokość okna
        NULL,
        NULL,
        hInstance,
        NULL
    ); // tworzenie obiektu okna 
}
```

### SetWindowOptions - tworzenie najbardziej standardowych ustawień okna, nie ma dodatkowych parametrów bo raczej nam niepotrzebne,
`wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);` - ustawia tło okna na jasnoszare

### WndProc - obsługa stanu aplikacji
Obsługa komendy interakcji z przyciskiem posiadającym ID `ID_CONFIRM1` otwierającej nowe okno.
```
    switch (message) {
        case WM_COMMAND:
            switch (wParam) {
                case ID_CONFIRM1:
                    data.sex = controls.GetOptionsFromRadioButtonGroup(hWnd, ID_SEXMALE, ID_SEXFEMALE); // pobieranie wybranego buttona z radio buttonów
                    data.weight = controls.GetNumberFromTextbox(GetDlgItem(hWnd, ID_WEIGHT)); // pobieranie danych z kontrolki wagi 
                    ShowWindow(secondWindow, _nCmdShow);
                    UpdateWindow(secondWindow);
                    break;
```
```
        case WM_CTLCOLORSTATIC: // ustawienie "przezroczystego" tła dla kontrolek
            SetBkMode((HDC)wParam, TRANSPARENT); // kolor boxa wychodzącego poza kontrolkę
            return (LRESULT)GetStockObject(LTGRAY_BRUSH); //tło samej kontrolki (bez tego tekst miałby białe tło mimo linijki wyżej
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam); // pętla na kolejkę procesów
            break;
```

## Controls.cpp/.h
Ogólnie klasy mają dwa pliki - nagłówkowe (.h) zawierające definicje klas, co jest publiczne a co prywatne, etc. oraz implementacyjne (.cpp) 
implementujące rozwiązania dla tych zdefiniowanych klas. Oczywiście korzystamy potem z pliku nagłówkowego ponieważ to on wie co ma być prywatne a co nie.

### (.cpp) CreateControl - okraja funkcję `CreateWindowEx` z parametrów których nigdy nie wypełniamy wstawiając tam domyślną wartość dla nas a zostawiając 
do wypełnienia wszystkie liczące się dla nas parametry
```
HWND Controls::CreateControl(LPCWSTR type, LPCWSTR text, DWORD styles, int x, int y, int width, int height, HWND hWnd, HINSTANCE hInstance, int id) {
    return CreateWindowEx(0, type, text, styles, x, y, width, height, hWnd, (HMENU)id, hInstance, NULL);
}
```
### (.cpp) GetNumberFromTextbox - Głównie korzystamy z wartości liczbowych, ta funkcja bierze kontrolkę, ustawia długość znaków na 5 (wątpię żeby ktoś miał więcej wartości do wpisania) 
i przypisuje wartość kontrolki zmiennej `text` a następnie konwertuje tekst na int.
```
int Controls::GetNumberFromTextbox(HWND control) {
    wchar_t text[5];
    GetWindowTextW(control, text, 5);
    return _wtoi(text);
}
```

### (.cpp) GetOptionsFromRadioButtonGroup - Determinujemy który radio button jest kliknięty. Ustalamy pozytywny scenariusz dla którego zwrócimy 1 (true) i negatywny dla którego zwrócimy 0 (false)
```
bool Controls::GetOptionsFromRadioButtonGroup(HWND window, int positiveOption, int negativeOption)
{
    if (IsDlgButtonChecked(window, positiveOption)) // sprawdzanie czy przycisk o danym ID ma stan "checked"
    {
        return true;
    }
    else if (IsDlgButtonChecked(window, negativeOption)) 
    {
        return false;
    }
}
```

### (.h) Zdefiniowanie id wszystkich kontrolek
```
#define ID_VODKA 108
#define ID_WINE 109
#define ID_CONFIRM2 110
#define ID_STARTDRINK 111
#define ID_ENDDRINK 112
#define ID_CONFIRM3 113
```

## ACCalc.cpp/.h - (A)lcohol (C)oncentration (Calc)ulator - właściwe obliczenia stężenia alkoholu we krwi
Raczej nie będę się rozpisywał. To są typowo matematyczne funkcje, nie ma nic specyficznego dla programowania czy WinAPI

### (.cpp) CalculateAlcoholConcentration - właściwa funkcja licząca stężenie, jedyna publiczna

### (.cpp) CalculateBMIFluidWeight - funkcja pomocnicza licząca dodatkową/ujemną wagę płynów w zależności od BMI

### (.cpp) CalculateAlcoholFillOverTime - funkcja pomocnicza licząca przypływ gramów alkoholu do krwi w czasie.

## MainWindow.cpp/.h - definiowanie okna (przykładowe pliki, reszta adekwatna)

### DefineMainWindowControls - definiowanie kontrolek dla pierwszego okna

Zdefiniowane po kolei: opis wejścia danych (label) oraz sama kontrolka. Typ kontrolki zależny od pierwszego parametru.
Co do liczb na końcu są to po kolei: _położenie x, położenie y (względem okna), szerokość, wysokość_.
Jako ostatni parametr opcjonalne ID. W pliku nagłówkowym opisane jako `.., id = NULL)`.
```
    HWND weightLabel = controls.CreateControl(_T("STATIC"), _T("Waga [kg]"), WS_CHILD | WS_VISIBLE, 75, 150, 150, 20,
        hWnd, hInstance);
    HWND weightTextBox = controls.CreateControl(_T("EDIT"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 175, 150, 150, 20,
        hWnd, hInstance, ID_WEIGHT);
```
