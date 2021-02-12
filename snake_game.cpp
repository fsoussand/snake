#include "include/duels/snake/snake_game.h"
#include <duels/snake/msg.h>
#include "include/duels/snake/snake_ia.h"
#include<time.h>
#include<stdlib.h>
#include <vector>


#include <duels/local.h>

using duels::Player;
using namespace duels::snake;

snake_game::snake_game(){

}

snake_game::snake_game(displayMsg display) //constructor of snake_game : creates the display of the two snakes and the apples
{

    srand(time(NULL));
    display.x1=rand()%WIDTH;
    display.y1=rand()%HEIGHT;
    while (display.x1>=WIDTH-15 && display.y1<5)
    {
        display.x1=rand()%WIDTH;
        display.y1=rand()%HEIGHT;
    }
    display.x2=rand()%WIDTH;
    display.y2=rand()%HEIGHT;
    while (display.x2>=WIDTH-15 && display.y2<5)
    {
        display.x2=rand()%WIDTH;
        display.y2=rand()%HEIGHT;
    }
    for(int i=0;i<20;i++)
    {

        display.x[i]=rand()%WIDTH;
        display.y[i]=rand()%HEIGHT;
        while(display.x[i]>=WIDTH-15 && display.y[i]<5)
        {
            display.x[i]=rand()%WIDTH;
            display.y[i]=rand()%HEIGHT;
        }
        this->Appleslist.push_back(Convert_To_Coordinate(display.x[i],display.y[i]));
    }

    Snake1Length=1;
    Snake2Length=1;
    this->Snake1ListOfCoordinate.push_back(Convert_To_Coordinate(display.x1,display.y1));
    this->Snake2ListOfCoordinate.push_back(Convert_To_Coordinate(display.x2,display.y2));
}

COORDINATE snake_game::generate_random_apple()
{
    COORDINATE new_apple;
    new_apple.X=rand()%WIDTH;
    new_apple.Y=rand()%HEIGHT;
    while(new_apple.X>=WIDTH-15 && new_apple.Y<5)
    {
        new_apple.X=rand()%WIDTH;
        new_apple.Y=rand()%HEIGHT;
    }
    for(int i=0;i<Snake1Length-1;i++)
    {

            while(new_apple.X==Snake1ListOfCoordinate[i].X && new_apple.Y==Snake1ListOfCoordinate[i].Y)
    {
        new_apple.X=rand()%WIDTH;
        new_apple.Y=rand()%HEIGHT;
    }
    }
    for(int i=0;i<Snake2Length-1;i++)
    {

            while(new_apple.X==Snake2ListOfCoordinate[i].X && new_apple.Y==Snake2ListOfCoordinate[i].Y)
    {
        new_apple.X=rand()%WIDTH;
        new_apple.Y=rand()%HEIGHT;
    }
    }
    return new_apple;
}



void snake_game::EatfoodSnake1() //THe function that deals with the snake eating an apple
{
    int dx_back=0;
    int dy_back=0;
    for (int i=0;i<Appleslist.size();i++)
    {
        if ((Snake1ListOfCoordinate[0].X == Appleslist[i].X)&&(Snake1ListOfCoordinate[0].Y == Appleslist[i].Y)) //If the snake head is on one of the apples
        {

            if (Snake1Length>=2) //We want to obtain the direction of the tail to add a new body part after the current tail
            {
                dx_back=Snake1ListOfCoordinate[Snake1Length-1].X-Snake1ListOfCoordinate[Snake1Length-2].X;
                dy_back=Snake1ListOfCoordinate[Snake1Length-1].Y-Snake1ListOfCoordinate[Snake1Length-2].Y;
            }
            Snake1Length+=1;
            COORDINATE coor2= Convert_To_Coordinate(Snake1ListOfCoordinate[Snake1Length-2].X+dx_back,Snake1ListOfCoordinate[Snake1Length-2].Y+dy_back);
            Snake1ListOfCoordinate.push_back(coor2); //We add the new body part to the list of coordinates

            COORDINATE new_apple=generate_random_apple();
            Appleslist.push_back(new_apple);

            int pos;
            for (int i=0;i<Appleslist.size();i++)
            {
                if ((Appleslist[i].X == Snake1ListOfCoordinate[0].X)&&(Appleslist[i].Y ==Snake1ListOfCoordinate[0].Y))
                {
                    pos=i;
                }
            }
            Appleslist.erase(Appleslist.begin()+pos); //We erase from the list the apple that was eaten
        }
    }
}

