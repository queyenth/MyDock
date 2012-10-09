#pragma once

#include "Icon.hpp"
#include <vector>
#include <windows.h>

class MyDock {
public:
  static int x;
  static int y;
  static int height;
  static int width;

  MyDock(int, int);
  ~MyDock();
  void Create(int, int);
  void Draw(HWND);
  bool AddIcon(std::string);
  bool DeleteIcon(size_t);
  int CountOfIcons() const;
  void OnClick(int, UINT);
  void OnMove(int);
  void InitSettings(HWND);
private:
  int icon_size;
  std::vector<Icon> icons;
};