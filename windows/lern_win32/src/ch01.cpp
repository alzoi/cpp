// g++.exe -Wall -O2 -c ch01.cpp -o ch01.o
// g++.exe ch01.o -s -lgdi32 -luser32 -lkernel32 -lcomctl32 -luxtheme -mwindows -o ch01.exe

#define UNICODE

#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <windows.h>
#include <commctrl.h>
#include <uxtheme.h>
#include <string>
#include <tchar.h>
#include <stdio.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

HINSTANCE hApp;

HWND hWinMain,
    hEdit1,
    hEdit2,
    hBut1,
    hBut2;

const int ID_Edit1 = 1,
          ID_Edit2 = 2,
          ID_But1 = 3,
          ID_But2 = 4;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

  hApp = hInstance;

  HICON icon = LoadIcon(NULL, IDI_APPLICATION);

  INITCOMMONCONTROLSEX icc;
  icc.dwSize = sizeof(icc);
  icc.dwICC = ICC_WIN95_CLASSES | ICC_STANDARD_CLASSES;
  InitCommonControlsEx(&icc);

  WNDCLASSEX wc{
      .cbSize = sizeof(WNDCLASSEX),
      .style = CS_HREDRAW | CS_VREDRAW,
      .lpfnWndProc = WindowProcedure,
      .hInstance = hInstance,
      .hIcon = icon,
      .hCursor = LoadCursor(NULL, IDC_ARROW),
      .hbrBackground = (HBRUSH)(COLOR_WINDOW), // COLOR_WINDOWFRAME), // Дескриптор для кисти фона
      .lpszClassName = szClassName,
      .hIconSm = icon};

  if (!RegisterClassEx(&wc))
  {
    return 1;
  }

  hWinMain = CreateWindowExW(WS_EX_WINDOWEDGE, wc.lpszClassName, _T("Шаблон Template124"),
                             WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_VISIBLE,
                             100, 100, 544, 375,
                             HWND_DESKTOP, // Родительское окно.
                             NULL, wc.hInstance, NULL);

  // Получаем Стандартный шрифт.
  NONCLIENTMETRICS ncm;
  ncm.cbSize = sizeof(NONCLIENTMETRICS);
  SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
  // Создаём логический шрифт (описание) по дескриптору шрифта строки заголовка.
  HFONT hFont = ::CreateFontIndirect(&ncm.lfCaptionFont);

  hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T("Привет 123"),
                          WS_VISIBLE | WS_CHILD | ES_LEFT,
                          50, 50, 380, 25,
                          hWinMain,
                          (HMENU)ID_Edit1, hApp, NULL);

  hEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""),
                          WS_VISIBLE | WS_CHILD | ES_LEFT,
                          50, 250, 380, 25,
                          hWinMain,
                          (HMENU)ID_Edit2, hApp, NULL);

  SendMessage(hEdit1, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

  hBut1 = CreateWindowEx(0, _T("BUTTON"), _T("Передать"),
                         WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                         // BS_PUSHBUTTON | WS_CHILDWINDOW | WS_VISIBLE | WS_TABSTOP | BS_TEXT, // | BS_FLAT,
                         200, 100, 75, 23,
                         hWinMain,
                         (HMENU)ID_But1, hApp, NULL);

  // Отправляем сообщение оконной процедуре окна-кнопки для установки указанного шрифта.
  SendMessage(hBut1, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

  // SetWindowTheme(hBut1, L" ", L" "); // Отключить тему

  hBut2 = CreateWindowEx(0, _T("BUTTON"), _T("Закрыть"),
                         WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                         200, 200, 75, 23,
                         hWinMain,
                         (HMENU)ID_But2, (HINSTANCE)GetWindowLongPtr(hWinMain, GWLP_HINSTANCE), NULL);
  SendMessage(hBut2, WM_SETFONT, (WPARAM)hFont, TRUE);

  // ShowWindow(hwnd_main, nCmdShow);

  MSG messages = {0};
  while (GetMessage(&messages, NULL, 0, 0))
  {
    TranslateMessage(&messages);
    DispatchMessage(&messages);
  }

  return messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_COMMAND:
    if (LOWORD(wParam) == ID_But1)
    {
      TCHAR input[101];
      GetWindowText(hEdit1, input, 100);
      SetWindowText(GetDlgItem(hWinMain, ID_Edit2), input);
    }
    break;

  case WM_CREATE:
    // hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T("Привет 123"),
    //                         WS_VISIBLE | WS_CHILD | ES_LEFT,
    //                         50, 50, 380, 25,
    //                         hwnd,
    //                         ID_Edit1, hApp, NULL);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  default:
    return DefWindowProc(hwnd, message, wParam, lParam);
  }

  return 0;
}
