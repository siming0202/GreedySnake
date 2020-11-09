#include "controller.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "tools.h"
#include "map.h"

int main()//程序入口
{
	FullScreen();//全屏显示
    Controller c;//声明一个Controller类
    c.Game();//整个游戏循环
	return 0;
}
