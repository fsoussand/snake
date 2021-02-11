#include "include/duels/snake/snake_game.h"
#include <vector>
#include<iostream>


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
    return Is_in;
}
