#include "include/duels/snake/Coordinate.h"
#include <vector>
#include<iostream>
#include "include/duels/snake/snake_game.h"


COORDINATE Convert_To_Coordinate(int x, int y)
{
    COORDINATE Coor;
    Coor.X=x;
    Coor.Y=y;
    return Coor;
}

void Print_Coord(COORDINATE coor)
{
    int x=coor.X;
    int y=coor.Y;
    std::cout<<"("<<x<<","<<y<<")"<<std::endl;
}

bool Test_Coord_in_List(COORDINATE coor,std::vector<COORDINATE> list)
{
    bool Is_in=false;
    for (int i=0;i<list.size();i++)
    {
        if ((coor.X==list[i].X) && ((coor.Y==list[i].Y)))
        {
            Is_in = true;
        }
    }
    //if (list.size()!=20) Is_in=false;

    //if(Is_in==false) std::cout<<"Not in list"<<std::endl;
    return Is_in;
} 

COORDINATE Where_is_next_head(int dir,COORDINATE previous_head)
{
    COORDINATE next_head;
    int X=previous_head.X;
    int Y=previous_head.Y;
    switch(dir)
    {
    case UP:
    {
        next_head=Convert_To_Coordinate(X,Y-1);
        break;
    }
    case DOWN:
    {
        next_head=Convert_To_Coordinate(X,Y+1);
        break;
    }
    case RIGHT:
    {
        next_head=Convert_To_Coordinate(X+1,Y);
        break;
    }
    case LEFT:
    {
        next_head=Convert_To_Coordinate(X-1,Y);
        break;
    }
    }
    return next_head;


}
