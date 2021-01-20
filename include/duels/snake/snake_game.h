#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <duels/snake/msg.h>
#include <vector>
#include<duels/utils/vector2d.h>

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
    COORDINATE Convert_To_Coordinate(int x, int y)
    {
        COORDINATE Coor;
        Coor.X=x;
        Coor.Y=y;
        return Coor;
    }
    COORDINATE Print_Coord(COORDINATE coor)
    {
        int x=coor.X;
        int y=coor.Y;
        std::cout<<"("<<x<<","<<y<<")"<<std::endl;
    }
    bool isaliveSnake1(displayMsg); //By snake1 we mean the snake whose head is located in (x1,y1)
    bool isaliveSnake2(displayMsg); //By snake2 we mean the snake whose head is located in (x2,y2)
    void EatfoodSnake1(displayMsg);
    bool EatfoodSnake2(displayMsg);
    void moveRandomlySnake1();
    void testbouffagepommeSnake1();
    void moveRandomlySnake2();
    displayMsg updateDisplay(displayMsg);
    std::vector<feedbackMsg> updatefeedback(displayMsg);

    int Snake1Length;
    std::vector<COORDINATE> Snake1ListOfCoordinate;
    int Snake2Length;
    std::vector <COORDINATE> Snake2ListOfCoordinate;
    std::vector <COORDINATE> Appleslist;

};

#endif // SNAKE_GAME_H
