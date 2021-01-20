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
    case 0:
        std::cout<<"IA-level 0: moving randomly"<<std::endl;
        break;
    case 1:
        std::cout<<"IA-level 1 : eating a random apple"<<std::endl;
        break;
    case 2:
        std::cout<<"IA-level 2 : eating the closest apple"<<std::endl;
        break;
    case 3:
        std::cout<<"IA-level 3: eating the closest apple and tries to bother its contestant"<<std::endl;
    };
}

snake_game snake_IA::move(int level,snake_game snake){
    switch(level)
    {
    case 0:
    {
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
        };
        COORDINATE Head=snake.Convert_To_Coordinate(X,Y);
        snake.Snake1ListOfCoordinate.insert(snake.Snake1ListOfCoordinate.begin(),Head);
        break;
    }
    case 1:
    {
        int randomdir=rand()%4;
        int randomapple=rand()%10;
        int X=snake.Snake1ListOfCoordinate[0].X;
        int Y=snake.Snake1ListOfCoordinate[0].Y;
        obj_x = snake.Appleslist[randomapple].X;
        obj_y = snake.Appleslist[randomapple].Y;
        if (X != obj_x)
        {
            if (X - obj_x <0)
            {
                randomdir=2;
            }
            else
            {
                randomdir=3;
            }
        }
        else
        {
            if (Y - obj_y <0)
            {
                randomdir=1;
            }
            else
            {
                randomdir=0;
            }
        }
        switch (randomdir)
        {
        case 0 : //moving up
            Y=Y-1;
            break;
        case 1: //moving down
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
        snake.Snake1ListOfCoordinate.insert(snake.Snake1ListOfCoordinate.begin(),Head);
        break;
    }
    case 2:
    {
        int X=snake.Snake1ListOfCoordinate[0].X;
        int Y=snake.Snake1ListOfCoordinate[0].Y;
        int closest_apple=0;
        if(obj_reached)
        {
            int distmin=abs(X*X+Y*Y-snake.Appleslist[closest_apple].X*snake.Appleslist[closest_apple].X-snake.Appleslist[closest_apple].Y*snake.Appleslist[closest_apple].Y);
            for(int i=1;i<10;i++)
            {
                int dist = abs(X*X+Y*Y-snake.Appleslist[i].X*snake.Appleslist[i].X-snake.Appleslist[i].Y*snake.Appleslist[i].Y);
                if (dist<distmin)
                {
                    distmin=dist;
                    closest_apple=i;
                }

            }
            obj_x = snake.Appleslist[closest_apple].X;
            obj_y = snake.Appleslist[closest_apple].Y;
        }
        if (X==obj_x && Y==obj_y)
        {
            obj_reached=true;
        }
        else
        {
            obj_reached=false;
            snake.go_target1(obj_x,obj_y);
        }

    }

    }
    return snake;
};
