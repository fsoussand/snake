#ifndef DUELS_GRID_POINT_H
#define DUELS_GRID_POINT_H

#include <duels/snake/vector2d.h>
#include <duels/snake/grid.h>
#include <vector>
#include <memory>

// A 2D point on a grid that is able to generate its neighboors for A*

namespace duels
{

class GridPoint : public Vector2D<int>
{
    using GridPointPtr = std::unique_ptr<GridPoint>;

public:

  GridPoint(int _x=0, int _y=0) : Vector2D<int>(_x, _y) {}

  static void configure(Grid & _grid, bool _use_manhattan = true)
  {
      grid = &_grid;
      use_manhattan = _use_manhattan;
  }

  float h(const GridPoint &other) const
  {
    return static_cast<float>(distance(other, use_manhattan));
  }

  float distToParent() const {return 1.f;}

  // assume 0 is empty / free / available
  std::vector<GridPointPtr> children() const
  {
    std::vector<GridPointPtr> out;
    for(auto [dx, dy]: std::vector<std::pair<int,int>>({{-1,0},{1,0},{0,-1},{0,1}}))
    {
      if(grid->isFree(x + dx, y + dy))
        out.push_back(std::make_unique<GridPoint>(x + dx, y + dy));
    }
    return out;
  }

protected:
  // grid points share the same grid
  static Grid *grid;
  static bool use_manhattan;
};

#pragma once
duels::Grid * duels::GridPoint::grid;
bool duels::GridPoint::use_manhattan;


}

#endif // DUELS_GRID_POINT_H
