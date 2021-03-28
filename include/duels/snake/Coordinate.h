#ifndef COORDINATE_H
#define COORDINATE_H

#include <vector>
#include<iostream>

struct COORDINATE
{
    int X;
    int Y;
};

COORDINATE Convert_To_Coordinate(int, int);
void Print_Coord(COORDINATE);
bool Test_Coord_in_List(COORDINATE,std::vector<COORDINATE>);
COORDINATE Where_is_next_head(int,COORDINATE);

#endif
