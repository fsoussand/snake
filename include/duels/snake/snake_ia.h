#ifndef SNAKE_IA_H
#define SNAKE_IA_H
#include "duels/snake/Coordinate.h"
#include "msg.h"
#include <vector>
#include "grid.h"
#include "duels/snake/snake_game.h"



using namespace duels::snake;

class snake_IA
{
public:

    snake_IA();
    snake_IA(int,displayMsg,int);
    int move(int,feedbackMsg,snake_IA);
    bool isaliveSnake(COORDINATE,snake_IA);
    bool isaliveSnakebis(snake_IA);
    COORDINATE EvalPosHead(int, int,int);
    int go_target(int, int,feedbackMsg, duels::Grid,snake_IA);
    bool moveX(feedbackMsg, int *);
    bool moveY(feedbackMsg, int *);

    void EatfoodSnake(snake_IA,feedbackMsg);


    int obj_x;
    int obj_y;
    int closest_apple=0;
    bool obj_reached=true;
    bool obj_already_eaten=false;
    int SnakeLength;
    std::vector<COORDINATE> SnakeListOfCoordinate;
    int SnakeNumber;
    int previousdir=4;
    int dir;
    snake_game snake_game_ia;


};



#endif // SNAKE_IA_H
