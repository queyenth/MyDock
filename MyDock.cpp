#include "MyDock.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>

int MyDock::width;
int MyDock::height;
int MyDock::x;
int MyDock::y;

MyDock::MyDock(int x, int y) {
  Create(x, y);
}

MyDock::~MyDock() {

}

void MyDock::Create(int x, int y) {
  this->x = x;
  this->y = y;
  width = 0;
}

void MyDock::InitSettings(HWND hWnd) {
  std::ifstream configFile("mydock.conf");
  if (!configFile.is_open()) {
    fprintf(stderr, "Couldn't found mydock.conf\n");
    exit(1);
  }
  while (configFile) {
    std::string setting;
    configFile >> setting;
    configFile.ignore(1, ' ');
    if (setting == "icon") {
      char iconPath[150] = {0};
      configFile.getline(iconPath, 150);
      AddIcon(static_cast<std::string>(iconPath));
      continue;
    }
    int value;
    configFile >> value;
    if (setting == "x")
      x = value;
    else if (setting == "y")
      y = value;
    else if (setting == "icon_size")
      icon_size = value;
  }
  height = icon_size+1;
  for (size_t i = 0; i < icons.size(); i++) {
    icons[i].SetHeight(icon_size);
    icons[i].SetWidth(icon_size);
  }
  configFile.close();
}

void MyDock::Draw(HWND hWnd) {
  PAINTSTRUCT ps;
  BITMAP bitmap;
  HDC hdc;
  HDC hdcMem;
  HGDIOBJ oldBitmap;
  hdc = GetDC(hWnd);
  hdcMem = CreateCompatibleDC(hdc);
  int position = 0;
  for (size_t i = 0; i < icons.size(); i++) {
    oldBitmap = SelectObject(hdcMem, icons[i].GetHBitmap());
    GetObject(icons[i].GetHBitmap(), sizeof(bitmap), &bitmap);
    BitBlt(hdc, position, 0, icons[i].GetWidth(),
      icons[i].GetHeight(), hdcMem, 0, 0, SRCCOPY);
    SelectObject(hdcMem, oldBitmap);
    position += icons[i].GetWidth()+1;
  }
  DeleteDC(hdcMem);
  ReleaseDC(hWnd, hdc);
  Sleep(100);
}


bool MyDock::AddIcon(std::string pathToFile) {
  bool done = false;
  FILE *iconFile = fopen(pathToFile.c_str(), "r");
  if (iconFile) {
    icons.push_back(Icon(pathToFile));
    done = true;
    fclose(iconFile);
    width += icon_size+1;
  }
  return done;
}

bool MyDock::DeleteIcon(size_t numberOfIcon) {
  if (numberOfIcon > icons.size())
    return false;
  std::vector<Icon>::iterator posIterator;
  posIterator = icons.begin()+numberOfIcon;
  icons.erase(posIterator);
  return true;
}

int MyDock::CountOfIcons() const {
  return static_cast<int>(icons.size());
}

void MyDock::OnClick(int x, UINT uMsg) {
  x /= icon_size;
  if (uMsg == WM_LBUTTONDOWN)
    ShellExecute(NULL, "open", icons[x].GetPathToFile().c_str(),
      NULL, NULL, SW_SHOWNORMAL);
}
