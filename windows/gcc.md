# Установка компилятора на Windows

## msys2.org
Скачиваем компилятор
https://github.com/msys2/msys2-installer/releases/download/2022-06-03/msys2-x86_64-20220603.exe
После установки, в окне msys2 даём команды для установки библиотек и инструментов:
```
pacman -Syu
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
```
В переменные окружения добавляем:
```
C:\msys64\mingw64\bin
C:\msys64\usr\bin
```

## MingW-W64-builds
Идём на сайт https://gcc.gnu.org/install/binaries.html  

Открываем ссылку [mingw-w64](https://www.mingw-w64.org/downloads/)  
Открываем ссылку [MingW-W64-builds](https://github.com/niXman/mingw-builds-binaries/releases)  

Для 64-битной версии ОС выбираем [x86_64-12.2.0-release-win32-seh-ucrt-rt_v10-rev2.7z](https://github.com/niXman/mingw-builds-binaries/releases/download/12.2.0-rt_v10-rev2/x86_64-12.2.0-release-win32-seh-ucrt-rt_v10-rev2.7z)  
Это компилятор без поддержки устаревших функций многопоточности С++11, обработкой исключений [seh](https://learn.microsoft.com/en-us/cpp/cpp/structured-exception-handling-c-cpp?view=msvc-170) (Structured Exception Handling, используется в Windows) и универсальной средой выполнения кода C [ucrt](https://support.microsoft.com/en-us/topic/update-for-universal-c-runtime-in-windows-c0514201-7fe6-95a3-b0a5-287930f3560c).

Архив распаковываем в папку **C:\mingw64** и в системную переменную Path добавляем ссылку на папку **C:\mingw64\bin**

Запускаем [cmd](https://learn.microsoft.com/ru-ru/windows-server/administration/windows-commands/cmd) и проверяем версию компилятора
```
g++ --version
```

С сайта https://www.gnu.org/software/make/#download скачиваем исходники утилиты [make](https://ftp.gnu.org/gnu/make/make-4.4.tar.lz).
Распаковываем исходники в папку C:\mingw64\bin\make-4.4
В cmd из папки с исходниками make даём команду установки
 ```
 .\build_w32.bat gcc
```

Добавляем в системную переменную Path папку **C:\mingw64\bin\make-4.4\GccRel**  
Файл **gnumake.exe** можно переименовать в **make.exe**
В сmd проверяем версию
```
make --version
```
## gcc
[GCC Command Options](https://gcc.gnu.org/onlinedocs/gcc/Invoking-GCC.html)  

## Hello World Win32
Создаём папку для объектных файлов
```
mkdir obj
```
Файл Makefile
```make
all: app.exe

app.exe: obj/main.o
	gcc -o app.exe obj/main.o -s -lcomctl32 -Wl,--subsystem,windows

obj/main.o: main.c
	gcc -std=c99 -D UNICODE -D _UNICODE -D _WIN32_IE=0x0500 -D WINVER=0x500 -Wall -c main.c -o obj/main.o
```
Файл main.c
```c
#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <commctrl.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Sample Window Class";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows 世界你好!",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
            EndPaint(hwnd, &ps);
        }
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
```

