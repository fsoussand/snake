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


snake_game::snake_game(){

}

snake_game::snake_game(displayMsg display)
{

    srand(time(NULL));
    display.x1=rand()%80;
    display.y1=rand()%40;
    std::cout<<display.x1<<std::endl;
    std::cout<<display.y1<<std::endl;
    display.x2=rand()%80;
    display.y2=rand()%40;
    for(int i=0;i<10;i++)
    {
        display.x[i]=rand()%80;
        display.y[i]=rand()%40;
        this->Appleslist.push_back(Convert_To_Coordinate(display.x[i],display.y[i]));
    }

    Snake1Length=1;
    Snake2Length=1;
    this->Snake1ListOfCoordinate.push_back(Convert_To_Coordinate(display.x1,display.y1));
    this->Snake2ListOfCoordinate.push_back(Convert_To_Coordinate(display.x2,display.y2));
}



bool isaliveSnake1(displayMsg display);
bool isaliveSnake2();

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

void snake_game::moveRandomlySnake2()
{
    int randomdir=rand()%4;
    int X=Snake2ListOfCoordinate[0].X;
    int Y=Snake2ListOfCoordinate[0].Y;
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
    Snake2ListOfCoordinate.insert(Snake2ListOfCoordinate.begin(),Head);

};

displayMsg snake_game::updateDisplay(displayMsg display)
{
    display.x1=Snake1ListOfCoordinate[0].X;
    display.y1=Snake1ListOfCoordinate[0].Y;
    display.x2=Snake2ListOfCoordinate[0].X;
    display.y2=Snake2ListOfCoordinate[0].Y;
    for(int i=0;i<10;i++)
    {
        display.x[i]=Appleslist[i].X;
        display.y[i]=Appleslist[i].Y;
    }
    return display;
}

std::vector<feedbackMsg> snake_game::updatefeedback(displayMsg display)
{
    feedbackMsg feedback1;
    feedbackMsg feedback2;
    std::vector<feedbackMsg> FB;
    feedback1.x1=display.x1;
    feedback1.y1=display.y1;
    feedback1.x2=display.x2;
    feedback1.y2=display.y2;
    feedback2.x1=display.x2;
    feedback2.y1=display.y2;
    feedback2.x2=display.x1;
    feedback2.y2=display.y1;
    for(int i=0;i<10;i++)
    {
        feedback1.x[i]=display.x[i];
        feedback1.y[i]=display.y[i];
        feedback2.x[i]=display.x[i];
        feedback2.y[i]=display.y[i];
    }
    FB.push_back(feedback1);
    FB.push_back(feedback2);
    return FB;

}
