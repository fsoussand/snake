﻿#include "include/duels/snake/snake_ia.h"
#include <duels/snake/msg.h>
#include <stdlib.h>
#include <iostream>
#include "include/duels/snake/snake_game.h"
#include <vector>

#include "include/duels/snake/grid_point.h"
#include <duels/utils/rand_utils.h>
#include <map>
#include "include/duels/snake/a_star.h"


snake_IA::snake_IA()
{

}

snake_IA::snake_IA(int Level,displayMsg display,int snake_number){ //snake number is either 1 or 2, it represents which snake we're playing with
    SnakeNumber=snake_number;
    SnakeLength=1;
    SnakeListOfCoordinate.push_back(Convert_To_Coordinate(display.x1,display.y1));
    for(int i=0;i<20;i++)
    {
        ApplesListSnake.push_back(Convert_To_Coordinate(display.x[i],display.y[i]));
    }


}

int snake_IA::move(int level,feedbackMsg msg,snake_IA *other){
    switch(level)
    {
    case 0:
    {
        int randomdir=rand()%4;
        COORDINATE next_Head=Where_is_next_head(randomdir,SnakeListOfCoordinate[0]);
        while (!isaliveSnake(next_Head,*other))
        {
            randomdir=rand()%4;
            next_Head=Where_is_next_head(randomdir,SnakeListOfCoordinate[0]);

        }
        return randomdir;
        break;
    }
    case 1:
    {
        inputMsg input;
        int randomdir=rand()%4;
        int randomapple=rand()%20;
        int X=msg.x1;
        int Y=msg.y1;
        COORDINATE next_Head;
        if(obj_reached)
        {
            obj_x = msg.x[randomapple];
            obj_y = msg.y[randomapple];
            obj_reached=false;
        }
        if(X==obj_x && Y==obj_y)
        {
            obj_reached=true;
            EatfoodSnake(*other,msg);
            randomdir =UP;
            next_Head=Convert_To_Coordinate(X,Y-1);
            //move(1,msg,other);
        }
        else
        {
            obj_reached=false;
            if (X != obj_x)
            {
                if (X - obj_x <0)
                {
                    if (previousdir!=LEFT)
                    {
                        randomdir=RIGHT;
                        next_Head=Convert_To_Coordinate(X+1,Y);
                    }
                    else
                    {
                        randomdir=UP;
                        next_Head=Convert_To_Coordinate(X,Y-1);
                    }
                }
                else
                {
                    if (previousdir!=RIGHT)
                    {
                        randomdir=LEFT;
                        next_Head=Convert_To_Coordinate(X-1,Y);
                    }
                    else
                    {
                        randomdir=UP;
                        next_Head=Convert_To_Coordinate(X,Y-1);
                    }

                }
            }
            else
            {
                if (Y - obj_y <0)
                {
                    if (previousdir!=UP)
                    {
                        randomdir=DOWN;
                        next_Head=Convert_To_Coordinate(X,Y+1);
                    }
                    else
                    {
                        randomdir=RIGHT;

                        next_Head=Convert_To_Coordinate(X+1,Y);
                    }
                }
                else
                {
                    if(previousdir!=DOWN)
                    {
                        randomdir=UP;
                        next_Head=Convert_To_Coordinate(X,Y-1);

                    }
                    else
                    {
                        randomdir=RIGHT;
                        next_Head=Convert_To_Coordinate(X+1,Y);
                    }
                }
            }
        }
        SnakeListOfCoordinate.insert(SnakeListOfCoordinate.begin(),next_Head);
        SnakeListOfCoordinate.pop_back();
        //input.dir=randomdir;
        previousdir=randomdir;
        return randomdir;
        break;
    }
    case 2:
    {
        inputMsg input;
        int randomdir=rand()%4;
        int randomapple=rand()%20;
        int X=msg.x1;
        int Y=msg.y1;
        COORDINATE next_Head;
        int distmin=std::pow((X-snake_game_ia.Appleslist[closest_apple].X),2)+std::pow((Y-snake_game_ia.Appleslist[closest_apple].Y),2);
        if(obj_reached || obj_already_eaten)
        {

            for(int i=1;i<20;i++)
            {
                int dist=std::pow((X-snake_game_ia.Appleslist[i].X),2)+std::pow((Y-snake_game_ia.Appleslist[i].Y),2);
                if (dist<distmin)
                {
                    distmin=dist;
                    closest_apple=i;

                }

            }
            obj_x = snake_game_ia.Appleslist[closest_apple].X;
            obj_y = snake_game_ia.Appleslist[closest_apple].Y;
            obj_already_eaten=false;
            obj_reached=false;

        }
        if(X==obj_x && Y==obj_y)
        {
            obj_reached=true;
            EatfoodSnake(*other,msg);
            dir=move(2,msg,other);
        }
        else
        {
            obj_reached=false;
            if (X != obj_x)
            {
                if (X - obj_x <0)
                {
                    if (previousdir!=LEFT)
                    {
                        randomdir=RIGHT;
                        next_Head=Convert_To_Coordinate(X+1,Y);
                    }
                    else
                    {
                        randomdir=UP;
                        next_Head=Convert_To_Coordinate(X,Y-1);
                    }
                }
                else
                {
                    if (previousdir!=RIGHT)
                    {
                        randomdir=LEFT;
                        next_Head=Convert_To_Coordinate(X-1,Y);
                    }
                    else
                    {
                        randomdir=UP;
                        next_Head=Convert_To_Coordinate(X,Y-1);
                    }

                }
            }
            else
            {
                if (Y - obj_y <0)
                {
                    if (previousdir!=UP)
                    {
                        randomdir=DOWN;
                        next_Head=Convert_To_Coordinate(X,Y+1);
                    }
                    else
                    {
                        randomdir=RIGHT;

                        next_Head=Convert_To_Coordinate(X+1,Y);
                    }
                }
                else
                {
                    if(previousdir!=DOWN)
                    {
                        randomdir=UP;
                        next_Head=Convert_To_Coordinate(X,Y-1);

                    }
                    else
                    {
                        randomdir=RIGHT;
                        next_Head=Convert_To_Coordinate(X+1,Y);
                    }
                }
            }
        }
        SnakeListOfCoordinate.insert(SnakeListOfCoordinate.begin(),next_Head);
        SnakeListOfCoordinate.pop_back();
        //input.dir=randomdir;
        previousdir=randomdir;
        return randomdir;
        break;

    }
    case 3:
    {
        //int dir;

        const int rows(HEIGHT);
        const int cols(WIDTH);

        duels::Grid grid(rows, cols);
        int X=msg.x1;
        int Y=msg.y1;
        std::vector<duels::GridPoint> path;
        duels::GridPoint start(SnakeListOfCoordinate[0].X,SnakeListOfCoordinate[0].Y);
        duels::GridPoint goal;

        int closest_apple=0;

        for(int i = 0; i < rows; i++) //This will be used to construct the grid
        {
            for(int j=0;j<cols;j++)
            {
                duels::GridPoint Point(i,j);
                COORDINATE Coor=Convert_To_Coordinate(i,j);
                if(isaliveSnake(Coor,*other))
                {
                    grid.cell(Point)=0; //0 Means the path is free

                }
                else
                {
                    grid.cell(Point)=1; //2 Means there's an obstacle
                }

            }

        }

        duels::GridPoint::configure(grid, true);

        int distmin=std::pow((X-ApplesListSnake[closest_apple].X),2)+std::pow((Y-ApplesListSnake[closest_apple].Y),2);
        if(obj_reached || obj_already_eaten)
        {

            for(int i=1;i<20;i++)
            {
                int dist=std::pow((X-ApplesListSnake[i].X),2)+std::pow((Y-ApplesListSnake[i].Y),2);
                if (dist<distmin)
                {
                    distmin=dist;
                    closest_apple=i;

                }

            }
            obj_x = ApplesListSnake[closest_apple].X;
            obj_y = ApplesListSnake[closest_apple].Y;
            obj_already_eaten=false;
            obj_reached=false;

        }

        if (obj_x==other->obj_x && obj_y==other->obj_y)
        {
            while(other->obj_x==obj_x && obj_y==other->obj_y)
            {
                closest_apple=rand()%ApplesListSnake.size();
                other->obj_x=snake_game_ia.Appleslist[closest_apple].X;
                other->obj_y=snake_game_ia.Appleslist[closest_apple].Y;
            }
        }



        if (X==obj_x && Y==obj_y)
        {
            obj_reached=true;
            EatfoodSnake(*other,msg);
            dir=move(3,msg,other);
        }

        else
        {
            COORDINATE obj=Convert_To_Coordinate(obj_x,obj_y);

            for (int i=0;i<ApplesListSnake.size();i++)
            {
                if (obj_x == ApplesListSnake[i].X && obj_y == ApplesListSnake[i].Y)
                {
                    obj_already_eaten=false;
                }
            }
            if(obj_already_eaten)
            {
                dir=move(3,msg,other);
            }
            else
            {
                goal.x=obj_x;
                goal.y=obj_y;

                path = duels::Astar(start, goal, true);

                duels::GridPoint next_Point=path[1];


                COORDINATE next_Head=Convert_To_Coordinate(next_Point.x,next_Point.y);

                if (X != next_Head.X)
                {
                    if (X - next_Head.X <0)
                    {
                        dir=RIGHT;
                    }
                    else
                    {
                        dir=LEFT;
                    }
                }
                else
                {
                    if (Y - next_Head.Y <0)
                    {
                        dir=DOWN;
                    }
                    else
                    {
                        dir=UP;
                    }
                }
                SnakeListOfCoordinate.insert(SnakeListOfCoordinate.begin(),next_Head);
                SnakeListOfCoordinate.pop_back();
            }
        }
        return dir;
        break;
    }
    case 4:
    {

        const int rows(HEIGHT);
        const int cols(WIDTH);

        duels::Grid grid(rows, cols);
        int X=msg.x1;
        int Y=msg.y1;
        std::vector<duels::GridPoint> path;

        duels::GridPoint start(X,Y);
        duels::GridPoint goal;

        int closest_apple=0;

        for(int i = 0; i < rows; i++) //This will be used to construct the grid
        {
            for(int j=0;j<cols;j++)
            {
                duels::GridPoint Point(j,i);
                COORDINATE Coor=Convert_To_Coordinate(j,i);

                if(isaliveSnake(Coor,*other))
                {
                    grid.cell(Point)=0; //0 Means the path is free
                }
                else
                {
                    grid.cell(Point)=2; //2 Means there's an obstacle
                }
            }
        }

        duels::GridPoint::configure(grid, true);

        closest_apple=0;
        goal.x=ApplesListSnake[0].X;
        goal.y=ApplesListSnake[0].Y;
        path = duels::Astar(start, goal, true);
        int distmin=path.size();

        if(obj_reached)
        {

            for(int i=1;i<ApplesListSnake.size();i++)
            {
                goal.x=ApplesListSnake[i].X;
                goal.y=ApplesListSnake[i].Y;
                path = duels::Astar(start, goal, true);
                int dist=path.size();
                if (dist<distmin)
                {
                    distmin=dist;
                    closest_apple=i;
                }
            }
            obj_x = ApplesListSnake[closest_apple].X;
            obj_y = ApplesListSnake[closest_apple].Y;
            obj_reached=false;
        }


        if (obj_x==other->obj_x && obj_y==other->obj_y)
        {
            while(other->obj_x==obj_x && obj_y==other->obj_y)
            {
                closest_apple=rand()%ApplesListSnake.size();
                other->obj_x=ApplesListSnake[closest_apple].X;
                other->obj_y=ApplesListSnake[closest_apple].Y;
            }
        }

        if (X==obj_x && Y==obj_y)
        {
            obj_reached=true;
            EatfoodSnake(*other,msg);
            dir=move(4,msg,other);
        }

        else
        {
            goal.x=obj_x;
            goal.y=obj_y;

            path = duels::Astar(start, goal, true);

            duels::GridPoint next_Point=path[1];


            COORDINATE next_Head=Convert_To_Coordinate(next_Point.x,next_Point.y);

            if (X != next_Head.X)
            {
                if (X - next_Head.X <0)
                {
                    dir=RIGHT;
                }
                else
                {
                    dir=LEFT;
                }
            }
            else
            {
                if (Y - next_Head.Y <0)
                {
                    dir=DOWN;
                }
                else
                {
                    dir=UP;
                }
            }
            SnakeListOfCoordinate.insert(SnakeListOfCoordinate.begin(),next_Head);
            SnakeListOfCoordinate.pop_back();

        }
        return dir;
        break;
    }

    }

};

