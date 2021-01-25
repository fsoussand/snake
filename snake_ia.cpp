#include "include/duels/snake/snake_ia.h"
#include <duels/snake/msg.h>
#include <stdlib.h>
#include <iostream>
#include "include/duels/snake/snake_game.h"
#include <vector>


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
 /*   case 3:
    {
        int X=snake.Snake2ListOfCoordinate[0].X;
        int Y=snake.Snake2ListOfCoordinate[0].Y;
        int closest_apple=0;
        int distmin=std::pow((X-snake.Appleslist[closest_apple].X),2)+std::pow((Y-snake.Appleslist[closest_apple].Y),2);
        if(obj1_reached || obj1_already_eaten)
        {
            distmin=std::pow((X-snake.Appleslist[closest_apple].X),2)+std::pow((Y-snake.Appleslist[closest_apple].Y),2);
            for(unsigned int i=1;i<snake.Appleslist.size();i++)
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
            snake=move1(3,snake);
        }
        else
        {
            if(obj2_reached && obj2_x==obj1_x && obj2_y==obj1_y)
            {
                obj2_already_eaten=true;
            }
            obj1_reached=false;

            for (int i = 0; i < snake.Snake1Length-1; i++)
            {
                aStar_AISnake.map[snake.Snake1ListOfCoordinate[i].Y][snake.Snake1ListOfCoordinate[i].X] = true;

            }

            for (int i = 0; i < snake.Snake2Length-1; i++)
            {
                aStar_AISnake.map[snake.Snake2ListOfCoordinate[i].Y][snake.Snake2ListOfCoordinate[i].X] = true;
            }

            COORDINATE begin_point, end_point;

            begin_point = snake.Snake1ListOfCoordinate[0];
            end_point = snake.Appleslist[closest_apple] ;
            node* start=(node*)new node;
            start->x=begin_point.Y;
            start->y=begin_point.X;
            start->F=0;
            start->G=0;
            start->H=0;
            start->preNode = NULL;
            node* end=(node*)new node;
            end->x=end_point.Y;
            end->y=end_point.X;
            end->F=0;
            end->G=0;
            end->H=0;
            if(firstSearch)
            {
                aStar_AISnake.initMap();
                aStar_AISnake.AstarSerch(start,end);
                firstSearch = false;
            }
            COORDINATE newhead, temp;
            newhead = aStar_AISnake.pathFinal.back();
            int direction[4][2] = { { 0,1 },{ 0,-1 },{ 1,0 },{ -1,0 } };
            int break_num = 0;
            for(int i=0; i<4; i++)
            {
                temp = newhead;
                temp.X = temp.X + direction[i][0];
                temp.Y = temp.Y + direction[i][1];
                if (temp.X > 0 &&
                        (temp.X < (WIDTH-1)) && temp.Y > 0 && (temp.Y < (HEIGHT-1)) && !snake.is_an_obstacle1(4))
                {
                    break_num++;
                }
            }
            if(break_num >= 3)
            {
                snake.Snake1ListOfCoordinate.insert(snake.Snake1ListOfCoordinate.begin(), newhead);
                aStar_AISnake.pathFinal.erase(aStar_AISnake.pathFinal.end()-1);
            }
            else
            {
                aStar_AISnake.initMap();
                aStar_AISnake.AstarSerch(start,end);
                newhead = aStar_AISnake.pathFinal.back();
                snake.Snake1ListOfCoordinate.insert(snake.Snake1ListOfCoordinate.begin(), newhead);
                aStar_AISnake.pathFinal.erase(aStar_AISnake.pathFinal.end()-1);
            }
            delete start;
            delete end;
        }
    }*/

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

aStarFindPath::aStarFindPath()
{
    for (int i = 0; i < HEIGHT ; i++)
    {
        for (int j = 0; j < WIDTH ; j++)
        {
            map[i][j] = false;
        }
    }
    for (int i = 0; i < HEIGHT ; i++)
    {
        map[i][0] = true;
        map[i][WIDTH-1] = true;
    }
    for (int j = 0; j < WIDTH ; j++)
    {
        map[0][j] = true;
        map[HEIGHT-1][j] = true;
    }
}

void aStarFindPath::initMap()
{
    std::vector<COORDINATE>().swap(pathFinal);
    std::vector<node*>().swap(openList);
    std::vector<node*>().swap(closeList);
}

aStarFindPath::~aStarFindPath() {

}

int aStarFindPath::findMinNode()
{
    int index = 0;
    int size = openList.size();
    for(int i=1;i<size;++i)
    {
        if(openList[i]->F < openList[index]->F)
        {
            index = i;
        }
    }
    return index;
}

