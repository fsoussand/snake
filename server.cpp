#define LOCAL_GAME  // to test the game AI with a dumb player AI

#include <duels/snake/msg.h>
#include<snake_game.h>
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
  GameIO game_io;
  // simulation time
  const double dt(game_io.samplingTime());

  // build initial game state
 /* std::string p1,p2;
  std::cout<<"What's the first player's name ?"<<std::endl;
  std::cin>>p1;
  std::cout<<std::endl<<"What's the second player's name ?"<<std::endl;
  std::cin>>p2;

   init.toYAMLString(p1,p2);*/
  
  // build init message for display
  srand(time(NULL));
  displayMsg display;
  display.x1=rand()%80;
  display.y1=rand()%40;
  display.x2=rand()%80;
  display.y2=rand()%40;
  for(int i=0;i<10;i++)
  {
      display.x[i]=rand()%80;
      display.y[i]=rand()%40;
  }

  snake_game snake(display);


#ifdef LOCAL_GAME
  game_io.initDisplay(init, "snake");  // add false at the end if you run the display in another terminal
  game_io.setLevel(1);
  game_io.sendDisplay(display);



#else
  game_io.initDisplay(argc, argv, init);
  const bool two_players = game_io.hasTwoPlayers();
#endif


  while(true)
  {
    // check if any regular winner
    if(false)
    {
      //if(...)
      game_io.registerVictory(Player::One, feedback1, feedback2);
      //else
      game_io.registerVictory(Player::Two, feedback1, feedback2);
    }


    // build display information

    //game_io.sendDisplay(display);

    std::cout<<"About to move"<<std::endl;
    snake.moveRandomlySnake1();
    display=snake.updateDisplay(display);
    game_io.sendDisplay(display);
    





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

  //
  //  feedback=snake.moveRandomlySnake2(feedback);
    //feedback1=feedback;
   // feedback2=feedback;
   // feedback2.x1,feedback2.y1,feedback2.x2,feedback2.y2=feedback2.x2,feedback2.y2,feedback2.x1,feedback2.y1;
   // display=snake.updateDisplay(feedback);
   // game_io.sendDisplay(display);

#endif

      // artificial opponent: put your AI here


#ifndef LOCAL_GAME
    }
#endif

    // update game state from input1 and input2
    
    
    
    
  }

  // final results
  game_io.sendResult(display, feedback1, feedback2);
}
