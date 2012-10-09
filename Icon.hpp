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
  bool IsOnMove() const;
  void SetWidth(int);
  void SetHeight(int);
  void OnMove(bool);
private:
  HBITMAP hBitmap;
  int height;
  int width;
  bool isOnMove;
  std::string pathToFile;
};