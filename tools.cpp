#include "tools.h"
#include <iostream>

//全屏显示
COORD FullScreen() {
	//获取当前工作的窗口的句柄（控制台）
	HWND hwnd = GetForegroundWindow();

	SHORT x = GetSystemMetrics(SM_CXSCREEN);	/* 屏幕宽度 像素 */
	SHORT y = GetSystemMetrics(SM_CYSCREEN);	/* 屏幕高度 像素*/

	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);	/* 获取窗口信息 */
	/* 设置窗口信息 最大化 取消标题栏及边框 */
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
	
	SetWindowPos(hwnd, HWND_TOP, 0, 0, x, y, 0);

	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOutput, &bInfo);
	SMALL_RECT rc = { 0,0, x, y};	//通过一个远超窗口右边界、下边界可能值的极大值使窗口大小取最大值
	//SMALL_RECT rc = { 0,0,87,28 };
	SetConsoleWindowInfo(hOutput, true, &rc);
	
	COORD dSize = { bInfo.srWindow.Right - bInfo.srWindow.Left + 1, bInfo.srWindow.Bottom - bInfo.srWindow.Top + 1 };
	//COORD dSize = { 88,29 };
	SetConsoleScreenBufferSize(hOutput, dSize);

	return { x,y };
}

COORD GetFontSize(COORD screenSize)//根据分辨率调整字体大小和屏幕总列数
{
	return { screenSize.Y / 32, 32 * screenSize.X / screenSize.Y };
}

void SetWindowSize(int cols, int lines)//设置窗口大小
{
    system("title 贪吃蛇");//设置窗口标题
    char cmd[30];
    sprintf_s(cmd, "mode con cols=%d lines=%d", cols * 2, lines);//一个图形■占两个字符，故宽度乘以2
    system(cmd);//system(mode con cols=88 lines=88)设置窗口宽度和高度
}

void SetCursorPosition(int x, int y)//设置光标位置
{
	//<windows.h>内定义COORD，表示一个字符在控制台屏幕上的坐标
    COORD position;
    position.X = x * 2;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void SetColor(int colorID)//设置文本颜色
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}

void SetBackColor()//设置文本背景色
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_BLUE |
                            BACKGROUND_BLUE |
                            BACKGROUND_GREEN |
                            BACKGROUND_RED );
}
