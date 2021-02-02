#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
#include <duels/client.h>
#include <duels/snake/msg.h>
#include <sstream>
namespace duels {
namespace snake {
class Game: public duels::Client<inputMsg, feedbackMsg>
{
public:
  Game(std::string name, int difficulty = 1)
    : Game(name, difficulty, "127.0.0.1") {}
  Game(std::string name, std::string ip, int difficulty = 1)
      : Game(name, difficulty, ip) {}
private:
  Game(std::string name, int difficulty, std::string ip)
      : duels::Client<inputMsg, feedbackMsg>(
      25, name, difficulty, ip, "snake") {}
};
}
}
#endif