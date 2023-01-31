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
  //wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // Цвет заливки фона.

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
  
  wchar_t str[40];

  switch (uMsg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;

    case WM_PAINT: {
      PAINTSTRUCT ps;
      RECT rect1, rect2;

      HDC hdc = BeginPaint(hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW+1));
        
        GetClientRect(hwnd, &rect1);
        DrawText(hdc, L"Win API, Uicode, gcc", -1, &rect1, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        
        wsprintf(str, L"Привет, %s", L"мир!");
        TextOut(hdc, 10, 10, str, wcslen(str));
        TextOut(hdc, 15, 18, str, wcslen(str));

        rect2.left = 50;
        rect2.top  = 55;
        rect2.right = 155;
        rect2.bottom = 100;
        UINT flags = DT_LEFT | DT_WORDBREAK; // DT_WORD_ELLIPSIS | DT_NOCLIP
        
        HFONT hFont, hOldFont; 

        hFont = (HFONT)GetStockObject(ANSI_VAR_FONT); 

        if (hOldFont = (HFONT)SelectObject(hdc, hFont)) {  
            //TextOut(hdc, 10, 50, L"Sample ANSI_VAR_FONT text", 25);        
            DrawTextExW(hdc, str, wsprintf(str, L"Изучение Win API\nУрок номер %d", 1), &rect2, flags, NULL);
            SelectObject(hdc, hOldFont); 
        }

        HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
        SelectObject(hdc, pen);
        MoveToEx(hdc, 50, 55, NULL);
        LineTo(hdc, 155, 55);
        LineTo(hdc, 155, 100);
        LineTo(hdc, 50, 100);
        LineTo(hdc, 50, 55);

      EndPaint(hwnd, &ps);
      return 0;
    }
  }
  // Передаём сообщение обработчику по умолчанию.
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
