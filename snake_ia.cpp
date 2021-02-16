#include "include/duels/snake/snake_ia.h"
#include <duels/snake/msg.h>
#include <stdlib.h>
#include <iostream>
#include "include/duels/snake/snake_game.h"
#include <vector>

#include "grid_point.h"
#include <duels/utils/rand_utils.h>
#include <map>
#include "a_star.h"



/* a supp quand on a reussi a modif tout ca
snake_IA::snake_IA(int Level, snake_game snake){
    /* switch(Level)
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
    case 4:
        std::cout<<"IA-level 4: A* measures the distances<<std::endl;

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
        snake.EatfoodSnake1();
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
            snake.EatfoodSnake1();
            snake=move1(2,snake);
        }
        else
        {
            obj1_reached=false;
            COORDINATE obj = snake.Convert_To_Coordinate(obj1_x,obj1_y);
            if (!snake.Test_Coord_in_List(obj,snake.Appleslist))
            {
                obj1_already_eaten=true;
                snake=move1(2,snake);
            }
            else
            {
                snake.go_target1(obj1_x,obj1_y);
            }
        }
        //std::cout<<"objectif"<<std::endl;
        //snake.Print_Coord(snake.Convert_To_Coordinate(obj_x,obj_y));
        break;
    }
    case 3:
    {
        const int rows(HEIGHT);
        const int cols(WIDTH);

        duels::Grid grid(rows, cols);
        int X=snake.Snake1ListOfCoordinate[0].X;
        int Y=snake.Snake1ListOfCoordinate[0].Y;
        std::vector<duels::GridPoint> path;
        duels::GridPoint start(X,Y);
        duels::GridPoint goal;

        for(int i = 0; i < cols; i++) //This will be used to construct the grid
        {
            for(int j=0;j<rows;j++)
            {
                duels::GridPoint Point(i,j);
                COORDINATE Coor=snake.Convert_To_Coordinate(i,j);
                if(snake.isaliveSnake1(Coor))
                {
                    grid.cell(Point)=0; //0 Means the path is free

                }
                else
                {
                    grid.cell(Point)=2; //2 Means there's an obstacle
                }
            }
        }

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


        duels::GridPoint::configure(grid, true);


        if (X==obj1_x && Y==obj1_y)
        {
            obj1_reached=true;
            snake.EatfoodSnake1();
            snake=move1(3,snake);
        }
        else
        {
            obj1_reached=false;
            COORDINATE obj = snake.Convert_To_Coordinate(obj1_x,obj1_y);
            if (!snake.Test_Coord_in_List(obj,snake.Appleslist))
            {
                obj1_already_eaten=true;
                snake=move1(3,snake);
            }
            else
            {
                goal.x=obj1_x;
                goal.y=obj1_y;

                path = duels::Astar(start, goal, true);
                duels::GridPoint next_Point=path[1];

                COORDINATE next_Head=snake.Convert_To_Coordinate(next_Point.x,next_Point.y);
                snake.Snake1ListOfCoordinate.insert(snake.Snake1ListOfCoordinate.begin(),next_Head);
                snake.Snake1ListOfCoordinate.pop_back();
            }
        }
        break;
    }
    case 4:
    {
        const int rows(HEIGHT);
        const int cols(WIDTH);

        duels::Grid grid(rows, cols);
        int X=snake.Snake1ListOfCoordinate[0].X;
        int Y=snake.Snake1ListOfCoordinate[0].Y;
        std::vector<duels::GridPoint> path;
        duels::GridPoint start(X,Y);
        duels::GridPoint goal;

        for(int i = 0; i < cols; i++) //This will be used to construct the grid
        {
            for(int j=0;j<rows;j++)
            {
                duels::GridPoint Point(i,j);
                COORDINATE Coor=snake.Convert_To_Coordinate(i,j);
                if(snake.isaliveSnake1(Coor))
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

        if(obj1_reached || obj1_already_eaten)
        {
            goal.x=snake.Appleslist[0].X;
            goal.y=snake.Appleslist[0].Y;
            path = duels::Astar(start, goal, true);
            closest_apple=0;
            int distmin=path.size();
            for(int i=1;i<snake.Appleslist.size();i++)
            {
                goal.x=snake.Appleslist[i].X;
                goal.y=snake.Appleslist[i].Y;
                path = duels::Astar(start, goal, true);
                int dist=path.size();
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
            snake.EatfoodSnake1();
            snake=move1(4,snake);
        }
        else
        {
            obj1_reached=false;
            COORDINATE obj = snake.Convert_To_Coordinate(obj1_x,obj1_y);
            if (!snake.Test_Coord_in_List(obj,snake.Appleslist))
            {
                obj1_already_eaten=true;
                snake=move1(4,snake);
            }
            else
            {
                goal.x=obj1_x;
                goal.y=obj1_y;

                path = duels::Astar(start, goal, true);
                duels::GridPoint next_Point=path[1];

                COORDINATE next_Head=snake.Convert_To_Coordinate(next_Point.x,next_Point.y);
                snake.Snake1ListOfCoordinate.insert(snake.Snake1ListOfCoordinate.begin(),next_Head);
                snake.Snake1ListOfCoordinate.pop_back();
            }
        }
        break;
    }
    case 5: // The snake tries to kill its opponent if it close enough
    {
        const int rows(HEIGHT);
        const int cols(WIDTH);

        duels::Grid grid(rows, cols);
        int X=snake.Snake1ListOfCoordinate[0].X;
        int Y=snake.Snake1ListOfCoordinate[0].Y;
        std::vector<duels::GridPoint> path;
        duels::GridPoint start(X,Y);
        duels::GridPoint goal;

        for(int i = 0; i < cols; i++) //This will be used to construct the grid
        {
            for(int j=0;j<rows;j++)
            {
                duels::GridPoint Point(i,j);
                COORDINATE Coor=snake.Convert_To_Coordinate(i,j);
                if(snake.isaliveSnake1(Coor))
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

        int distmin;

        if(obj1_reached || obj1_already_eaten)
        {
            goal.x=snake.Appleslist[0].X;
            goal.y=snake.Appleslist[0].Y;
            path = duels::Astar(start, goal, true);
            closest_apple=0;
             distmin=path.size();
            for(int i=1;i<snake.Appleslist.size();i++)
            {
                goal.x=snake.Appleslist[i].X;
                goal.y=snake.Appleslist[i].Y;
                path = duels::Astar(start, goal, true);
                int dist=path.size();
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

        GridPoint Head_opponent;
        Head_opponent.x=snake.Snake2ListOfCoordinate[0].X;
        Head_opponent.y=snake.Snake2ListOfCoordinate[0].Y;
        std::vector<GridPoint> path_to_opponent =duels::Astar(start,Head_opponent,true);
        if (path_to_opponent.size()<distmin)
        {
            obj1_x = Head_opponent.x;
            obj1_y = Head_opponent.y;
        }

        if (X==obj1_x && Y==obj1_y)
        {
            obj1_reached=true;
            snake.EatfoodSnake1();
            snake=move1(4,snake);
        }
        else
        {
            obj1_reached=false;
            COORDINATE obj = snake.Convert_To_Coordinate(obj1_x,obj1_y);
            if (!snake.Test_Coord_in_List(obj,snake.Appleslist))
            {
                obj1_already_eaten=true;
                snake=move1(4,snake);
            }
            else
            {
                goal.x=obj1_x;
                goal.y=obj1_y;

                path = duels::Astar(start, goal, true);
                duels::GridPoint next_Point=path[1];

                COORDINATE next_Head=snake.Convert_To_Coordinate(next_Point.x,next_Point.y);
                snake.Snake1ListOfCoordinate.insert(snake.Snake1ListOfCoordinate.begin(),next_Head);
                snake.Snake1ListOfCoordinate.pop_back();
            }
        }
        break;
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
        snake.EatfoodSnake2();
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
            snake.EatfoodSnake2();
            snake=move2(2,snake);
        }
        else
        {
            obj2_reached=false;
            COORDINATE obj = snake.Convert_To_Coordinate(obj2_x,obj2_y);
            if (!snake.Test_Coord_in_List(obj,snake.Appleslist))
            {
                obj2_already_eaten=true;
                snake=move2(2,snake);
            }
            else
            {
                snake.go_target2(obj2_x,obj2_y);
            }
        }
        //std::cout<<"objectif"<<std::endl;
        //snake.Print_Coord(snake.Convert_To_Coordinate(obj_x,obj_y));
        break;
    }
    case 3:
    {

        const int rows(HEIGHT);
        const int cols(WIDTH);

        duels::Grid grid(rows, cols);
        int X=snake.Snake2ListOfCoordinate[0].X;
        int Y=snake.Snake2ListOfCoordinate[0].Y;
        std::vector<duels::GridPoint> path;
        duels::GridPoint start(X,Y);
        duels::GridPoint goal;


        for(int i = 0; i < cols; i++) //This will be used to construct the grid
        {
            for(int j=0;j<rows;j++)
            {
                duels::GridPoint Point(i,j);
                COORDINATE Coor=snake.Convert_To_Coordinate(i,j);
                if(snake.isaliveSnake2(Coor))
                {
                    grid.cell(Point)=0; //0 Means the path is free

                }
                else
                {
                    grid.cell(Point)=2; //2 Means there's an obstacle
                }
            }
        }


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


        duels::GridPoint::configure(grid, true);


        if (X==obj2_x && Y==obj2_y)
        {
            obj2_reached=true;
            snake.EatfoodSnake2();
            snake=move2(3,snake);
        }
        else
        {
            obj2_reached=false;
            COORDINATE obj = snake.Convert_To_Coordinate(obj2_x,obj2_y);
            if (!snake.Test_Coord_in_List(obj,snake.Appleslist))
            {
                obj2_already_eaten=true;
                snake=move2(3,snake);
            }
            else
            {
                goal.x=obj2_x;
                goal.y=obj2_y;

                path = duels::Astar(start, goal, true);
                duels::GridPoint next_Point=path[1];

                COORDINATE next_Head=snake.Convert_To_Coordinate(next_Point.x,next_Point.y);
                snake.EatfoodSnake2();
                snake.Snake2ListOfCoordinate.insert(snake.Snake2ListOfCoordinate.begin(),next_Head);
                snake.Snake2ListOfCoordinate.pop_back();
            }
        }

        break;
    }
    }

    return snake;
};*/

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