bool snake_IA::moveX(feedbackMsg msg,int *dir)
{
    int X=msg.x1;
    bool move=false;
    if (X!=obj_x)
    {
        if (X - obj_x<0)
        {
            *dir=2;
        }
        else
        {
            *dir=3;
        }
        move=true;
    }
    return move;
}

bool snake_IA::moveY(feedbackMsg msg, int *dir)
{
    int Y=msg.y1;
    bool move=false;
    if (Y!=obj_y)
    {
        if (Y - obj_y<0)
        {
            *dir=1;
        }
        else
        {
            *dir=0;
        }
        move=true;
    }
    return move;
}

COORDINATE snake_IA::EvalPosHead(int X, int Y,int dir)
{
    COORDINATE Head;
    int pos_x=X;
    int pos_y=Y;
    switch(dir)
    {
    case 0:
        pos_y=Y-1;
        break;
    case 1:
        pos_y=Y+1;
        break;
    case 2:
        pos_x=X+1;
        break;
    case 3:
        pos_x=X-1;
    }
    Head = Convert_To_Coordinate(pos_x,pos_y);
    return Head;
}

bool snake_IA::isaliveSnake(COORDINATE Head, snake_IA other)
{
    bool state=true;
    if(Head.X<0||Head.Y<0||Head.X>HEIGHT||Head.Y>WIDTH)
    {
        state=false;
    }
    if(Head.X>=WIDTH-15&&Head.Y<5)
    {
        state=false;
    }
    for (int i=0;i<other.SnakeLength;i++)
    {
        if(Head.X==other.SnakeListOfCoordinate[i].X && Head.Y==other.SnakeListOfCoordinate[i].Y)
        {
            state=false;
        }
    }
    for(int i=1;i<SnakeLength;i++)
    {
        if(Head.X==SnakeListOfCoordinate[i].X && Head.Y==SnakeListOfCoordinate[i].Y)
        {
            state=false;
        }
    }
    return state;
};

