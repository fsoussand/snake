//#ifndef SNAKE_GAME_H
//#define SNAKE_GAME_H
#include "/opt/duels/include/duels/client.h"
#include "/home/ecn/snake_project/snake_retrieve/snake/include/duels/snake/msg.h"
#include <sstream>
namespace duels {
namespace snake {


class Game: public duels::Client<inputMsg, feedbackMsg>
{
public:
  Game(int argc, char** argv, std::string name, int difficulty = 1)
    : Game(argc, argv, name, difficulty, "local_game") {}
  Game(int argc, char** argv, std::string name, std::string ip, int difficulty = 1)
      : Game(argc, argv, name, difficulty, ip) {}
private:
  Game(int argc, char** argv, std::string name, int difficulty, std::string ip)
      : duels::Client<inputMsg, feedbackMsg>(
      argc, argv, 100, name, difficulty, ip, "snake") {}
};
}
}
//#endif
