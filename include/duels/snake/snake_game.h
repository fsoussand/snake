#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <duels/snake/Coordinate.h>
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

class snake_IA;

class snake_game
{
public:
    snake_game();
    snake_game(displayMsg);

    displayMsg Create_display();

    COORDINATE generate_random_apple();
    COORDINATE EvalPosHead(int,int ,int);
    displayMsg updateDisplay(displayMsg);
    std::vector<feedbackMsg> updatefeedback(displayMsg);
    std::vector<feedbackMsg> constructFeedback(feedbackMsg,feedbackMsg);
    void UpdateGame(int,int,snake_IA,snake_IA);


    int Snake1Length;
    std::vector<COORDINATE> Snake1ListOfCoordinate;
    int Snake2Length;
    std::vector <COORDINATE> Snake2ListOfCoordinate;
    static std::vector <COORDINATE> Appleslist;

};

#endif // SNAKE_GAME_H

