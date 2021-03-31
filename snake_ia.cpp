#include "include/duels/snake/snake_ia.h"
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
    SnakeLength=1;
    SnakeListOfCoordinate.push_back(Convert_To_Coordinate(display.x1,display.y1));
}

int snake_IA::move(int level,feedbackMsg msg,snake_IA *other){
    switch(level)
    {
    case 0:
    {
        //random move
        COORDINATE next_Head=Where_is_next_head(dir,SnakeListOfCoordinate[0]);
        //test if acceptable next_head
        while (!isaliveSnake(next_Head,*other))
        {
            dir=rand()%4;
            next_Head=Where_is_next_head(dir,SnakeListOfCoordinate[0]);

        }
        //check if apple eaten
        EatfoodSnake(*other,msg);
        return dir;
        break;
    }
    case 1:
    {
        //move toward a random apple
        int randomapple=rand()%20;
        int X=msg.x1;
        int Y=msg.y1;
        COORDINATE next_Head;
        //fix new obj if previous reached
        if(obj_reached)
        {
            obj_x = msg.x[randomapple];
            obj_y = msg.y[randomapple];
            obj_reached=false;
        }
        if(X==obj_x && Y==obj_y)
        {
            //obj reached
            obj_reached=true;
            //check if apple eaten
            EatfoodSnake(*other,msg);
        }
        else
        {
            //chose direction
            obj_reached=false;
            if (X != obj_x)
            {
                if (X - obj_x <0)
                {
                    if (previousdir!=LEFT)
                    {
                        dir=RIGHT;
                        next_Head=Convert_To_Coordinate(X+1,Y);
                    }
                    else
                    {
                        dir=UP;
                        next_Head=Convert_To_Coordinate(X,Y-1);
                    }
                }
                else
                {
                    if (previousdir!=RIGHT)
                    {
                        dir=LEFT;
                        next_Head=Convert_To_Coordinate(X-1,Y);
                    }
                    else
                    {
                        dir=UP;
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
                        dir=DOWN;
                        next_Head=Convert_To_Coordinate(X,Y+1);
                    }
                    else
                    {
                        dir=RIGHT;
                        next_Head=Convert_To_Coordinate(X+1,Y);
                    }
                }
                else
                {
                    if(previousdir!=DOWN)
                    {
                        dir=UP;
                        next_Head=Convert_To_Coordinate(X,Y-1);

                    }
                    else
                    {
                        dir=RIGHT;
                        next_Head=Convert_To_Coordinate(X+1,Y);
                    }
                }
            }
        }
        //update the snake coordinates
        SnakeListOfCoordinate.insert(SnakeListOfCoordinate.begin(),next_Head);
        SnakeListOfCoordinate.pop_back();
        previousdir=dir;
        return dir;
        break;
    }
    case 2:
    {
        //move toward the nearest apple in term of cartesian distance
        int X=msg.x1;
        int Y=msg.y1;
        COORDINATE next_Head;
        int distmin=std::pow((X-snake_game_ia.Appleslist[closest_apple].X),2)+std::pow((Y-snake_game_ia.Appleslist[closest_apple].Y),2);
        //set the obj
        if(obj_reached)
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
            obj_reached=false;

        }
        if(X==obj_x && Y==obj_y)
        {
            obj_reached=true;
            //check if apple eaten
            EatfoodSnake(*other,msg);
            dir=move(2,msg,other);
        }
        else
        {
            //chose direction
            obj_reached=false;
            if (X != obj_x)
            {
                if (X - obj_x <0)
                {
                    if (previousdir!=LEFT)
                    {
                        dir=RIGHT;
                        next_Head=Convert_To_Coordinate(X+1,Y);
                    }
                    else
                    {
                        dir=UP;
                        next_Head=Convert_To_Coordinate(X,Y-1);
                    }
                }
                else
                {
                    if (previousdir!=RIGHT)
                    {
                        dir=LEFT;
                        next_Head=Convert_To_Coordinate(X-1,Y);
                    }
                    else
                    {
                        dir=UP;
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
                        dir=DOWN;
                        next_Head=Convert_To_Coordinate(X,Y+1);
                    }
                    else
                    {
                        dir=RIGHT;

                        next_Head=Convert_To_Coordinate(X+1,Y);
                    }
                }
                else
                {
                    if(previousdir!=DOWN)
                    {
                        dir=UP;
                        next_Head=Convert_To_Coordinate(X,Y-1);

                    }
                    else
                    {
                        dir=RIGHT;
                        next_Head=Convert_To_Coordinate(X+1,Y);
                    }
                }
            }
            //update snake coordinates
            SnakeListOfCoordinate.insert(SnakeListOfCoordinate.begin(),next_Head);
            SnakeListOfCoordinate.pop_back();
        }
        for (int i=0;i<SnakeListOfCoordinate.size();i++)
        {
            Print_Coord(SnakeListOfCoordinate[i]);
        }
        std::cout<<SnakeLength<<std::endl;

        std::cout<<"___________"<<std::endl;
        previousdir=dir;
        return dir;
        break;

    }
    case 3:
    {
        //move toward the nearest apple in term of cartesian distance
        //but using A* : with the optimal path
        const int rows(HEIGHT);
        const int cols(WIDTH);

        duels::Grid grid(rows, cols);
        int X=msg.x1;
        int Y=msg.y1;
        std::vector<duels::GridPoint> path;
        duels::GridPoint start(SnakeListOfCoordinate[0].X,SnakeListOfCoordinate[0].Y);
        duels::GridPoint goal;

        int closest_apple=0;

        //construct the obstacles grid
        for(int i = 0; i < rows; i++)
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
                    grid.cell(Point)=1; //1 Means there's an obstacle
                }

            }

        }

        duels::GridPoint::configure(grid, true);

        int distmin=std::pow((X-snake_game_ia.Appleslist[closest_apple].X),2)+std::pow((Y-snake_game_ia.Appleslist[closest_apple].Y),2);
        //set the obj
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

        //solve a problem when the 2 snakes have the same obj
        //we fix a new random obj to one of them
        //smartest to set the 2nd nearest apple, but lack of time
        if (obj_x==other->obj_x && obj_y==other->obj_y)
        {
            while(other->obj_x==obj_x && obj_y==other->obj_y)
            {
                closest_apple=rand()%snake_game_ia.Appleslist.size();
                other->obj_x=snake_game_ia.Appleslist[closest_apple].X;
                other->obj_y=snake_game_ia.Appleslist[closest_apple].Y;
            }
        }



        if (X==obj_x && Y==obj_y)
        {
            obj_reached=true;
            //check if apple eaten
            EatfoodSnake(*other,msg);
            dir=move(3,msg,other);
        }

        else
        {
            COORDINATE obj=Convert_To_Coordinate(obj_x,obj_y);
            obj_already_eaten=true;
            for (int i=0;i<snake_game_ia.Appleslist.size();i++)
            {
                if (obj_x == snake_game_ia.Appleslist[i].X && obj_y == snake_game_ia.Appleslist[i].Y)
                {
                    obj_already_eaten=false;
                    break;
                }
            }
            if(obj_already_eaten)
            {
                dir=move(3,msg,other);
            }
            else
            {
                //build the path
                goal.x=obj_x;
                goal.y=obj_y;

                path = duels::Astar(start, goal, true);

                duels::GridPoint next_Point=path[1];


                COORDINATE next_Head=Convert_To_Coordinate(next_Point.x,next_Point.y);
                //chose direction
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
                //update snake coordinates
                SnakeListOfCoordinate.insert(SnakeListOfCoordinate.begin(),next_Head);
                SnakeListOfCoordinate.pop_back();
            }
        }
        return dir;
        break;
    }
    case 4:
    {
        //move toward the nearest apple in term of length of path
        //using A* to find the optimal path
        const int rows(HEIGHT);
        const int cols(WIDTH);

        duels::Grid grid(rows, cols);
        int X=msg.x1;
        int Y=msg.y1;
        std::vector<duels::GridPoint> path;

        duels::GridPoint start(X,Y);
        duels::GridPoint goal;

        int closest_apple=0;
        //construct the obstacle grid
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
                    grid.cell(Point)=1; //1 Means there's an obstacle
                }
            }
        }

        duels::GridPoint::configure(grid, true);

        closest_apple=0;
        goal.x=snake_game_ia.Appleslist[0].X;
        goal.y=snake_game_ia.Appleslist[0].Y;
        path = duels::Astar(start, goal, true);
        int distmin=path.size();

        //set the obj
        if(obj_reached||obj_already_eaten)
        {
            for(int i=1;i<snake_game_ia.Appleslist.size();i++)
            {
                goal.x=snake_game_ia.Appleslist[i].X;
                goal.y=snake_game_ia.Appleslist[i].Y;
                path = duels::Astar(start, goal, true);
                int dist=path.size();
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

        //solve a problem when the 2 snakes have the same obj
        //we fix a new random obj to one of them
        //smartest to set the 2nd nearest apple, but lack of time
        if (obj_x==other->obj_x && obj_y==other->obj_y)
        {
            while(other->obj_x==obj_x && obj_y==other->obj_y)
            {
                closest_apple=rand()%snake_game_ia.Appleslist.size();
                other->obj_x=snake_game_ia.Appleslist[closest_apple].X;
                other->obj_y=snake_game_ia.Appleslist[closest_apple].Y;
            }
        }

        if (X==obj_x && Y==obj_y)
        {
            obj_reached=true;
            //check if apple eaten
            EatfoodSnake(*other,msg);
            dir=move(4,msg,other);
        }

        else
        {
            COORDINATE obj=Convert_To_Coordinate(obj_x,obj_y);
            //obj_already_eaten=true; //decommente ca et commente ta partie vers un obj random si tu veux test :)
            for (int i=0;i<snake_game_ia.Appleslist.size();i++)
            {
                if (obj_x == snake_game_ia.Appleslist[i].X && obj_y == snake_game_ia.Appleslist[i].Y)
                {
                    obj_already_eaten=false;
                    break;
                }
            }
            if(obj_already_eaten)
            {
                dir=move(3,msg,other);
            }
            else
            {
                //build the path
                goal.x=obj_x;
                goal.y=obj_y;

                path = duels::Astar(start, goal, true);

                duels::GridPoint next_Point=path[1];


                COORDINATE next_Head=Convert_To_Coordinate(next_Point.x,next_Point.y);
                //chose direction
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
                //update snake coordinates
                SnakeListOfCoordinate.insert(SnakeListOfCoordinate.begin(),next_Head);
                SnakeListOfCoordinate.pop_back();
            }
        }
        return dir;
        break;
    }

    }

};

