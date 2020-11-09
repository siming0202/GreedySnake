#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "controller.h"
#include "tools.h"
#include "startinterface.h"
#include "map.h"
#include "snake.h"
#include "food.h"

void Controller::Start()//开始界面
{
	COORD screenSize = FullScreen();//全屏显示
	//SetWindowSize(41, 32);//设置窗口大小
    
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX consoleCurrentFontEx;
	//CONSOLE_SCREEN_BUFFER_INFO bInfo;

	GetCurrentConsoleFontEx(hOutput, TRUE, &consoleCurrentFontEx);
	consoleCurrentFontEx.cbSize = sizeof(CONSOLE_FONT_INFOEX); //在改变字体的扩展信息之前必须包含该语句
	COORD FontSizeAndColsNum = GetFontSize(screenSize);
	consoleCurrentFontEx.dwFontSize.Y = FontSizeAndColsNum.X;
	cols_total_num = FontSizeAndColsNum.Y;
	SetCurrentConsoleFontEx(hOutput, TRUE, &consoleCurrentFontEx);

	SetColor(2);//设置开始动画颜色
    StartInterface *start = new StartInterface();//动态分配一个StartInterface类start
    start->Action(cols_total_num);//开始动画
    delete start;//释放内存空间

    /*设置关标位置，并输出提示语，等待任意键输入结束*/
    SetCursorPosition(cols_total_num / 2 - 7, 26);
    std::cout << "Press any key to start... ";
    SetCursorPosition(cols_total_num / 2 - 7, 27);
    system("pause");
}

int Controller::Select()//选择界面
{
    /*初始化界面选项*/
    SetColor(3);
    SetCursorPosition(cols_total_num / 2 - 7, 26);
    std::cout << "                          " ;
    SetCursorPosition(cols_total_num / 2 - 7, 27);
    std::cout << "                          " ;
    SetCursorPosition(cols_total_num / 3, 21);
    std::cout << "请选择游戏难度：" ;
    SetCursorPosition(cols_total_num / 3, 22);
    std::cout << "(上下键选择,回车确认)" ;
    SetCursorPosition(2 * cols_total_num / 3, 22);
    SetBackColor();//第一个选项设置背景色以表示当前选中
    std::cout << "简单模式" ;
    SetCursorPosition(2 * cols_total_num / 3, 24);
    SetColor(3);
    std::cout << "普通模式" ;
    SetCursorPosition(2 * cols_total_num / 3, 26);
    std::cout << "困难模式" ;
    SetCursorPosition(2 * cols_total_num / 3, 28);
    std::cout << "炼狱模式" ;
	SetCursorPosition(2 * cols_total_num / 3, 30);
	std::cout << "退出游戏";
    SetCursorPosition(0, 31);
    score = 0;

    /*上下方向键选择模块*/
    int ch;//记录键入值
    key = 1;//记录选中项，初始选择第一个
    bool flag = false;//记录是否键入Enter键标记，初始置为否
    while ((ch = _getch()))
    {
        switch (ch)//检测输入键
        {
        case 72://UP上方向键
            if (key > 1)//当此时选中项为第一项时，UP上方向键无效
            {
                switch (key)
                {
                case 2:
                    SetCursorPosition(2 * cols_total_num / 3, 22);//给待选中项设置背景色
                    SetBackColor();
                    std::cout << "简单模式" ;

                    SetCursorPosition(2 * cols_total_num / 3, 24);//将已选中项取消背景色
                    SetColor(3);
                    std::cout << "普通模式" ;

                    break;
                case 3:
                    SetCursorPosition(2 * cols_total_num / 3, 24);
                    SetBackColor();
                    std::cout << "普通模式" ;

                    SetCursorPosition(2 * cols_total_num / 3, 26);
                    SetColor(3);
                    std::cout << "困难模式" ;

                    break;
                case 4:
                    SetCursorPosition(2 * cols_total_num / 3, 26);
                    SetBackColor();
                    std::cout << "困难模式" ;

                    SetCursorPosition(2 * cols_total_num / 3, 28);
                    SetColor(3);
                    std::cout << "炼狱模式" ;

                    break;
				case 5:
					SetCursorPosition(2 * cols_total_num / 3, 28);
					SetBackColor();
					std::cout << "炼狱模式";

					SetCursorPosition(2 * cols_total_num / 3, 30);
					SetColor(3);
					std::cout << "退出游戏";

					break;
                }
				--key;
            }
            break;

        case 80://DOWN下方向键
            if (key < 5)
            {
                switch (key)
                {
                case 1:
                    SetCursorPosition(2 * cols_total_num / 3, 24);
                    SetBackColor();
                    std::cout << "普通模式" ;
                    SetCursorPosition(2 * cols_total_num / 3, 22);
                    SetColor(3);
                    std::cout << "简单模式" ;

                    break;
                case 2:
                    SetCursorPosition(2 * cols_total_num / 3, 26);
                    SetBackColor();
                    std::cout << "困难模式" ;
                    SetCursorPosition(2 * cols_total_num / 3, 24);
                    SetColor(3);
                    std::cout << "普通模式" ;

                    break;
                case 3:
                    SetCursorPosition(2 * cols_total_num / 3, 28);
                    SetBackColor();
                    std::cout << "炼狱模式" ;
                    SetCursorPosition(2 * cols_total_num / 3, 26);
                    SetColor(3);
                    std::cout << "困难模式" ;

                    break;
				case 4:
					SetCursorPosition(2 * cols_total_num / 3, 30);
					SetBackColor();
					std::cout << "退出游戏";
					SetCursorPosition(2 * cols_total_num / 3, 28);
					SetColor(3);
					std::cout << "炼狱模式";

					break;
                }
				++key;
            }
            break;

        case 13://Enter回车键
            flag = true;
            break;
        default://无效按键
            break;
        }
        if (flag) break;//输入Enter回车键确认，退出检查输入循环

        SetCursorPosition(0, 31);//将光标置于左下角，避免光标闪烁影响游戏体验
    }

    switch (key)//根据所选选项设置蛇的移动速度，speed值越小，速度越快
    {
    case 1:
        speed = 135;
        break;
    case 2:
        speed = 100;
        break;
    case 3:
        speed = 60;
        break;
    case 4:
        speed = 30;
        break;
    default:
        break;
    }
	return key;
}

