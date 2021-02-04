#define LOCAL_GAME  // to test the game AI with a dumb player AI

#include <duels/snake/msg.h>
#include<duels/snake/snake_game.h>
#include <duels/snake/snake_ia.h>
#ifdef LOCAL_GAME
#include <duels/local.h>

#else
#include <duels/server.h>
#endif

using duels::Player;
using namespace duels::snake;
#ifdef LOCAL_GAME
using GameIO = duels::LocalGame<initMsg, inputMsg, feedbackMsg, displayMsg, 100, 500>;
#else
using GameIO = duels::Server<initMsg, inputMsg, feedbackMsg, displayMsg, 100, 500>;
#endif


int main(int argc, char** argv)
{
  feedbackMsg feedback1, feedback2;
  initMsg init;
  inputMsg input1, input2;
  displayMsg display;
  GameIO game_io;

  // simulation time
  const double dt(game_io.samplingTime());

  // build initial game state

  // build init message for display

  snake_game snake(display);
  display=snake.updateDisplay(display);
  game_io.sendDisplay(display);

#ifdef LOCAL_GAME
  game_io.initDisplay(init, "snake"); // add false at the end if you run the display in another terminal
  game_io.setLevel(1);
  game_io.sendDisplay(display);


snake_IA snakeIA(3,snake);


#else
  game_io.initDisplay(argc, argv, init);
  const bool two_players = game_io.hasTwoPlayers();
#endif


  while(true)
  {
    // check if any regular winner
    if(!snake.isaliveSnake1bis()||!snake.isaliveSnake2bis())
    {
      if(!snake.isaliveSnake1bis()){
          game_io.registerVictory(Player::One, feedback1, feedback2);
          game_io.sendDisplay(display,2);
      }

      else
      game_io.registerVictory(Player::Two, feedback1, feedback2);
      game_io.sendDisplay(display,1);
    }


    // build display information

    //game_io.sendDisplay(display);



#ifndef LOCAL_GAME
    if(two_players)
    {
      if(!game_io.sync(feedback1, input1, feedback2, input2))
        break;
    }
    else
    {
      // sync with player 1, exits if needed
      if(!game_io.sync(feedback1, input1))
        break;


#else
      // write dumb player AI from feedback1 to input1


    snake.EatfoodSnake1();
    snake.EatfoodSnake2();
    snake=snakeIA.move1(4,snake);

    snake=snakeIA.move2(3,snake);
    display=snake.updateDisplay(display);

    game_io.sendDisplay(display);



#endif

      // artificial opponent: put your AI here


#ifndef LOCAL_GAME
    }
#endif

    // update game state from input1 and input2
    std::vector<feedbackMsg> FB=snake.updatefeedback(display);
    feedback1=FB[0];
    feedback2=FB[1];

  }

  // final results
  game_io.sendResult(display, feedback1, feedback2);
}