void snake_game::EatfoodSnake2()
{
    int dx_back=0;
    int dy_back=0;
    for (int i=0;i<Appleslist.size();i++)
    {
        if ((Snake2ListOfCoordinate[0].X == Appleslist[i].X)&&(Snake2ListOfCoordinate[0].Y == Appleslist[i].Y))
        {

            if (Snake2Length>=2)
            {
                dx_back=Snake2ListOfCoordinate[Snake2Length-1].X-Snake2ListOfCoordinate[Snake2Length-2].X;
                dy_back=Snake2ListOfCoordinate[Snake2Length-1].Y-Snake2ListOfCoordinate[Snake2Length-2].Y;

            }
            Snake2Length+=1;
            COORDINATE coor2= Convert_To_Coordinate(Snake2ListOfCoordinate[Snake2Length-2].X+dx_back,Snake2ListOfCoordinate[Snake2Length-2].Y+dy_back);
            Snake2ListOfCoordinate.push_back(coor2);
            COORDINATE new_apple=generate_random_apple();
            Appleslist.push_back(new_apple);
            int pos;
            for (int i=0;i<Appleslist.size();i++)
            {
                if ((Appleslist[i].X == Snake2ListOfCoordinate[0].X)&&(Appleslist[i].Y ==Snake2ListOfCoordinate[0].Y))
                {
                    pos=i;
                }
            }
            Appleslist.erase(Appleslist.begin()+pos);
        }
    }

};

displayMsg snake_game::updateDisplay(displayMsg display)
{
    display.x1=Snake1ListOfCoordinate[0].X;
    display.y1=Snake1ListOfCoordinate[0].Y;
    display.x2=Snake2ListOfCoordinate[0].X;
    display.y2=Snake2ListOfCoordinate[0].Y;
    for(int i=0;i<Appleslist.size();i++)
    {
        display.x[i]=Appleslist[i].X;
        display.y[i]=Appleslist[i].Y;
    }
    return display;
}

std::vector<feedbackMsg> snake_game::updatefeedback(displayMsg display)
{
    feedbackMsg feedback1;
    feedbackMsg feedback2;
    std::vector<feedbackMsg> FB;
    feedback1.x1=display.x1;
    feedback1.y1=display.y1;
    feedback1.x2=display.x2;
    feedback1.y2=display.y2;
    feedback2.x1=display.x2;
    feedback2.y1=display.y2;
    feedback2.x2=display.x1;
    feedback2.y2=display.y1;
    for(int i=0;i<10;i++)
    {
        feedback1.x[i]=display.x[i];
        feedback1.y[i]=display.y[i];
        feedback2.x[i]=display.x[i];
        feedback2.y[i]=display.y[i];
    }
    FB.push_back(feedback1);
    FB.push_back(feedback2);
    return FB;

}

void snake_game::UpdateGame(inputMsg input1,inputMsg input2)
{
    int X1=Snake1ListOfCoordinate[0].X;
    int Y1=Snake1ListOfCoordinate[0].Y;
    int X2=Snake2ListOfCoordinate[0].X;
    int Y2=Snake2ListOfCoordinate[0].Y;
  switch(input1.dir)
  {
  case 0 : //moving up
      Y1=Y1-1;
      break;
  case 1: //moving down
      Y1=Y1+1;
      break;
  case 2: //moving right
      X1=X1+1;
      break;
  case 3: //moving left
      X1=X1-1;
      break;
  }
  switch(input2.dir)
  {
  case 0 : //moving up
      Y2=Y2-1;
      break;
  case 1: //moving down
      Y2=Y2+1;
      break;
  case 2: //moving right
      X2=X2+1;
      break;
  case 3: //moving left
      X2=X2-1;
      break;
  }
  COORDINATE Head1=Convert_To_Coordinate(X1,Y1);
  Snake1ListOfCoordinate.insert(Snake1ListOfCoordinate.begin(),Head1);
  COORDINATE Head2=Convert_To_Coordinate(X2,Y2);
  Snake2ListOfCoordinate.insert(Snake2ListOfCoordinate.begin(),Head2);
}

bool snake_game::moveX(int X,int obj_x, int *dir)
{
    bool move=false;
    if (X!=obj_x)
    {
        if (X - obj_x<0)
        {
            *dir=2;
        }
        else
        {
            *dir=3;
        }
        move=true;
    }
    return move;
}

