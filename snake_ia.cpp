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
    SnakeNumber=snake_number;

    ;
    switch (snake_number) {
    case 1:
    {
        switch(Level)
        case 0:
        {
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
            SnakeLength=1;
            SnakeListOfCoordinate.push_back(Convert_To_Coordinate(display.x1,display.y1));
            break;
        }
    case 2:
    {
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
            break;
        };
        SnakeLength=1;
        SnakeListOfCoordinate.push_back(Convert_To_Coordinate(display.x1,display.y1));
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
        SnakeLength=1;
        SnakeListOfCoordinate.push_back(Convert_To_Coordinate(display.x1,display.y1));
        break;
    }

    }



}

int snake_IA::move(int level,feedbackMsg msg,snake_IA *other){
    switch(level)
    {
    case 0:
    {
        int randomdir=rand()%4;
        inputMsg input;
        input.dir=randomdir;
        //return input;
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
        int dir=0;
        int X=msg.x1;
        int Y=msg.y1;
        int closest_apple=0;

        const int row(WIDTH);
        const int col(HEIGHT);

        duels::Grid grid(row,col);

        for(int i = 0; i < row-1; i++) //This will be used to construct the grid
        {
            for(int j=0;j<col-1;j++)
            {
                duels::GridPoint Point(i,j);
                COORDINATE Coor=Convert_To_Coordinate(i,j);

                if(isaliveSnake(Coor,*other))
                {
                    grid.cell(Point)=0; //0 Means the path is free


                }
                else
                {
                    grid.cell(Point)=2; //2 Means there's an obstacle
                }


            }
            //std::cout<<"go";
        }

        duels::GridPoint::configure(grid, true);

        std::cout<<"go";


        int distmin=std::pow((X-msg.x[closest_apple]),2)+std::pow((Y-msg.y[closest_apple]),2);
        if(obj_reached || obj_already_eaten)
        {

            for(int i=1;i<20;i++)
            {
                int dist=std::pow((X-msg.x[i]),2)+std::pow((Y-msg.y[i]),2);
                if (dist<distmin)
                {
                    distmin=dist;
                    closest_apple=i;
                }

            }
            obj_x = msg.x[closest_apple];
            obj_y = msg.y[closest_apple];
            obj_already_eaten=false;

        }
        std::cout<<obj_x;


        if (X==obj_x && Y==obj_y)
        {
            obj_reached=true;
            move(2,msg,other);
        }

        else
        {
            obj_reached=false;
            COORDINATE obj = Convert_To_Coordinate(obj_x,obj_y);
            /* if (!Test_Coord_in_List(obj,snake_game_ia.Appleslist))
            {
                obj_already_eaten=true;
                move(2,msg,other);
            }*/
            //else{
            std::cout<<dir;
            dir=go_target(obj_x,obj_y,msg,grid);
            std::cout<<dir;

            // }

        }
        //std::cout<<"objectif"<<std::endl;
        //snake.Print_Coord(snake.Convert_To_Coordinate(obj_x,obj_y));
        return dir;
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
        int otherdist;

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
                //std::cout<<grid.cell(Point);
            }
            // std::cout<<std::endl;
        }
        //std::cout<<std::endl;

        duels::GridPoint::configure(grid, true);

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

        if (obj_x==other->obj_x && obj_y==other->obj_y)
        {
            std::cout<<"Changed objective"<<std::endl;
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
            EatfoodSnake(*other,msg);


            dir=move(3,msg,other);
        }

        else
        {
            COORDINATE obj=Convert_To_Coordinate(obj_x,obj_y);
            /*if (!Test_Coord_in_List(obj,snake_game_ia.Appleslist))
            {
               std::cout<<"Wrong dir"<<std::endl;
                dir=move(3,msg,other);

        }*/
                    for (int i=0;i<snake_game_ia.Appleslist.size();i++)
            {
                    if (obj_x == snake_game_ia.Appleslist[i].X && obj_y == snake_game_ia.Appleslist[i].Y)
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

                    inputMsg input;

                    int dir;

                    const int rows(HEIGHT);
                    const int cols(WIDTH);

                    duels::Grid grid(rows, cols);
                    int X=msg.x1;
                    int Y=msg.y1;
                    std::vector<duels::GridPoint> path;
                    duels::GridPoint start(SnakeListOfCoordinate[0].X,SnakeListOfCoordinate[0].Y);
                    duels::GridPoint goal;

                    int closest_apple=0;

                    for(int i = 0; i < cols; i++) //This will be used to construct the grid
            {
                    for(int j=0;j<rows;j++)
            {
                    duels::GridPoint Point(i,j);
                    COORDINATE Coor=Convert_To_Coordinate(j,i);
                    if(isaliveSnake(Coor,*other))
            {
                    grid.cell(Point)=0; //0 Means the path is free

        }
                    else
            {
                    grid.cell(Point)=2; //2 Means there's an obstacle
        }
                    //std::cout<<grid.cell(Point);
        }
                    // std::cout<<std::endl;
        }
                    // std::cout<<std::endl;
                    // std::cout<<"=============="<<std::endl;
                    // std::cout<<std::endl;

                    duels::GridPoint::configure(grid, true);

                    if(obj_reached || obj_already_eaten)
            {

                    goal.x=msg.x[0];
                    goal.y=msg.y[0];
                    path = duels::Astar(start, goal, true);
                    closest_apple=0;
                    int distmin=path.size();
                    for(int i=1;i<20;i++)
            {
                    goal.x=msg.x[i];
                    goal.y=msg.y[i];
                    path = duels::Astar(start, goal, true);
                    int dist=path.size();
                    if (dist<distmin)
            {
                    distmin=dist;
                    closest_apple=i;

        }

        }
                    obj_x = msg.x[closest_apple];
                    obj_y = msg.y[closest_apple];
                    obj_already_eaten=false;
        }


                    if (X==obj_x && Y==obj_y)
            {
                    obj_reached=true;
                    EatfoodSnake(*other,msg);
                    dir=move(4,msg,other);
        }
                    else
            {
                    obj_reached=false;

                    COORDINATE obj = Convert_To_Coordinate(obj_x,obj_y);
                    if (!Test_Coord_in_List(obj,snake_game_ia.Appleslist))
            {
                    obj_already_eaten=true;
                    dir=move(4,msg,other);
        }
                    else
            {
                    goal.x=obj_x;
                    goal.y=obj_y;
                    //grid.cell(start)=0;
                    //grid.cell(goal)=0;
                    //duels::GridPoint::configure(grid,true);

                    path = duels::Astar(start, goal, true);

                    /* for(int i = 0; i < cols; i++) //This will be used to construct the grid
                        {
                            for(int j=0;j<rows;j++)
                            {
                                duels::GridPoint Point(i,j);
                                COORDINATE Coor=Convert_To_Coordinate(j,i);
                                for (i=0;i<path.size();i++)
                                {
                                    if (Point==path[i])
                                    {
                                        grid.cell(Point)=2;
                                    }
                                }

                                std::cout<<grid.cell(Point);
                            }
                            std::cout<<std::endl;
                        }
                        std::cout<<std::endl;
                        std::cout<<"=============="<<std::endl;
                        std::cout<<std::endl;*/

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
                    std::cout<<SnakeLength;
                    for (int i=0;i<SnakeLength;i++)
            {
                    std::cout<<"move=";
                    Print_Coord(SnakeListOfCoordinate[i]);
        }
                    std::cout<<"======="<<std::endl;

                    return dir;

                    //return input;
                    break;
        }
                    /*    inputMsg input;

                int dir;

                const int rows(HEIGHT);
                const int cols(WIDTH);

                duels::Grid grid(rows, cols);
                int X=msg.x1;
                int Y=msg.y1;

                COORDINATE a=this->SnakeListOfCoordinate[0];
                std::cout<<a.X<<std::endl;

                std::vector<duels::GridPoint> path;
                duels::GridPoint start(X,Y);
                duels::GridPoint goal;

                for(int i = 0; i < cols; i++) //This will be used to construct the grid
                {
                    for(int j=0;j<rows;j++)
                    {
                        duels::GridPoint Point(i,j);
                        COORDINATE Coor=Convert_To_Coordinate(j,i);
                        if(isaliveSnake(Coor,other))
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

                if(obj_reached || obj_already_eaten)
                {
                    goal.x=msg.x[0];
                    goal.y=msg.y[0];
                    path = duels::Astar(start, goal, true);
                    closest_apple=0;
                    int distmin=path.size();
                    for(int i=1;i<20;i++)
                    {
                        goal.x=msg.x[i];
                        goal.y=msg.y[i];
                        path = duels::Astar(start, goal, true);
                        int dist=path.size();
                        if (dist<distmin)
                        {
                            distmin=dist;
                            closest_apple=i;

                        }

                    }
                    obj_x = msg.x[closest_apple];
                    obj_y = msg.y[closest_apple];
                    obj_already_eaten=false;
                }

                if (X==obj_x && Y==obj_y)
                {
                    obj_reached=true;
                    move(4,msg,other);
                    closest_apple=0;
                    /*int distmin=path.size();
                    for(int i=1;i<20;i++)
                    {
                        goal.x=msg.x[i];
                        goal.y=msg.y[i];
                        path = duels::Astar(start, goal, true);
                        int dist=path.size();
                        if (dist<distmin)
                        {
                            distmin=dist;
                            closest_apple=i;

                        }

                    }
                    obj_x = msg.x[closest_apple];
                    obj_y = msg.y[closest_apple];
                    obj_already_eaten=false;
                }
                else
                {
                    obj_reached=false;
                }
                    COORDINATE obj = Convert_To_Coordinate(obj_x,obj_y);
                    if (!Test_Coord_in_List(obj,Appleslist))
                    {
                        obj_already_eaten=true;
                        move(3,msg,other);
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
                        //SnakeListOfCoordinate.insert(SnakeListOfCoordinate.begin(),next_Head);
                        //SnakeListOfCoordinate.pop_back();
                   // }

                return dir;
                break;
            }*/
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
                    /*    depla_x=moveX(msg, &dir);
            if (!depla_x)
            {
                depla_y=moveY(msg,&dir);
            }
            next_Head = EvalPosHead(X,Y,dir);
            is_alive = isaliveSnake(next_Head,other);
            //std::cout<<"alive"<<std::endl;
            //std::cout<<is_alive<<std::endl;
            if (is_alive)
            {
                SnakeListOfCoordinate.insert(SnakeListOfCoordinate.begin(),next_Head);
                SnakeListOfCoordinate.pop_back();
            }
            else
            {
                if (depla_x)
                {
                    depla_y=moveY(msg,&dir);
                }
                next_Head = EvalPosHead(X,Y,dir);
                is_alive = isaliveSnake(next_Head,other);
                if (is_alive)
                {
                    SnakeListOfCoordinate.insert(SnakeListOfCoordinate.begin(),next_Head);
                    SnakeListOfCoordinate.pop_back();
                }
                else
                {
                    std::vector<int> dir_available;
                    for (int i=0;i<4;i++)
                    {
                        next_Head = EvalPosHead(X,Y,i);
                        if (isaliveSnake(next_Head,other))
                        {
                            dir_available.push_back(i);
                        }
                    }
                    if (dir_available.size()!=0)
                    {
                        dir=dir_available[rand()%dir_available.size()];
                    }
                    next_Head = EvalPosHead(X,Y,dir);
                    SnakeListOfCoordinate.insert(SnakeListOfCoordinate.begin(),next_Head);
                    SnakeListOfCoordinate.pop_back();
                }
            }
            */

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
                    for (int i=0;i<snake_game_ia.Appleslist.size();i++)
            {
                    if ((SnakeListOfCoordinate[0].X == snake_game_ia.Appleslist[i].X)&&(SnakeListOfCoordinate[0].Y == snake_game_ia.Appleslist[i].Y)) //If the snake head is on one of the apples
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

                    snake_game_ia.Appleslist.push_back(new_apple);

                    int pos;
                    for (int i=0;i<snake_game_ia.Appleslist.size();i++)
            {
                    if ((snake_game_ia.Appleslist[i].X == SnakeListOfCoordinate[0].X)&&(snake_game_ia.Appleslist[i].Y ==SnakeListOfCoordinate[0].Y))
            {
                    pos=i;
        }
        }
                    snake_game_ia.Appleslist.erase(snake_game_ia.Appleslist.begin()+pos); //We erase from the list the apple that was eaten
        }
        }
        }
