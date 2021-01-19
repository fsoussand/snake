#ifndef SNAKE_IA_H
#define SNAKE_IA_H
#include "snake_game.h"



class snake_IA
{
public:
    snake_IA();
    snake_IA(int,snake_game);
    void move(int,snake_game snake);
};

#endif // SNAKE_IA_H