int snake_IA::go_target(int obj_x,int obj_y,feedbackMsg msg, Grid grid)
{
    int dir=0;
    inputMsg input;
    int X=msg.x1;
    int Y=msg.y1;
    bool depla_x=false;
    bool depla_y=false;
    COORDINATE next_Head;
    bool is_alive;
    GridPoint start(X,Y);
    GridPoint goal(obj_x,obj_y);


    if(start==goal)
    {
        obj_reached=true;
    }
    else
    {
        obj_reached=false;
        if (X != obj_x)
        {
            if (X - obj_x <0)
            {
                if (grid.isFree(X+1,Y))
                    dir=2;
                else dir=0;
            }
            else
            {
                if (grid.isFree(X-1,Y))
                    dir =3;
                else dir=0;
            }
        }
        else
        {
            if (Y - obj_y <0)
            {
                if (grid.isFree(X,Y+1))
                    dir=1;
                else dir=2;
            }
            else
            {
                if(grid.isFree(X,Y-1))
                    dir=0;
                else dir=2;
            }
        }
    }

    input.dir=dir;
    return dir;



}

bool snake_IA::isaliveSnakebis(snake_IA other)
{
    COORDINATE Head=SnakeListOfCoordinate[0];
    bool state=true;
    if(Head.X<0||Head.Y<0||Head.X>HEIGHT||Head.Y>=WIDTH)
    {
        state=false;
    }
    for (int i=0;i<other.SnakeLength;i++)
    {
        if(Head.X==other.SnakeListOfCoordinate[i].X && Head.Y==other.SnakeListOfCoordinate[i].Y)
        {
            state=false;
        }
    }
    for(int i=1;i<SnakeLength;i++)
    {
        if(Head.X==SnakeListOfCoordinate[i].X && Head.Y==SnakeListOfCoordinate[i].Y)
        {
            state=false;
        }
    }
    return state;
};


