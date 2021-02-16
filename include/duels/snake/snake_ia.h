#ifndef SNAKE_IA_H
#define SNAKE_IA_H
#include "duels/snake/Coordinate.h"
#include "msg.h"
#include <vector>
#include "grid.h"


/* classe qui marchait a supprimer des qu'on a modif ca bien
class snake_IA
{
public:
    snake_IA();
    snake_IA(int,snake_game);
    snake_game move1(int,snake_game snake);
    snake_game move2(int,snake_game snake);
    int obj1_x;
    int obj1_y;
    int obj2_x;
    int obj2_y;
    int closest_apple=0;
    bool obj1_reached=true;
    bool obj2_reached=true;
    bool obj1_already_eaten=false;
    bool obj2_already_eaten=false;
};*/

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
    int go_target(int, int,feedbackMsg, duels::Grid);
    bool moveX(feedbackMsg, int *);
    bool moveY(feedbackMsg, int *);
    int obj_x;
    int obj_y;
    int closest_apple=0;
    bool obj_reached=true;
    bool obj_already_eaten=false;
    int SnakeLength;
    std::vector<COORDINATE> SnakeListOfCoordinate;
    int SnakeNumber;
    int previousdir=4;


};



#endif // SNAKE_IA_H