void Controller::DrawGame()//绘制游戏界面
{
    system("cls");//清屏

    /*绘制地图*/
    SetColor(3);
    Map *init_map = new Map(cols_total_num);
    init_map->PrintInitmap();
    delete init_map;

    /*绘制侧边栏*/
    SetColor(3);
    SetCursorPosition(11 * cols_total_num / 14, 1);
    std::cout << "Greedy Snake" ;
    SetCursorPosition(11 * cols_total_num / 14 + 1, 2);
    std::cout << "贪吃蛇" ;
    SetCursorPosition(11 * cols_total_num / 14 - 2, 4);
    std::cout << "难度：" ;
    SetCursorPosition(11 * cols_total_num / 14 + 3, 5);
    switch (key)
    {
    case 1:
        std::cout << "简单模式" ;
        break;
    case 2:
        std::cout << "普通模式" ;
        break;
    case 3:
        std::cout << "困难模式" ;
        break;
    case 4:
        std::cout << "炼狱模式" ;
        break;
    default:
        break;
    }
    SetCursorPosition(11 * cols_total_num / 14 - 2, 7);
    std::cout << "得分：" ;
    SetCursorPosition(11 * cols_total_num / 14 + 4, 8);
    std::cout << "     0" ;
    SetCursorPosition(11 * cols_total_num / 14, 13);
    std::cout << " 方向键移动" ;
    SetCursorPosition(11 * cols_total_num / 14, 15);
    std::cout << " ESC键暂停" ;
}

int Controller::PlayGame()//游戏二级循环
{
    /*初始化蛇和食物*/
    Snake *csnake = new Snake();
    Food *cfood = new Food();
    csnake->InitSnake();
    srand((unsigned)time(NULL));//设置随机数种子，如果没有 食物的出现位置将会固定
    cfood->DrawFood(*csnake);

    /*游戏循环*/
    while (csnake->OverEdge(19 * cols_total_num / 29) && csnake->HitItself()) //判断是否撞墙或撞到自身，即是否还有生命
    {
        /*调出选择菜单*/
        if (!csnake->ChangeDirection()) //按Esc键时
        {
            int tmp = Menu();//绘制菜单，并得到返回值
            switch (tmp)
            {
            case 1://继续游戏
                break;

            case 2://重新开始
                delete csnake;
                delete cfood;
                return 1;//将1作为PlayGame函数的返回值返回到Game函数中，表示重新开始

            case 3://退出游戏
                delete csnake;
                delete cfood;
                return 2;//将2作为PlayGame函数的返回值返回到Game函数中，表示退出游戏

            default:
                break;
            }
        }

        if (csnake->GetFood(*cfood)) //吃到食物
        {
            csnake->Move();//蛇增长
            UpdateScore(1);//更新分数，1为分数权重
            RewriteScore();//重新绘制分数
            cfood->DrawFood(*csnake);//绘制蛇头时已经覆盖了食物原本的图案，所以不用消除食物图案，绘制新食物
        }
		else if (csnake->GetBigFood(*cfood)) //吃到限时食物,为了第一时间取消食物的闪烁，必须在移动后判断是否吃到大型食物
		{
			csnake->Move();
			UpdateScore(cfood->GetProgressBar() / 5 + 1);//分数根据限时食物进度条确定
			RewriteScore();
		}
        else
        {
            csnake->NormalMove();//蛇正常移动
        }



        if (cfood->GetBigFlag() && !csnake->CatchBigFood(*cfood)) //如果此时有限时食物，闪烁它
        {
            cfood->FlashBigFood();
        }

        Sleep(speed);//制造蛇的移动效果
    }

    /*蛇死亡*/
    delete csnake;//释放分配的内存空间
    delete cfood;
    int tmp = GameOver();//绘制游戏结束界面，并返回所选项
    switch (tmp)
    {
    case 1:
        return 1;//重新开始
    case 2:
        return 2;//退出游戏
    default:
        return 2;
    }
}