int snake_IA::move(int level,feedbackMsg msg,snake_IA other){
    std::vector <COORDINATE> Appleslist;
   /* for (int i=0;i<20;i++)
    {
        Appleslist.push_back(Convert_To_Coordinate(msg.x[i],msg.y[i]));
    }*/
    switch(level)
    {
    std::cout<<Appleslist.size()<<std::endl;

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
        if(obj_reached)
        {
            obj_x = msg.x[randomapple];
            obj_y = msg.y[randomapple];
            obj_reached=false;
        }
        if(X==obj_x && Y==obj_y)
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
                    if (previousdir!=3)
                        randomdir=2;
                    else randomdir=0;
                }
                else
                {
                    if (previousdir!=2)
                        randomdir=3;
                    else randomdir=0;
                }
            }
            else
            {
                if (Y - obj_y <0)
                {
                    if (previousdir!=0)
                        randomdir=1;
                    else randomdir=2;
                }
                else
                {
                    if(previousdir!=1)
                        randomdir=0;
                    else randomdir=2;
                }
            }
        }
        input.dir=randomdir;
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

        for(int i = 0; i < col-1; i++) //This will be used to construct the grid
        {
            for(int j=0;j<row-1;j++)
            {
                duels::GridPoint Point(i,j);
                COORDINATE Coor=Convert_To_Coordinate(i,j);



                if(this->isaliveSnake(*this,Coor,other))
                {
                    grid.cell(Point)=0; //0 Means the path is free


                }
                else
                {
                    grid.cell(Point)=2; //2 Means there's an obstacle
                }


            }
            std::cout<<"go";
        }

        duels::GridPoint::configure(grid, true);

        std::cout<<"go";


        if(obj_reached || obj_already_eaten)
        {
            int distmin=std::pow((X-msg.x[closest_apple]),2)+std::pow((Y-msg.y[closest_apple]),2);
            for(int i=1;i<20;i++)
            {
                int dist=std::pow((X-msg.x[i]),2)+std::pow((Y-msg.y[i]),2);
                if (dist<distmin)
                {
                    distmin=dist;
                    closest_apple=i;
                }

            }
            obj_x = Appleslist[closest_apple].X;
            obj_y = Appleslist[closest_apple].Y;
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
            //COORDINATE obj = Convert_To_Coordinate(obj_x,obj_y);
            /*if (!Test_Coord_in_List(obj,Appleslist))
            {
                obj_already_eaten=true;
                move(2,msg,other);
            }
            else{*/
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
        inputMsg input;

        int dir;

        const int rows(HEIGHT);
        const int cols(WIDTH);

        duels::Grid grid(rows, cols);
        int X=msg.x1;
        int Y=msg.y1;
        std::vector<duels::GridPoint> path;
        duels::GridPoint start(X,Y);
        duels::GridPoint goal;

        int closest_apple=0;



        for(int i = 0; i < cols; i++) //This will be used to construct the grid
        {
            for(int j=0;j<rows;j++)
            {
                duels::GridPoint Point(i,j);
                COORDINATE Coor=Convert_To_Coordinate(j,i);
                if(isaliveSnake(*this,Coor,other))
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

            int distmin=std::pow((X-msg.x[0]),2)+std::pow((Y-msg.y[0]),2);
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


        if (X==obj_x && Y==obj_y)
        {
            //move(3,msg,other);
            int distmin=std::pow((X-msg.x[0]),2)+std::pow((Y-msg.y[0]),2);
            for(int i=0;i<20;i++)
            {
                int dist=std::pow((X-msg.x[i]),2)+std::pow((Y-msg.y[i]),2);
                if (dist<=distmin)
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
            /*if (!Test_Coord_in_List(obj,Appleslist))
            {
                obj_already_eaten=true;
                move(3,msg,other);
            }
            else
            {*/
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

        //return input;
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
                if(isaliveSnake(*this,Coor,other))
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
            goal.x=Appleslist[0].X;
            goal.y=Appleslist[0].Y;
            path = duels::Astar(start, goal, true);
            closest_apple=0;
            int distmin=path.size();
            for(int i=1;i<Appleslist.size();i++)
            {
                goal.x=Appleslist[i].X;
                goal.y=Appleslist[i].Y;
                path = duels::Astar(start, goal, true);
                int dist=path.size();
                if (dist<distmin)
                {
                    distmin=dist;
                    closest_apple=i;

                }

            }
            obj_x = Appleslist[closest_apple].X;
            obj_y = Appleslist[closest_apple].Y;
            obj_already_eaten=false;
        }

        if (X==obj_x && Y==obj_y)
        {
            obj_reached=true;
            move(4,msg,other);
        }
        else
        {
            obj_reached=false;
            COORDINATE obj = Convert_To_Coordinate(obj_x,obj_y);
            if (!Test_Coord_in_List(obj,Appleslist))
            {
                obj_already_eaten=true;
                move(4,msg,other);
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

                        dir=3;
                    }
                    else
                    {
                        dir=2;
                    }
                }
                else
                {
                    if (Y - next_Head.Y <0)
                    {

                        dir=1;
                    }
                    else
                    {
                        dir=0;
                    }
                }
            }
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

bool snake_IA::isaliveSnake(snake_IA snake,COORDINATE Head, snake_IA other)
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
    for(int i=1;i<snake.SnakeLength;i++)
    {
        if(Head.X==snake.SnakeListOfCoordinate[i].X && Head.Y==snake.SnakeListOfCoordinate[i].Y)
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
                if (grid.isFree(X+1,Y)) dir=2;
                else dir=0;
            }
            else
            {
                if (grid.isFree(X-1,Y)) dir =3;
                else dir=0;
            }
        }
        else
        {
            if (Y - obj_y <0)
            {
                if (grid.isFree(X,Y+1)) dir=1;
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
    COORDINATE Head=this->SnakeListOfCoordinate[0];
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
    for(int i=1;i<this->SnakeLength-1;i++)
    {
        if(Head.X==this->SnakeListOfCoordinate[i].X && Head.Y==this->SnakeListOfCoordinate[i].Y)
        {
            state=false;
        }
    }
    return state;
};