void snake_IA::EatfoodSnake(snake_IA other, feedbackMsg msg) //THe function that deals with the snake eating an apple
{

    int dx_back=0;
    int dy_back=0;
    int pos;
    for (int i=0;i<ApplesListSnake.size();i++)
    {
        if ((SnakeListOfCoordinate[0].X == ApplesListSnake[i].X)&&(SnakeListOfCoordinate[0].Y == ApplesListSnake[i].Y)) //If the snake head is on one of the apples
        {

            if (SnakeLength>=2) //We want to obtain the direction of the tail to add a new body part after the current tail
            {
                dx_back=SnakeListOfCoordinate[SnakeLength-1].X-SnakeListOfCoordinate[SnakeLength-2].X;
                dy_back=SnakeListOfCoordinate[SnakeLength-1].Y-SnakeListOfCoordinate[SnakeLength-2].Y;
            }
            SnakeLength+=1;
            COORDINATE coor2= Convert_To_Coordinate(SnakeListOfCoordinate[SnakeLength-2].X+dx_back,SnakeListOfCoordinate[SnakeLength-2].Y+dy_back);
            SnakeListOfCoordinate.push_back(coor2); //We add the new body part to the list of coordinates

            COORDINATE new_apple;
            new_apple.X=rand()%WIDTH;
            new_apple.Y=rand()%HEIGHT;
            while(new_apple.X>=WIDTH-15 && new_apple.Y<5)
            {
                new_apple.X=rand()%WIDTH;
                new_apple.Y=rand()%HEIGHT;
            }
            for(int i=0;i<SnakeLength-1;i++)
            {

                while(new_apple.X==SnakeListOfCoordinate[i].X && new_apple.Y==SnakeListOfCoordinate[i].Y)
                {
                    new_apple.X=rand()%WIDTH;
                    new_apple.Y=rand()%HEIGHT;
                }
            }
            for(int i=0;i<other.SnakeLength-1;i++)
            {

                while(new_apple.X==other.SnakeListOfCoordinate[i].X && new_apple.Y==other.SnakeListOfCoordinate[i].Y)
                {
                    new_apple.X=rand()%WIDTH;
                    new_apple.Y=rand()%HEIGHT;
                }
            }

            ApplesListSnake.push_back(new_apple);


            for (int i=0;i<ApplesListSnake.size();i++)
            {
                if ((ApplesListSnake[i].X == SnakeListOfCoordinate[0].X)&&(ApplesListSnake[i].Y ==SnakeListOfCoordinate[0].Y))
                {
                    pos=i;
                }
            }
            ApplesListSnake.erase(ApplesListSnake.begin()+pos); //We erase from the list the apple that was eaten

        }

    }

}