bool snake_game::moveY(int Y,int obj_y, int *dir)
{
    bool move=false;
    if (Y!=obj_y)
    {
        if (Y - obj_y<0)
        {
            *dir=1;
        }
        else
        {
            *dir=0;
        }
        move=true;
    }
    return move;
}

COORDINATE snake_game::EvalPosHead(int X, int Y, int dir)
{
    COORDINATE Head;
    int pos_x=X;
    int pos_y=Y;
    switch(dir)
    {
    case 0:
        pos_y=Y-1;
        break;
    case 1:
        pos_y=Y+1;
        break;
    case 2:
        pos_x=X+1;
        break;
    case 3:
        pos_x=X-1;
    }
    Head = Convert_To_Coordinate(pos_x,pos_y);
    return Head;
}


bool snake_game::isaliveSnake1(COORDINATE Head)
{
  bool state=true;
  if(Head.X<0||Head.Y<0||Head.X>HEIGHT||Head.Y>=WIDTH)
  {
      state=false;
  }
  if(Head.X>=WIDTH-15&&Head.Y<5)
  {
      state=false;
  }
  for (int i=0;i<Snake2Length;i++)
  {
   if(Head.X==Snake2ListOfCoordinate[i].X && Head.Y==Snake2ListOfCoordinate[i].Y)
   {
       state=false;
   }
  }
  for(int i=1;i<Snake1Length;i++)
  {
      if(Head.X==Snake1ListOfCoordinate[i].X && Head.Y==Snake1ListOfCoordinate[i].Y)
      {
          state=false;
      }
  }
  return state;
};

void snake_game::go_target1(int obj_x,int obj_y)
{
    int dir;
    int X=Snake1ListOfCoordinate[0].X;
    int Y=Snake1ListOfCoordinate[0].Y;
    bool depla_x=false;
    bool depla_y=false;
    COORDINATE next_Head;
    bool is_alive;
    depla_x=moveX(X,obj_x,&dir);
    if (!depla_x)
    {
        depla_y=moveY(Y,obj_y,&dir);
    }
    next_Head = EvalPosHead(X,Y,dir);
    is_alive = isaliveSnake1(next_Head);
    //std::cout<<"alive"<<std::endl;
    //std::cout<<is_alive<<std::endl;
    if (is_alive)
    {
        Snake1ListOfCoordinate.insert(Snake1ListOfCoordinate.begin(),next_Head);
        Snake1ListOfCoordinate.pop_back();
    }
    else
    {
        if (depla_x)
        {
            depla_y=moveY(Y,obj_y,&dir);
        }
        next_Head = EvalPosHead(X,Y,dir);
        is_alive = isaliveSnake1(next_Head);
        if (is_alive)
        {
            Snake1ListOfCoordinate.insert(Snake1ListOfCoordinate.begin(),next_Head);
            Snake1ListOfCoordinate.pop_back();
        }
        else
        {
            std::vector<int> dir_available;
            for (int i=0;i<4;i++)
            {
                next_Head = EvalPosHead(X,Y,i);
                if (isaliveSnake1(next_Head))
                {
                    dir_available.push_back(i);
                }
            }
            if (dir_available.size()!=0)
            {
                dir=dir_available[rand()%dir_available.size()];
            }
            next_Head = EvalPosHead(X,Y,dir);
            Snake1ListOfCoordinate.insert(Snake1ListOfCoordinate.begin(),next_Head);
            Snake1ListOfCoordinate.pop_back();
        }
    }
}


bool snake_game::isaliveSnake2(COORDINATE Head)
{
  bool state=true;
  if(Head.X<0||Head.Y<0||Head.X>HEIGHT||Head.Y>WIDTH-1)
  {
      state=false;
  }
  if(Head.X>=WIDTH-15&&Head.Y<5)
  {
      state=false;
  }
  for (int i=1;i<Snake2Length;i++)
  {
   if(Head.X==Snake2ListOfCoordinate[i].X && Head.Y==Snake2ListOfCoordinate[i].Y)
   {
       state=false;
   }
  }
  for(int i=0;i<Snake1Length;i++)
  {
      if(Head.X==Snake1ListOfCoordinate[i].X && Head.Y==Snake1ListOfCoordinate[i].Y)
      {
          state=false;
      }
  }
  return state;
};

