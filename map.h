#ifndef MAP_H
#define MAP_H

#include <vector>
#include "point.h"

class Map
{
public:
    Map(int cols_total_num)//默认构造函数，将正方形各点压入initmap
    {
		int right_border = 19 * cols_total_num / 29;	/* 左边界和上边界为1， 右边界为变量值， 下边界为30*/
		for (int index = 1; index <= right_border; index++)
		{
			initmap.emplace_back(Point(index, 1));
			initmap.emplace_back(Point(index, 30));
		}

		for (int index = 2; index < 30; index++)
		{
			initmap.emplace_back(Point(1, index));
			initmap.emplace_back(Point(right_border, index));
		}				
    }
    void PrintInitmap();//绘制初始地图
private:
    std::vector<Point> initmap;//保存初始地图
    /*Map类可自定义多种地图，只需将表示地图的各个点保存在相应的map中，并在Snake类中增加相应判断撞墙函数即可
    std::vector<Point> map1;
    std::vector<Point> map2;
    */
};
#endif // MAP_H
