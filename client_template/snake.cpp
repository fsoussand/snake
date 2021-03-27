#include <duels/snake/game.h>

using namespace duels::snake;

int main(int argc, char** argv)
{
  Game game(argc, argv, "Your name here",1);


  inputMsg input;
  feedbackMsg feedback;
  const auto timeout = game.timeout;

  while(game.get(feedback))
  {
    // write input in less than timeout
      input.dir=0;



    game.send(input);
  }
}
