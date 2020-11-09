#ifndef CONTROLLER_H
#define CONTROLLER_H


class Controller
{
public:
    Controller() : speed(200), key(1), score(0) {}
    void Start();
    int Select();
    void DrawGame();
    int PlayGame();
    void UpdateScore(const int&);
    void RewriteScore();
    int Menu();
    void Game();
    int GameOver();
private:
    int speed;
    int key;
    int score;
	int cols_total_num;
};
#endif // CONTROLLER_H