void snake_game::go_target2(int obj_x,int obj_y)
{
    int dir;
    int X=Snake2ListOfCoordinate[0].X;
    int Y=Snake2ListOfCoordinate[0].Y;
    bool depla_x=false;
    bool depla_y=false;
    COORDINATE next_Head;
    bool is_alive;
    depla_x=moveX(X,obj_x,&dir);
    if (!depla_x)
    {
        depla_y=moveY(Y,obj_y,&dir);
    }
    next_Head = EvalPosHead(X,Y,dir);
    is_alive = isaliveSnake2(next_Head);
    //std::cout<<"alive"<<std::endl;
    //std::cout<<is_alive<<std::endl;
    if (is_alive)
    {
        Snake2ListOfCoordinate.insert(Snake2ListOfCoordinate.begin(),next_Head);
        Snake2ListOfCoordinate.pop_back();
    }
    else
    {
        if (depla_x)
        {
            depla_y=moveY(Y,obj_y,&dir);
        }
        next_Head = EvalPosHead(X,Y,dir);
        is_alive = isaliveSnake2(next_Head);
        if (is_alive)
        {
            Snake2ListOfCoordinate.insert(Snake2ListOfCoordinate.begin(),next_Head);
            Snake2ListOfCoordinate.pop_back();
        }
        else
        {
            std::vector<int> dir_available;
            for (int i=0;i<4;i++)
            {
                next_Head = EvalPosHead(X,Y,i);
                if (isaliveSnake2(next_Head))
                {
                    dir_available.push_back(i);
                }
            }
            if (dir_available.size()!=0)
            {
                dir=dir_available[rand()%dir_available.size()];
            }
            next_Head = EvalPosHead(X,Y,dir);
            Snake2ListOfCoordinate.insert(Snake2ListOfCoordinate.begin(),next_Head);
            Snake2ListOfCoordinate.pop_back();
        }
    }
}

bool snake_game::isaliveSnake1bis()
{
    COORDINATE Head=Snake1ListOfCoordinate[0];
    bool state=true;
    if(Head.X<0||Head.Y<0||Head.X>HEIGHT||Head.Y>=WIDTH)
    {
        state=false;
    }
    for (int i=0;i<Snake2Length;i++)
    {
        if(Head.X==Snake2ListOfCoordinate[i].X && Head.Y==Snake2ListOfCoordinate[i].Y)
        {
            state=false;
        }
    }
    for(int i=1;i<Snake1Length-1;i++)
        {
            if(Head.X==Snake1ListOfCoordinate[i].X && Head.Y==Snake1ListOfCoordinate[i].Y)
            {
                state=false;
            }
        }
    return state;
};

bool snake_game::isaliveSnake2bis()
{
  COORDINATE Head=Snake2ListOfCoordinate[0];
  bool state=true;
  if(Head.X<0||Head.Y<0||Head.X>HEIGHT||Head.Y>=WIDTH)
  {
      state=false;
  }
  for (int i=1;i<Snake2Length-1;i++)
  {
   if(Head.X==Snake2ListOfCoordinate[i].X && Head.Y==Snake2ListOfCoordinate[i].Y)
   {
       state=false;
   }
  }
  for(int i=0;i<Snake1Length-1;i++)
  {
      if(Head.X==Snake1ListOfCoordinate[i].X && Head.Y==Snake1ListOfCoordinate[i].Y)
      {
          state=false;
      }
  }
  return state;
};

std::vector<feedbackMsg> snake_game::constructFeedback(feedbackMsg msg1, feedbackMsg msg2)
{
 for (int i=0;i<Appleslist.size();i++)
 {
     msg1.x[i]=Appleslist[i].X;
     msg1.y[i]=Appleslist[i].Y;
     msg2.x[i]=Appleslist[i].X;
     msg2.y[i]=Appleslist[i].Y;
 }

 msg1.x1=Snake1ListOfCoordinate[0].X;
 msg1.y1=Snake1ListOfCoordinate[0].Y;
 msg1.x2=Snake2ListOfCoordinate[0].X;
 msg1.y2=Snake2ListOfCoordinate[0].Y;

 msg2.x1=Snake2ListOfCoordinate[0].X;
 msg2.y1=Snake2ListOfCoordinate[0].Y;
 msg2.x2=Snake1ListOfCoordinate[0].X;
 msg2.y2=Snake1ListOfCoordinate[0].Y;

 std::vector<feedbackMsg> FB;
 FB.push_back(msg1);
 FB.push_back(msg2);
 return FB;

}



