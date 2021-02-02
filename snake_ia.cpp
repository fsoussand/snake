#include "include/duels/snake/snake_ia.h"
#include <duels/snake/msg.h>
#include <stdlib.h>
#include <iostream>
#include "include/duels/snake/snake_game.h"
#include <vector>
#include "include/duels/snake/a_star.h"
#include "include/duels/snake/vector2d.h"
#include "include/duels/snake/grid.h"
#include "include/duels/snake/grid_point.h"

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
        std::cout<<"IA-level 3: using A*"<<std::endl;
    };
}

snake_game snake_IA::move1(int level,snake_game snake){
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
        int randomapple=rand()%snake.Appleslist.size();
        int X=snake.Snake1ListOfCoordinate[0].X;
        int Y=snake.Snake1ListOfCoordinate[0].Y;
        obj1_x = snake.Appleslist[randomapple].X;
        obj1_y = snake.Appleslist[randomapple].Y;
        if (X != obj1_x)
        {
            if (X - obj1_x <0)
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
            if (Y - obj1_y <0)
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
        if(obj1_reached || obj1_already_eaten)
        {
            int distmin=std::pow((X-snake.Appleslist[closest_apple].X),2)+std::pow((Y-snake.Appleslist[closest_apple].Y),2);
            for(int i=1;i<snake.Appleslist.size();i++)
            {
                int dist=std::pow((X-snake.Appleslist[i].X),2)+std::pow((Y-snake.Appleslist[i].Y),2);
                if (dist<distmin)
                {
                    distmin=dist;
                    closest_apple=i;
                }

            }
            obj1_x = snake.Appleslist[closest_apple].X;
            obj1_y = snake.Appleslist[closest_apple].Y;
            obj1_already_eaten=false;

        }
        if (X==obj1_x && Y==obj1_y)
        {
            obj1_reached=true;
            snake=move1(2,snake);
        }
        else
        {
            if(obj2_reached && obj2_x==obj1_x && obj2_y==obj1_y)
            {
                obj1_already_eaten=true;
            }
            obj1_reached=false;
            snake.go_target1(obj1_x,obj1_y);
        }
        COORDINATE obj = snake.Convert_To_Coordinate(obj1_x,obj1_y);
        if (!snake.Test_Coord_in_List(obj,snake.Appleslist))
        {
            move1(2,snake);
        }
        //std::cout<<"objectif"<<std::endl;
        //snake.Print_Coord(snake.Convert_To_Coordinate(obj_x,obj_y));

    }
    case 3:
    {

    }
    }

    return snake;
};

snake_game snake_IA::move2(int level,snake_game snake){
    switch(level)
    {
    case 0:
    {
        int dir=rand()%4;
        int X=snake.Snake2ListOfCoordinate[0].X;
        int Y=snake.Snake2ListOfCoordinate[0].Y;
        switch (dir)
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
        snake.Snake2ListOfCoordinate.insert(snake.Snake2ListOfCoordinate.begin(),Head);
        break;
    }
    case 1:
    {
        int randomdir=rand()%4;
        int randomapple=rand()%snake.Appleslist.size();
        int X=snake.Snake2ListOfCoordinate[0].X;
        int Y=snake.Snake2ListOfCoordinate[0].Y;
        obj2_x = snake.Appleslist[randomapple].X;
        obj2_y = snake.Appleslist[randomapple].Y;
        if (X != obj2_x)
        {
            if (X - obj2_x <0)
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
            if (Y - obj2_y <0)
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
        snake.Snake2ListOfCoordinate.insert(snake.Snake2ListOfCoordinate.begin(),Head);
        break;
    }
    case 2:
    {
        int X=snake.Snake2ListOfCoordinate[0].X;
        int Y=snake.Snake2ListOfCoordinate[0].Y;
        int closest_apple=0;
        if(obj2_reached || obj2_already_eaten)
        {
            int distmin=std::pow((X-snake.Appleslist[closest_apple].X),2)+std::pow((Y-snake.Appleslist[closest_apple].Y),2);
            for(int i=1;i<snake.Appleslist.size();i++)
            {
                int dist=std::pow((X-snake.Appleslist[i].X),2)+std::pow((Y-snake.Appleslist[i].Y),2);
                if (dist<distmin)
                {
                    distmin=dist;
                    closest_apple=i;
                }

            }
            obj2_x = snake.Appleslist[closest_apple].X;
            obj2_y = snake.Appleslist[closest_apple].Y;
            obj2_already_eaten=false;

        }
        if (X==obj2_x && Y==obj2_y)
        {
            obj2_reached=true;
            snake=move2(2,snake);
        }
        else
        {
            if(obj1_reached && obj2_x==obj1_x && obj2_y==obj1_y)
            {
                obj2_already_eaten=true;
            }
            obj2_reached=false;
            snake.go_target2(obj2_x,obj2_y);
        }
        COORDINATE obj = snake.Convert_To_Coordinate(obj2_x,obj2_y);
        if (!snake.Test_Coord_in_List(obj,snake.Appleslist))
        {
            move2(2,snake);
        }
        //std::cout<<"objectif"<<std::endl;
        //snake.Print_Coord(snake.Convert_To_Coordinate(obj_x,obj_y));

    }


    }
    return snake;
};