bool snake_IA::isaliveSnake(COORDINATE Head, snake_IA other)
{
    bool state=true;
    //check if snake is in the window
    if(Head.X<0||Head.Y<0||Head.X>HEIGHT||Head.Y>WIDTH)
    {
        state=false;
    }
    if(Head.X>=WIDTH-15&&Head.Y<5)
    {
        state=false;
    }
    //check if snake doesn't eat the other
    for (int i=0;i<other.SnakeLength;i++)
    {
        if(Head.X==other.SnakeListOfCoordinate[i].X && Head.Y==other.SnakeListOfCoordinate[i].Y)
        {
            state=false;
        }
    }
    //check if snake doesn't eat itself
    for(int i=1;i<SnakeLength;i++)
    {
        if(Head.X==SnakeListOfCoordinate[i].X && Head.Y==SnakeListOfCoordinate[i].Y)
        {
            state=false;
        }
    }
    return state;
};


bool snake_IA::isaliveSnakebis(snake_IA other)
{
    COORDINATE Head=SnakeListOfCoordinate[0];
    bool state=true;
    //check if snake is in the window
    if(Head.X<0||Head.Y<0||Head.X>HEIGHT||Head.Y>=WIDTH)
    {
        state=false;
    }
    //check if snake doesn't eat the other
    for (int i=0;i<other.SnakeLength;i++)
    {
        if(Head.X==other.SnakeListOfCoordinate[i].X && Head.Y==other.SnakeListOfCoordinate[i].Y)
        {
            state=false;
        }
    }
    //check if snake doesn't eat itself
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
    for (int i=0;i<snake_game_ia.Appleslist.size();i++)
    {
        if ((SnakeListOfCoordinate[0].X == snake_game_ia.Appleslist[i].X)&&(SnakeListOfCoordinate[0].Y == snake_game_ia.Appleslist[i].Y)) //If the snake head is on one of the apples
        {
            //update the snake coordinates
            if (SnakeLength>=2) //We want to obtain the direction of the tail to add a new body part after the current tail
            {
                dx_back=SnakeListOfCoordinate[SnakeLength-1].X-SnakeListOfCoordinate[SnakeLength-2].X;
                dy_back=SnakeListOfCoordinate[SnakeLength-1].Y-SnakeListOfCoordinate[SnakeLength-2].Y;
            }
            SnakeLength+=1;
            COORDINATE coor2= Convert_To_Coordinate(SnakeListOfCoordinate[SnakeLength-2].X+dx_back,SnakeListOfCoordinate[SnakeLength-2].Y+dy_back);
            SnakeListOfCoordinate.push_back(coor2); //We add the new body part to the list of coordinates

            //generate new apple
            COORDINATE new_apple;
            new_apple.X=rand()%WIDTH;
            new_apple.Y=rand()%HEIGHT;
            while(new_apple.X>=WIDTH-15 && new_apple.Y<5)
            {
                new_apple.X=rand()%WIDTH;
                new_apple.Y=rand()%HEIGHT;
            }
            //check if the new apple is not in snakes
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
            //update the list of apples
            snake_game_ia.Appleslist.push_back(new_apple);

            //We erase from the list the apple that was eaten
            for (int i=0;i<snake_game_ia.Appleslist.size();i++)
            {
                if ((snake_game_ia.Appleslist[i].X == SnakeListOfCoordinate[0].X)&&(snake_game_ia.Appleslist[i].Y ==SnakeListOfCoordinate[0].Y))
                {
                    pos=i;
                }
            }
            snake_game_ia.Appleslist.erase(snake_game_ia.Appleslist.begin()+pos);

        }

    }

}
