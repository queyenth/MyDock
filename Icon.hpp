#pragma once

#include <string>
#include <windows.h>

class Icon {
public:
  Icon(std::string);
  ~Icon();
  HBITMAP GetHBitmap() const;
  std::string GetPathToFile() const;
  int GetHeight() const;
  int GetWidth() const;
  void SetWidth(int);
  void SetHeight(int);
private:
  HBITMAP hBitmap;
  int height;
  int width;
  std::string pathToFile;
};
