#define LOCAL_GAME  // to test the game AI with a dumb player AI

#include <duels/snake/msg.h>
#include <duels/snake/snake_game.h>
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
  int int1,int2;

  snake_IA snake1;
  snake_IA snake2;


  // simulation time
  const double dt(game_io.samplingTime());

  // build initial game state

  // build init message for display

  snake_game snake(display);

  //snake_IA snake1=snake_IA();
  //snake_IA snake2=snake_IA();
  display=snake.updateDisplay(display);
  game_io.sendDisplay(display);

  std::vector<feedbackMsg> FB=snake.constructFeedback(feedback1,feedback2);
  feedback1=FB[0];
  feedback2=FB[1];



#ifdef LOCAL_GAME
  game_io.initDisplay(init, "snake"); // add false at the end if you run the display in another terminal

  game_io.setLevel(1);
  game_io.sendDisplay(display);

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


    /* partie Lucas pour mangeage correct
    snake.testbouffagepommeSnake1();
    display=snake.updateDisplay(display);
    std::cout<<"display envoyé a python"<<std::endl;
    snake.Print_Coord(snake.Convert_To_Coordinate(display.x1,display.y1));
    game_io.sendDisplay(display);


    snake.EatfoodSnake1();
    snake.EatfoodSnake2();
    snake=snakeIA.move1(4,snake);

    snake=snakeIA.move2(3,snake);
    display=snake.updateDisplay(display);

    game_io.sendDisplay(display);*/



#endif

      // artificial opponent: put your AI here
    snake1.SnakeListOfCoordinate=snake.Snake1ListOfCoordinate;
    snake2.SnakeListOfCoordinate=snake.Snake2ListOfCoordinate;
    snake1.SnakeLength=snake.Snake1Length;
    snake2.SnakeLength=snake.Snake2Length;


    snake.EatfoodSnake1();
    snake.EatfoodSnake2();
    int1=snake1.move(3,feedback1,snake2);
    int2=snake2.move(1,feedback2,snake1);
    //input2.dir=0;
    snake.UpdateGame(int1,int2);

    display=snake.updateDisplay(display);

    game_io.sendDisplay(display);

    std::vector<feedbackMsg> FB=snake.updatefeedback(display);
    feedback1=FB[0];
    feedback2=FB[1];


#ifndef LOCAL_GAME
    }
#endif

    // update game state from input1 and input2


  }

  // final results
  game_io.sendResult(display, feedback1, feedback2);
}

