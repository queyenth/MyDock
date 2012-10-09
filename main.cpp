/*
TODO: Popup menu like that:
 - Add new icon
 - Delete this icon
 - MyDock settings
*/

#include "MyDock.hpp"

#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <windowsx.h>

MyDock *dock = new MyDock(0, 0);

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch(uMsg) {
    case WM_PAINT:
      dock->Draw(hwnd);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
      dock->OnClick(GET_X_LPARAM(lParam), uMsg);
      break;
    case WM_MOUSEMOVE:
        dock->OnMove(GET_X_LPARAM(lParam));
    default:
      return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }
  return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  WNDCLASS wc;
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = (WNDPROC)WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = (HICON)LoadImage(hInstance,
    "C:\\Users\\oveRan\\Desktop\\dev\\MyDock\\mydock.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = (char *)"MyDock";
  
  if (!RegisterClass(&wc))
    return 1;
  HWND hWnd;
  hWnd = CreateWindowEx(WS_EX_APPWINDOW, (char *)"MyDock",
    (char *)"MyDock", WS_POPUP, MyDock::x, MyDock::y,
    MyDock::width, MyDock::height, NULL, NULL, hInstance, NULL);
  if (!hWnd)
    return 1;

  ShowWindow(hWnd, SW_SHOW);
  UpdateWindow(hWnd);

  MSG msg;
  POINT mousePoint;
  dock->InitSettings(hWnd);
  while (true) {
    GetCursorPos(&mousePoint);
    if (GetMessage(&msg, NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else if ((mousePoint.x > MyDock::x && mousePoint.x < MyDock::x+MyDock::width) &&
        (mousePoint.y > MyDock::y && mousePoint.y < MyDock::y+MyDock::height)) {
      SetWindowPos(hWnd, HWND_TOPMOST,
        MyDock::x, MyDock::y, MyDock::width, MyDock::height, SWP_SHOWWINDOW);
      dock->Draw(hWnd);
    }
    else {
      SetWindowPos(hWnd, HWND_BOTTOM,
        MyDock::x, MyDock::y, MyDock::width, MyDock::height, SWP_SHOWWINDOW);
    }
  }

  delete dock;
  return (msg.wParam);
}
