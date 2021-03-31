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
  snake1.SnakeListOfCoordinate = snake.Snake1ListOfCoordinate;
  snake2.SnakeListOfCoordinate = snake.Snake2ListOfCoordinate;
  snake1.SnakeLength = snake.Snake1Length;
  snake2.SnakeLength = snake.Snake2Length;
  for (int i=0;i<snake.Snake1Length;i++)
  {
      std::cout<<"";
      Print_Coord(snake.Snake1ListOfCoordinate[i]);
  }
  for (int i=0;i<snake1.SnakeLength;i++)
  {
      std::cout<<"=";
      Print_Coord(snake1.SnakeListOfCoordinate[i]);
  }

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


  while(snake1.isaliveSnakebis(snake2) && snake2.isaliveSnakebis(snake1))
  {

    // check if any regular winner
    if(!snake1.isaliveSnakebis(snake2)||!snake2.isaliveSnakebis(snake1))

    {
      std::cout<<"Dead"<<std::endl;
      if(!snake1.isaliveSnakebis(snake2))
      {
          game_io.registerVictory(Player::One, feedback1, feedback2);
          //std::cout<<"Dead"<<std::endl;
          game_io.sendDisplay(display,2);
      }

      else
      {
      game_io.registerVictory(Player::Two, feedback1, feedback2);
      game_io.sendDisplay(display,1);
      //std::cout<<"Dead"<<std::endl;
      }
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



#endif

      // artificial opponent: put your AI here



    //snake.EatfoodSnake1();
    //snake.EatfoodSnake2();

    //snake1.SnakeListOfCoordinate = snake.Snake1ListOfCoordinate;
    //snake2.SnakeListOfCoordinate = snake.Snake2ListOfCoordinate;
    //snake1.SnakeLength = snake.Snake1Length;
    //snake2.SnakeLength = snake.Snake2Length;

    int1=snake1.move(0,feedback1,&snake2);
    int2=snake2.move(0,feedback2,&snake1);

    //snake.Snake1ListOfCoordinate = snake1.SnakeListOfCoordinate;
    //snake.Snake2ListOfCoordinate = snake2.SnakeListOfCoordinate;
    snake.Snake1Length = snake1.SnakeLength;
    snake.Snake2Length = snake2.SnakeLength;

    //input2.dir=0;



#ifndef LOCAL_GAME
    }
#endif

    // update game state from input1 and input2
  snake.UpdateGame(int1,int2,snake1,snake2);

  display=snake.updateDisplay(display);

  game_io.sendDisplay(display);

  std::vector<feedbackMsg> FB=snake.updatefeedback(display);
  feedback1=FB[0];
  feedback2=FB[1];


}

  // final results
  std::cout<<"end game"<<std::endl;
  game_io.sendResult(display, feedback1, feedback2);
}

