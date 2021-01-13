#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <duels/snake/msg.h>
#include <vector>

using namespace duels;
using namespace duels::snake;

struct COORDINATE
{
    int X;
    int Y;
};


class snake_game
{
public:
    snake_game();
    snake_game(displayMsg);

    displayMsg Create_display();
    bool isaliveSnake1(displayMsg); //By snake1 we mean the snake whose head is located in (x1,y1)
    bool isaliveSnake2(displayMsg); //By snake2 we mean the snake whose head is located in (x2,y2)
    feedbackMsg playSnake1(displayMsg);
    feedbackMsg playSnake2(displayMsg);
    bool EatfoodSnake1(displayMsg);
    bool EatfoodSnake2(displayMsg);
    feedbackMsg Create_feedback(displayMsg);
    void moveRandomlySnake1();
    feedbackMsg moveRandomlySnake2(feedbackMsg);
    displayMsg updateDisplay(displayMsg);

    int Snake1Length;
    std::vector<COORDINATE> Snake1ListOfCoordinate;
    int Snake2Length;
    std::vector <COORDINATE> Snake2ListOfCoordinate;

};

#endif // SNAKE_GAME_H
