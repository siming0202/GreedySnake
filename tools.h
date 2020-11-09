#include <windows.h>
#include <stdio.h>

#ifndef TOOLS_H
#define TOOLS_H

COORD FullScreen();
void SetWindowSize(int cols, int lines);
void SetCursorPosition(int x, int y);
void SetColor(int colorID);
void SetBackColor();
COORD GetFontSize(COORD);

#endif // TOOLS_H
