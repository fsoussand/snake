#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "snake_ia.h"

#include <duels/snake/msg.h>
#include <vector>
#include<duels/utils/vector2d.h>




const int HEIGHT=40;
const int WIDTH=40;

using namespace duels;
using namespace duels::snake;

/*anceienne version a supp des qu'on a modif ca bien
class snake_game
{
public:
    snake_game();
    snake_game(displayMsg);

    displayMsg Create_display();
    COORDINATE Convert_To_Coordinate(int x, int y)
    {
        COORDINATE Coor;
        Coor.X=x;
        Coor.Y=y;
        return Coor;
    }
    void Print_Coord(COORDINATE coor)
    {
        int x=coor.X;
        int y=coor.Y;
        std::cout<<"("<<x<<","<<y<<")"<<std::endl;
    }

    bool Test_Coord_in_List(COORDINATE coor,std::vector<COORDINATE> list)
    {
        bool Is_in=false;
        for (int i=0;i<list.size();i++)
        {
            if ((coor.X==list[i].X) && ((coor.Y==list[i].Y)))
            {
                Is_in = true;
            }
        }
        return Is_in;
    }
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

    int Snake1Length;
    std::vector<COORDINATE> Snake1ListOfCoordinate;
    int Snake2Length;
    std::vector <COORDINATE> Snake2ListOfCoordinate;
    std::vector <COORDINATE> Appleslist;

};*/

class snake_game
{
public:
    snake_game();
    snake_game(displayMsg);

    displayMsg Create_display();

    void EatfoodSnake(snake_IA,snake_IA,feedbackMsg);
    COORDINATE generate_random_apple(snake_IA,snake_IA);
    displayMsg updateDisplay(displayMsg,snake_IA,snake_IA);
    std::vector<feedbackMsg> updatefeedback(displayMsg);

    std::vector <COORDINATE> Appleslist;

};

#endif // SNAKE_GAME_H

