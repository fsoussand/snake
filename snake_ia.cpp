#include "include/duels/snake/snake_ia.h"
#include <duels/snake/msg.h>
#include <stdlib.h>
#include <iostream>
#include "include/duels/snake/snake_game.h"


snake_IA::snake_IA()
{
}

snake_IA::snake_IA(int Level, snake_game snake){
    switch(Level)
    {
    case 1:
        std::cout<<"IA-level 1 : moving randomly"<<std::endl;
        break;
    case 2:
        std::cout<<"IA-level 2 : eating the closest apple"<<std::endl;
        break;
    case 3:
        std::cout<<"IA-level 3: eating the closest apple and tries to bother its contestant"<<std::endl;
    };
}

void snake_IA::move(int level,snake_game snake){
    switch(level)
    {
    case 1:
        int randomdir=rand()%4;
        int X=snake.Snake1ListOfCoordinate[0].X;
        int Y=snake.Snake1ListOfCoordinate[0].Y;
        switch (randomdir)
        {
        case 0 : //moving down
            Y=Y-1;
            break;
        case 1: //moving up
            Y=Y+1;
            break;
        case 2: //moving right
            X=X+1;
            break;
        case 3: //moving left
            X=X-1;
            break;
        }
        COORDINATE Head=snake.Convert_To_Coordinate(X,Y);
        snake.Snake1ListOfCoordinate.insert(snake.Snake1ListOfCoordinate.end(),Head);
        break;
    }
};
