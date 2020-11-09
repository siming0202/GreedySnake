#ifndef MAP_H
#define MAP_H

#include <vector>
#include "point.h"

class Map
{
public:
    Map(int cols_total_num)//Ĭ�Ϲ��캯�����������θ���ѹ��initmap
    {
		int right_border = 19 * cols_total_num / 29;	/* ��߽���ϱ߽�Ϊ1�� �ұ߽�Ϊ����ֵ�� �±߽�Ϊ30*/
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
    void PrintInitmap();//���Ƴ�ʼ��ͼ
private:
    std::vector<Point> initmap;//�����ʼ��ͼ
    /*Map����Զ�����ֵ�ͼ��ֻ�轫��ʾ��ͼ�ĸ����㱣������Ӧ��map�У�����Snake����������Ӧ�ж�ײǽ��������
    std::vector<Point> map1;
    std::vector<Point> map2;
    */
};
#endif // MAP_H
