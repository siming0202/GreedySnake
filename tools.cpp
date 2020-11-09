#include "tools.h"
#include <iostream>

//ȫ����ʾ
COORD FullScreen() {
	//��ȡ��ǰ�����Ĵ��ڵľ��������̨��
	HWND hwnd = GetForegroundWindow();

	SHORT x = GetSystemMetrics(SM_CXSCREEN);	/* ��Ļ��� ���� */
	SHORT y = GetSystemMetrics(SM_CYSCREEN);	/* ��Ļ�߶� ����*/

	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);	/* ��ȡ������Ϣ */
	/* ���ô�����Ϣ ��� ȡ�����������߿� */
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
	
	SetWindowPos(hwnd, HWND_TOP, 0, 0, x, y, 0);

	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOutput, &bInfo);
	SMALL_RECT rc = { 0,0, x, y};	//ͨ��һ��Զ�������ұ߽硢�±߽����ֵ�ļ���ֵʹ���ڴ�Сȡ���ֵ
	//SMALL_RECT rc = { 0,0,87,28 };
	SetConsoleWindowInfo(hOutput, true, &rc);
	
	COORD dSize = { bInfo.srWindow.Right - bInfo.srWindow.Left + 1, bInfo.srWindow.Bottom - bInfo.srWindow.Top + 1 };
	//COORD dSize = { 88,29 };
	SetConsoleScreenBufferSize(hOutput, dSize);

	return { x,y };
}

COORD GetFontSize(COORD screenSize)//���ݷֱ��ʵ��������С����Ļ������
{
	return { screenSize.Y / 32, 32 * screenSize.X / screenSize.Y };
}

void SetWindowSize(int cols, int lines)//���ô��ڴ�С
{
    system("title ̰����");//���ô��ڱ���
    char cmd[30];
    sprintf_s(cmd, "mode con cols=%d lines=%d", cols * 2, lines);//һ��ͼ�Ρ�ռ�����ַ����ʿ�ȳ���2
    system(cmd);//system(mode con cols=88 lines=88)���ô��ڿ�Ⱥ͸߶�
}

void SetCursorPosition(int x, int y)//���ù��λ��
{
	//<windows.h>�ڶ���COORD����ʾһ���ַ��ڿ���̨��Ļ�ϵ�����
    COORD position;
    position.X = x * 2;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void SetColor(int colorID)//�����ı���ɫ
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}

void SetBackColor()//�����ı�����ɫ
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_BLUE |
                            BACKGROUND_BLUE |
                            BACKGROUND_GREEN |
                            BACKGROUND_RED );
}
