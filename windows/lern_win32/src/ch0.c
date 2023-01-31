// Файл ch0.c
// gcc ch0.c -o ch0.exe -s -lkernel32 -luser32 -lgdi32 -mwindows -municode

#ifndef UNICODE
  #define UNICODE
#endif 

#ifndef _UNICODE
  #define _UNICODE
#endif 

#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain
(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {
  
  // В модальном окне выводим параметры командной строки.
  if (*lpCmdLine) {
    wchar_t cmd_buffer[1024];
    swprintf_s(cmd_buffer, 1024, L"%s", lpCmdLine);
    MessageBoxW(NULL, cmd_buffer, L"Сообщение", 0);
  }

  // Регистрируем класс окна.
  const wchar_t CLASS_NAME[]  = L"Sample Window Class";
  WNDCLASS wc = { };

  wc.lpfnWndProc   = WindowProc;
  wc.hInstance     = hInstance;
  wc.lpszClassName = CLASS_NAME;
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);

  RegisterClass(&wc);

  // Создаём окно.
  HWND hwnd = CreateWindowEx(
    0,
    CLASS_NAME,
    L"Learn to Program Windows",
    WS_OVERLAPPEDWINDOW,            // Стиль окна.
    // Размер и положение окна.
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    NULL,
    NULL, // Меню отсутствует.
    hInstance,
    NULL
  );

  if (hwnd == NULL) {
      return 0;
  }

  ShowWindow(hwnd, nShowCmd);
  UpdateWindow(hwnd);

  // Цикл обработки сообщений ОС.
  MSG msg = { };
  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}

LRESULT CALLBACK
WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  
  switch (uMsg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;

    case WM_PAINT: {
      PAINTSTRUCT ps;

      HDC hdc = BeginPaint(hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
      EndPaint(hwnd, &ps);
      
      return 0;
    }
    return 0;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
