#include "include/snake_game.h"
#include <duels/snake/msg.h>
#include<time.h>
#include<stdlib.h>
#include <vector>

#include <duels/local.h>

using duels::Player;
using namespace duels::snake;

COORDINATE Convert_To_Coordinate(int x, int y)
{
    COORDINATE Coor;
    Coor.X=x;
    Coor.Y=y;
    return Coor;
}


snake_game::snake_game(){}

snake_game::snake_game(displayMsg display)
{
    Snake1Length=1;
    Snake2Length=1;
    this->Snake1ListOfCoordinate.push_back(Convert_To_Coordinate(display.x1,display.y1));
    this->Snake2ListOfCoordinate.push_back(Convert_To_Coordinate(display.x2,display.y2));
}



bool snake_game::isaliveSnake1(displayMsg display)
{
};
bool isaliveSnake2();

feedbackMsg playSnake1();
feedbackMsg playSnake2();
bool EatfoodSnake1();
bool EatfoodSnake2();


void snake_game::moveRandomlySnake1()
{
    int randomdir=rand()%4;
    int X=Snake1ListOfCoordinate[0].X;
    int Y=Snake1ListOfCoordinate[0].Y;
    switch (randomdir)
    {
    case 0 : //moving down
        std::cout<<"Moving down"<<std::endl;
        Y=Y-1;
        break;
    case 1: //moving up
        std::cout<<"Moving up"<<std::endl;
        Y=Y+1;
        break;
    case 2: //moving right
        X=X+1;
        break;
    case 3: //moving left
        X=X-1;
        break;
    }
    std::cout<<"Inserting in list"<<std::endl;
    COORDINATE Head=Convert_To_Coordinate(X,Y);
    Snake1ListOfCoordinate.insert(Snake1ListOfCoordinate.begin(),Head);
    }

displayMsg snake_game::updateDisplay(displayMsg display)
{
    display.x1=Snake1ListOfCoordinate[0].X;
    display.y1=Snake1ListOfCoordinate[0].Y;
    return display;
}

feedbackMsg snake_game::moveRandomlySnake2(feedbackMsg feedback)
{
    int randomdir=rand()%4;
    switch (randomdir)
    {

    case 0://moving up
        for(int i=0;i<Snake2Length;i++)
        {
            Snake2ListOfCoordinate[i].Y+=1;
        }
        break;
    case 1://moving left
        for(int i=0;i<Snake1Length;i++)
        {
            Snake2ListOfCoordinate[i].X+=1;
        }
        break;
    case 2://moving down
        for(int i=0;i<Snake1Length;i++)
        {
            Snake2ListOfCoordinate[i].Y-=1;
        }
        break;
    case 3://moving left
        for(int i=0;i<Snake1Length;i++)
        {
            Snake2ListOfCoordinate[i].Y+=1;
        }
        break;
    }
    feedback.x2=Snake2ListOfCoordinate[0].X;
    feedback.y2=Snake2ListOfCoordinate[0].Y;
    return feedback;

};
