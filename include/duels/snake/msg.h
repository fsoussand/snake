#ifndef SNAKE_MSG_H
#define SNAKE_MSG_H
#include <sstream>
#include <duels/game_state.h>

namespace duels {
namespace snake {
struct initMsg
{
  std::string toYAMLString(std::string p1, std::string p2) const 
  {
    std::stringstream ss;
    ss << "p1: " << p1;
    ss << "\np2: " << p2;
    return ss.str();
  }
};

struct inputMsg
{
  char dir;
};

struct feedbackMsg
{
  int x1; int y1; int x2; int y2; int x[20]; int y[20];
  feedbackMsg() {}
  feedbackMsg(int _x1, int _y1, int _x2, int _y2, int _x[20], int _y[20])
    : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
  State state = State::ONGOING;
};

struct displayMsg
{
  int x1; int y1; int x2; int y2; int x[20]; int y[20];
  std::string toYAMLString(int winner) const 
  {
    std::stringstream ss;
    ss << "winner: " << winner;
    ss << "\nx1: " << x1;
    ss << "\ny1: " << y1;
    ss << "\nx2: " << x2;
    ss << "\ny2: " << y2;
    ss << "\nx: " << "[";
    for(size_t i=0; i < 20; ++i)
      ss << x[i] << (i == 19?"]":", ");
    ss << "\ny: " << "[";
    for(size_t i=0; i < 20; ++i)
      ss << y[i] << (i == 19?"]":", ");
    return ss.str();
  }
};

}
}
#endif
