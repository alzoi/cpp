// Привет, Мир! Unicode версия на Win API.
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
  if (*lpCmdLine != 0) {
    wchar_t cmd_buffer[1024];
    //swprintf_s(cmd_buffer, 1024, L"%s", lpCmdLine);
    _snwprintf_s(cmd_buffer, 1024, 1023, L"%s", lpCmdLine);
    MessageBoxW(NULL, cmd_buffer, L"Параметры командной строки", MB_ICONINFORMATION);
  }

  // Регистрируем класс окна.
  const wchar_t CLASS_NAME[]  = L"Win_Class_hello";
  WNDCLASS wc = { };

  wc.lpfnWndProc   = WindowProc;
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.hInstance     = hInstance;
  wc.lpszClassName = CLASS_NAME;
  wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // Цвет заливки фона.

  RegisterClass(&wc);

  // Создаём окно.
  HWND hwnd = CreateWindowEx(0,
    CLASS_NAME,
    L"Окно Win API",
    WS_OVERLAPPEDWINDOW, // Стиль окна.
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, // Размер и положение окна.
    NULL,
    NULL, // Меню отсутствует.
    hInstance,
    NULL
  );

  if (hwnd == NULL) {
      return 0;
  }

  ShowWindow(hwnd, nShowCmd);
  //UpdateWindow(hwnd);

  // Цикл обработки сообщений ОС.
  MSG msg = { };
  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return msg.wParam;
}

LRESULT CALLBACK WindowProc
(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  
  switch (uMsg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;

    case WM_PAINT: {
      PAINTSTRUCT ps;
      RECT rect;

      HDC hdc = BeginPaint(hwnd, &ps);
        //FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW+1));
        GetClientRect(hwnd, &rect);
        DrawText(hdc, L"Привет, мир!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
      EndPaint(hwnd, &ps);
      return 0;
    }
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
