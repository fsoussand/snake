#ifndef SNAKE_IA_H
#define SNAKE_IA_H
#include "snake_game.h"



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
    bool obj1_reached=true;
    bool obj2_reached=true;
    bool obj1_already_eaten=false;
    bool obj2_already_eaten=false;
};

#endif // SNAKE_IA_H