void Controller::UpdateScore(const int& tmp)//更新分数
{
    score += key * 10 * tmp;//所得分数根据游戏难度及传人的参数tmp确定
}

void Controller::RewriteScore()//重绘分数
{
    /*为保持分数尾部对齐，将最大分数设置为6位，计算当前分数位数，将剩余位数用空格补全，再输出分数*/
    SetCursorPosition(11 * cols_total_num / 14 + 4, 8);
    SetColor(11);
    int bit = 0;
    int tmp = score;
    while (tmp != 0)
    {
        ++bit;
        tmp /= 10;
    }
    for (int i = 0; i < (6 - bit); ++i)
    {
        std::cout << " " ;
    }
    std::cout << score ;
}

int Controller::Menu()//选择菜单
{
    /*绘制菜单*/
    SetColor(11);
    SetCursorPosition(11 * cols_total_num / 14 - 1, 19);
    std::cout << "菜单：" ;
    Sleep(100);
    SetCursorPosition(11 * cols_total_num / 14 + 1, 21);
    SetBackColor();
    std::cout << "继续游戏" ;
    Sleep(100);
    SetCursorPosition(11 * cols_total_num / 14 + 1, 23);
    SetColor(11);
    std::cout << "重新开始" ;
    Sleep(100);
    SetCursorPosition(11 * cols_total_num / 14 + 1, 25);
    std::cout << "退出游戏" ;
    SetCursorPosition(0, 31);

    /*选择部分*/
    int ch;
    int tmp_key = 1;
    bool flag = false;
    while (ch = _getch())
    {
        switch (ch)
        {
        case 72://UP
            if (tmp_key > 1)
            {
                switch (tmp_key)
                {
                case 2:
                    SetCursorPosition(11 * cols_total_num / 14 + 1, 21);
                    SetBackColor();
                    std::cout << "继续游戏" ;
                    SetCursorPosition(11 * cols_total_num / 14 + 1, 23);
                    SetColor(11);
                    std::cout << "重新开始" ;

                    break;
                case 3:
                    SetCursorPosition(11 * cols_total_num / 14 + 1, 23);
                    SetBackColor();
                    std::cout << "重新开始" ;
                    SetCursorPosition(11 * cols_total_num / 14 + 1, 25);
                    SetColor(11);
                    std::cout << "退出游戏" ;
                    break;
                }
				--tmp_key;
            }
            break;

        case 80://DOWN
            if (tmp_key < 3)
            {
                switch (tmp_key)
                {
                case 1:
                    SetCursorPosition(11 * cols_total_num / 14 + 1, 23);
                    SetBackColor();
                    std::cout << "重新开始" ;
                    SetCursorPosition(11 * cols_total_num / 14 + 1, 21);
                    SetColor(11);
                    std::cout << "继续游戏" ;

                    break;
                case 2:
                    SetCursorPosition(11 * cols_total_num / 14 + 1, 25);
                    SetBackColor();
                    std::cout << "退出游戏" ;
                    SetCursorPosition(11 * cols_total_num / 14 + 1, 23);
                    SetColor(11);
                    std::cout << "重新开始" ;

                    break;
                }
				++tmp_key;
            }
            break;

        case 13://Enter
            flag = true;
            break;

        default:
            break;
        }

        if (flag)
        {
            break;
        }
        SetCursorPosition(0, 31);
    }

    if (tmp_key == 1) //选择继续游戏，则将菜单擦除
    {
        SetCursorPosition(11 * cols_total_num / 14 - 1, 19);
        std::cout << "      " ;
        SetCursorPosition(11 * cols_total_num / 14 + 1, 21);
        std::cout << "        ";
        SetCursorPosition(11 * cols_total_num / 14 + 1, 23);
        std::cout << "        ";
        SetCursorPosition(11 * cols_total_num / 14 + 1, 25);
        std::cout << "        ";
    }
    return tmp_key;
}