/*

COORDINATE snake_game::generate_random_apple(snake_IA snake1, snake_IA snake2)
{
    COORDINATE new_apple;
    new_apple.X=rand()%WIDTH;
    new_apple.Y=rand()%HEIGHT;
    while(new_apple.X>=WIDTH-15 && new_apple.Y<5)
    {
        new_apple.X=rand()%WIDTH;
        new_apple.Y=rand()%HEIGHT;
    }
    for(int i=0;i<snake1.SnakeLength-1;i++)
    {

            while(new_apple.X==snake1.SnakeListOfCoordinate[i].X && new_apple.Y==snake1.SnakeListOfCoordinate[i].Y)
    {
        new_apple.X=rand()%WIDTH;
        new_apple.Y=rand()%HEIGHT;
    }
    }
    for(int i=0;i<snake2.SnakeLength-1;i++)
    {

            while(new_apple.X==snake2.SnakeListOfCoordinate[i].X && new_apple.Y==snake2.SnakeListOfCoordinate[i].Y)
    {
        new_apple.X=rand()%WIDTH;
        new_apple.Y=rand()%HEIGHT;
    }
    }
    return new_apple;
}

void snake_game::EatfoodSnake(snake_IA snake,snake_IA other, feedbackMsg msg) //THe function that deals with the snake eating an apple
{
    int dx_back=0;
    int dy_back=0;
    for (int i=0;i<Appleslist.size();i++)
    {
        if ((snake.SnakeListOfCoordinate[0].X == Appleslist[i].X)&&(snake.SnakeListOfCoordinate[0].Y == Appleslist[i].Y)) //If the snake head is on one of the apples
        {

            if (snake.SnakeLength>=2) //We want to obtain the direction of the tail to add a new body part after the current tail
            {
                dx_back=snake.SnakeListOfCoordinate[snake.SnakeLength-1].X-snake.SnakeListOfCoordinate[snake.SnakeLength-2].X;
                dy_back=snake.SnakeListOfCoordinate[snake.SnakeLength-1].Y-snake.SnakeListOfCoordinate[snake.SnakeLength-2].Y;
            }
            snake.SnakeLength+=1;
            COORDINATE coor2= Convert_To_Coordinate(snake.SnakeListOfCoordinate[snake.SnakeLength-2].X+dx_back,snake.SnakeListOfCoordinate[snake.SnakeLength-2].Y+dy_back);
            snake.SnakeListOfCoordinate.push_back(coor2); //We add the new body part to the list of coordinates

            COORDINATE new_apple=generate_random_apple(snake,other);
            Appleslist.push_back(new_apple);

            int pos;
            for (int i=0;i<Appleslist.size();i++)
            {
                if ((Appleslist[i].X == snake.SnakeListOfCoordinate[0].X)&&(Appleslist[i].Y ==snake.SnakeListOfCoordinate[0].Y))
                {
                    pos=i;
                }
            }
            Appleslist.erase(Appleslist.begin()+pos); //We erase from the list the apple that was eaten
        }
    }
}

displayMsg snake_game::updateDisplay(displayMsg display,snake_game snake)
{

    display.x1=snake.Snake1ListOfCoordinate[0].X;
    display.y1=snake.Snake1ListOfCoordinate[0].Y;
    display.x2=snake.Snake2ListOfCoordinate[0].X;
    display.y2=snake.Snake2ListOfCoordinate[0].Y;
    for(int i=0;i<Appleslist.size();i++)
    {
        display.x[i]=Appleslist[i].X;
        display.y[i]=Appleslist[i].Y;
    }
    return display;
}

std::vector<feedbackMsg> snake_game::updatefeedback(displayMsg display)
{
    feedbackMsg feedback1;
    feedbackMsg feedback2;
    std::vector<feedbackMsg> FB;
    feedback1.x1=display.x1;
    feedback1.y1=display.y1;
    feedback1.x2=display.x2;
    feedback1.y2=display.y2;
    feedback2.x1=display.x2;
    feedback2.y1=display.y2;
    feedback2.x2=display.x1;
    feedback2.y2=display.y1;
    for(int i=0;i<10;i++)
    {
        feedback1.x[i]=display.x[i];
        feedback1.y[i]=display.y[i];
        feedback2.x[i]=display.x[i];
        feedback2.y[i]=display.y[i];
    }
    FB.push_back(feedback1);
    FB.push_back(feedback2);
    return FB;

}*/