void aStarFindPath::findNeighbors(node* current,node* end)
{
    int openSize = openList.size();
    int closeSize = closeList.size();
    bool isInclude = false;
    //UP
    if(current->x-1>=0 && map[current->x-1][current->y]==0 )
    {
        for(int i =0;i<openSize;++i)
        {
            if(openList[i]->x == current->x-1 && openList[i]->y == current->y)
            {
                isInclude = true;
                break;
            }
        }
        for(int i =0;i<closeSize;++i)
        {
            if(closeList[i]->x == current->x-1 && closeList[i]->y == current->y)
            {
                isInclude = true;
                break;
            }
        }
        if(isInclude == false)
        {
            node *up = (node*)new node;
            up->x = current->x-1;
            up->y = current->y;
            //cout<<"up  "<<up->x<<"  "<<up->y<<endl;
            up->G = current->G+1;
            up->H = abs(end->x-up->x)+abs(end->y-up->y);
            up->preNode = current;
            openList.push_back(up);
        }
    }
    //DOWN
    isInclude = false;
    if(current->x+1<HEIGHT && map[current->x+1][current->y]==0 )
    {
        for(int i =0;i<openSize;++i)
        {
            if(openList[i]->x == current->x+1 && openList[i]->y == current->y)
            {
                isInclude = true;
                break;
            }
        }
        for(int i =0;i<closeSize;++i)
        {
            if(closeList[i]->x == current->x+1 && closeList[i]->y == current->y)
            {
                isInclude = true;
                break;
            }
        }
        if(isInclude == false)
        {
            node* down=(node*)new node;
            down->x = current->x+1;
            down->y = current->y;
            //cout<<"down  "<<down->x<<"  "<<down->y<<endl;
            down->G = current->G+1;
            down->H = abs(end->x-down->x)+abs(end->y-down->y);
            down->preNode = current;
            openList.push_back(down);
        }
    }
    //LEFT
    isInclude = false;
    if(current->y-1>=0 && map[current->x][current->y-1]==0)
    {
        for(int i =0;i<openSize;++i)
        {
            if(openList[i]->x == current->x && openList[i]->y == current->y-1)
            {
                isInclude = true;
                break;
            }
        }
        for(int i =0;i<closeSize;++i)
        {
            if(closeList[i]->x == current->x && closeList[i]->y == current->y-1)
            {
                isInclude = true;
                break;
            }
        }
        if(isInclude == false)
        {
            node* left=(node*)new node;
            left->x = current->x;
            left->y = current->y-1;
            //cout<<"left  "<<left->x<<"  "<<left->y<<endl;
            left->G = current->G+1;
            left->H = abs(end->x-left->x)+abs(end->y-left->y);
            left->preNode = current;
            openList.push_back(left);
        }
    }
    //RIGHT
    isInclude = false;
    if(current->y+1<WIDTH && map[current->x][current->y+1]==0)
    {
        for(int i =0;i<openSize;++i)
        {
            if(openList[i]->x == current->x && openList[i]->y == current->y+1)
            {
                isInclude = true;
                break;
            }
        }
        for(int i =0;i<closeSize;++i)
        {
            if(closeList[i]->x == current->x && closeList[i]->y == current->y+1)
            {
                isInclude = true;
                break;
            }
        }
        if(isInclude == false)
        {
            node* right=(node*)new node;
            right->x = current->x;

            right->y = current->y+1;
            //cout<<"right  "<<right->x<<"  "<<right->y<<endl;
            right->G = current->G+1;
            right->H = abs(end->x-right->x)+abs(end->y-right->y);
            right->preNode = current;
            openList.push_back(right);
        }
    }
}

void aStarFindPath::AstarSerch (node* start,node* end)
{
    openList.push_back(start);
    while(openList.size()>0)
    {
        int currentIndex = findMinNode();
        node* current = openList[currentIndex];
        openList.erase(openList.begin()+currentIndex);
        closeList.push_back(current);
        findNeighbors(current,end);
        for(int i =0;i<openList.size();++i)
        {
            if(openList[i]->x == end->x && openList[i]->y == end->y)
            {
                //cout<<"find it"<<endl;
                node* cur = openList[i];
                while(cur->preNode)
                {

                    COORDINATE currentWay;
                    currentWay.X =cur->y;
                    currentWay.Y =cur->x;
                    //cout<<""<<currentWay.x<<"   "<<currentWay.y<<endl;
                    this->pathFinal.push_back(currentWay);
                    cur=(cur->preNode);
                }
                return;
            }
        }
    }
}
