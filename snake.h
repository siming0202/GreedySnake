#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include "point.h"
#include "food.h"

class Food;
class Snake
{
	friend class Food;//将Food类置为友元，以便访问其私有元素

public:
    enum Direction {UP, DOWN, LEFT, RIGHT};

    Snake() {
        snake.emplace_back(14, 8);
        snake.emplace_back(15, 8);
        snake.emplace_back(16, 8);
        direction = Direction::DOWN;
    }
    void InitSnake();
	void Move();
    void NormalMove();
    bool OverEdge(int);
    bool HitItself();
    bool ChangeDirection();
    bool GetFood(const Food&);
    bool GetBigFood(Food&);
	bool CatchBigFood(Food&);
private:
    std::deque<Point> snake;
    Direction direction;
};
#endif // SNAKE_H
