#include "Icon.hpp"

#include <cstdlib>

Icon::Icon(std::string pathToFile) : pathToFile(pathToFile), isOnMove(false) {
  WORD pWord;
  ICONINFO iconinfo;
  HICON hIcon = ExtractAssociatedIcon(GetModuleHandle(NULL), pathToFile.c_str(), &pWord);
  GetIconInfo(hIcon, &iconinfo);
  hBitmap = iconinfo.hbmColor;
  if (!hBitmap) exit(1);
}

Icon::~Icon() {
  
}

std::string Icon::GetPathToFile() const {
  return pathToFile;
}

HBITMAP Icon::GetHBitmap() const {
  return hBitmap;
}

int Icon::GetHeight() const {
  return height;
}

int Icon::GetWidth() const {
  return width;
}

void Icon::OnMove(bool isOnMoved) {
  this->isOnMove = isOnMoved;
  int newSize;
  if (isOnMoved)
    newSize = 48;
  else
    newSize = 32;
  SetHeight(newSize);
  SetWidth(newSize);
}

bool Icon::IsOnMove() const {
  return isOnMove;
}

void Icon::SetHeight(int newHeight) {
  height = newHeight;
}

void Icon::SetWidth(int newWidth) {
  width = newWidth;
}