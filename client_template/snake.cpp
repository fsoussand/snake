<<<<<<< HEAD
#include </home/ecn/snake_project/snake/include/duels/snake/msg.h>
#include </home/ecn/snake_project/snake/include/duels/snake/game.h>
=======
#include <duels/snake/game.h>
>>>>>>> trial

using namespace duels::snake;

int main()
{
  Game game("snake",1);


  inputMsg input;
  feedbackMsg feedback;
  const auto timeout = game.timeout;

  while(game.get(feedback))
  {
    // write input in less than timeout



    game.send(input);
  }
}
