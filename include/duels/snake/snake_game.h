#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "snake_ia.h"

#include <duels/snake/msg.h>
#include <vector>
#include<duels/utils/vector2d.h>





const int HEIGHT=40;
const int WIDTH=40;

const int UP=0;
const int DOWN=1;
const int RIGHT=2;
const int LEFT=3;

using namespace duels;
using namespace duels::snake;

class snake_game
{
public:
    snake_game();
    snake_game(displayMsg);

    displayMsg Create_display();

    void EatfoodSnake1();
    void EatfoodSnake2();
    void go_target1(int, int);
    void go_target2(int, int);
    bool moveX(int ,int ,int *);
    bool moveY(int ,int ,int *);
    COORDINATE generate_random_apple();
    COORDINATE EvalPosHead(int,int ,int);
    bool isaliveSnake1(COORDINATE);
    bool isaliveSnake2(COORDINATE);
    bool isaliveSnake1bis();
    bool isaliveSnake2bis();
    displayMsg updateDisplay(displayMsg);
    std::vector<feedbackMsg> updatefeedback(displayMsg);
    std::vector<feedbackMsg> constructFeedback(feedbackMsg,feedbackMsg);
    void UpdateGame(int,int);



    int Snake1Length;
    std::vector<COORDINATE> Snake1ListOfCoordinate;
    int Snake2Length;
    std::vector <COORDINATE> Snake2ListOfCoordinate;
    std::vector <COORDINATE> Appleslist;

};

/*

class snake_game
{
public:
    snake_game();
    snake_game(displayMsg);

    displayMsg Create_display();

    void EatfoodSnake1();
    void EatfoodSnake2();

    void EatfoodSnake(snake_IA,snake_IA,feedbackMsg);
    COORDINATE generate_random_apple(snake_IA,snake_IA);
    displayMsg updateDisplay(displayMsg,snake_game);
    std::vector<feedbackMsg> updatefeedback(displayMsg);

    int Snake1Length;
    std::vector<COORDINATE> Snake1ListOfCoordinate;
    int Snake2Length;
    std::vector <COORDINATE> Snake2ListOfCoordinate;
    std::vector <COORDINATE> Appleslist;


};*/

#endif // SNAKE_GAME_H