void Controller::Game()//游戏一级循环
{
    while (true)//游戏可视为一个死循环，直到退出游戏时循环结束
    {
		Start();//开始界面
        int tmp_1 = Select();//选择界面
		if (tmp_1 == 5)
			break;

        DrawGame();//绘制游戏界面
        int tmp_2 = PlayGame();//开启游戏循环，当重新开始或退出游戏时，结束循环并返回值给tmp
        if (tmp_2 == 1) //返回值为1时重新开始游戏
        {
            system("cls");
            continue;
        }
        else if (tmp_2 == 2) //返回值为2时退出游戏
        {
            break;
        }
        else
        {
            break;
        }
    }
}

int Controller::GameOver()//游戏结束界面
{
    /*绘制游戏结束界面*/
    Sleep(500);
    SetColor(11);
    SetCursorPosition(cols_total_num / 2 - 11, 8);
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━" ;
    Sleep(30);
    SetCursorPosition(cols_total_num / 2 - 12, 9);
    std::cout << " ┃               Game Over !!!              ┃" ;
    Sleep(30);
    SetCursorPosition(cols_total_num / 2 - 12, 10);
    std::cout << " ┃                                          ┃" ;
    Sleep(30);
    SetCursorPosition(cols_total_num / 2 - 12, 11);
    std::cout << " ┃              很遗憾！你挂了              ┃" ;
    Sleep(30);
    SetCursorPosition(cols_total_num / 2 - 12, 12);
    std::cout << " ┃                                          ┃" ;
    Sleep(30);
    SetCursorPosition(cols_total_num / 2 - 12, 13);
    std::cout << " ┃             你的分数为：                 ┃" ;
    SetCursorPosition(cols_total_num / 2 + 3, 13);
    std::cout << score ;
    Sleep(30);
    SetCursorPosition(cols_total_num / 2 - 12, 14);
    std::cout << " ┃                                          ┃" ;
    Sleep(30);
    SetCursorPosition(cols_total_num / 2 - 12, 15);
    std::cout << " ┃   是否再来一局？                         ┃" ;
    Sleep(30);
    SetCursorPosition(cols_total_num / 2 - 12, 16);
    std::cout << " ┃                                          ┃" ;
    Sleep(30);
    SetCursorPosition(cols_total_num / 2 - 12, 17);
    std::cout << " ┃                                          ┃" ;
    Sleep(30);
    SetCursorPosition(cols_total_num / 2 - 12, 18);
    std::cout << " ┃    嗯，好的        不了，还是学习有意思  ┃" ;
    Sleep(30);
    SetCursorPosition(cols_total_num / 2 - 12, 19);
    std::cout << " ┃                                          ┃" ;
    Sleep(30);
    SetCursorPosition(cols_total_num / 2 - 12, 20);
    std::cout << " ┃                                          ┃" ;
    Sleep(30);
    SetCursorPosition(cols_total_num / 2 - 11, 21);
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━" ;

    Sleep(100);
    SetCursorPosition(cols_total_num / 2 - 9, 18);
    SetBackColor();
    std::cout << "嗯，好的" ;
    SetCursorPosition(0, 31);

    /*选择部分*/
    int ch;
    int tmp_key = 1;
    bool flag = false;
    while (ch = _getch())
    {
        switch (ch)
        {
        case 75://LEFT
            if (tmp_key == 2)
            {
                SetCursorPosition(cols_total_num / 2 - 9, 18);
                SetBackColor();
                std::cout << "嗯，好的" ;
                SetCursorPosition(cols_total_num / 2 - 1, 18);
                SetColor(11);
                std::cout << "不了，还是学习有意思" ;
                --tmp_key;
            }
            break;

        case 77://RIGHT
            if (tmp_key == 1)
            {
                SetCursorPosition(cols_total_num / 2 - 1, 18);
                SetBackColor();
                std::cout << "不了，还是学习有意思" ;
                SetCursorPosition(cols_total_num / 2 - 9, 18);
                SetColor(11);
                std::cout << "嗯，好的" ;
                ++tmp_key;
            }
            break;

        case 13://Enter
            flag = true;
            break;

        default:
            break;
        }

        SetCursorPosition(0, 31);
        if (flag) {
            break;
        }
    }

    SetColor(11);
    switch (tmp_key)
    {
    case 1:
        return 1;//重新开始
    case 2:
        return 2;//退出游戏
    default:
        return 1;
    }
}

