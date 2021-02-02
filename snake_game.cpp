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
    display.x1=rand()%80; //Generates the head of the first snake
    display.y1=rand()%40;
    display.x2=rand()%80; //Generates the head of the second snake
    display.y2=rand()%40;
    for(int i=0;i<10;i++) //Generates the apples
    {
        display.x[i]=rand()%80;
        display.y[i]=rand()%40;
        this->Appleslist.push_back(Convert_To_Coordinate(display.x[i],display.y[i]));
    }

    Snake1Length=1;
    Snake2Length=1;
    this->Snake1ListOfCoordinate.push_back(Convert_To_Coordinate(display.x1,display.y1));
    this->Snake2ListOfCoordinate.push_back(Convert_To_Coordinate(display.x2,display.y2));
}



bool snake_game::isaliveSnake1() //return true if the snake 1 is still alive
{
  int X=Snake1ListOfCoordinate[0].X;
  int Y=Snake1ListOfCoordinate[0].Y;
  if(X<0||Y<0||X>80||Y>40) //Checks if the snake is beyond the window borders
  {
      return false;
  }
  for (int i=2;i<Snake1Length;i++) //Check is the snake ate itself
  {
   if(X==Snake1ListOfCoordinate[i].X && Y==Snake1ListOfCoordinate[i].Y)
   {
       return false;
   }
  }
  for(int i=0;i<Snake2Length;i++) //Check is the snake eats its opponent
  {
      if(X==Snake2ListOfCoordinate[i].X && Y==Snake2ListOfCoordinate[i].Y)
      {
          return false;
      }
  }
  return true;
};


bool snake_game::isaliveSnake2() //same function, but with the second snake
{
    int X=Snake2ListOfCoordinate[0].X;
    int Y=Snake2ListOfCoordinate[0].Y;
    if(X<0||Y<0||X>80||Y>40)
    {
        return false;
    }
    for (int i=2;i<Snake2Length;i++)
    {
     if(X==Snake2ListOfCoordinate[i].X && Y==Snake2ListOfCoordinate[i].Y)
     {
         return false;
     }
    }
    for(int i=0;i<Snake1Length;i++)
    {
        if(X==Snake1ListOfCoordinate[i].X && Y==Snake1ListOfCoordinate[i].Y)
        {
            return false;
        }
    }
    return true;
};

void snake_game::EatfoodSnake1(displayMsg display) //THe function that deals with the snake eating an apple
{
    int dx_back=0;
    int dy_back=0;
    for (int i=0;i<Appleslist.size();i++)
    {
        if ((display.x1 == display.x[i])&&(display.y1 == display.y[i])) //If the snake head is on one of the apples
        {

            if (Snake1Length>=2) //We want to obtain the direction of the tail to add a new body part after the current tail
            {
                dx_back=Snake1ListOfCoordinate[Snake1Length-1].X-Snake1ListOfCoordinate[Snake1Length-2].X;
                std::cout<<"dx "<<dx_back<<std::endl; //dx = 1/-1/0

                dy_back=Snake1ListOfCoordinate[Snake1Length-1].Y-Snake1ListOfCoordinate[Snake1Length-2].Y;
                std::cout<<"dy "<<dy_back<<std::endl;

            }
            Snake1Length+=1;
            COORDINATE coor;
            coor = Convert_To_Coordinate(display.x1,display.y1);
            COORDINATE coor2= Convert_To_Coordinate(Snake1ListOfCoordinate[Snake1Length-2].X+dx_back,Snake1ListOfCoordinate[Snake1Length-2].Y+dy_back);
            Snake1ListOfCoordinate.push_back(coor2); //We add the new body part to the list of coordinates
            std::cout<<"new corps"<<std::endl;
            for (int i=0;i<Snake1ListOfCoordinate.size();i++)
            {
                Print_Coord(Snake1ListOfCoordinate[i]);
            }
            int new_x=rand()%80;
            int new_y=rand()%40;
            COORDINATE new_pomme;
            new_pomme = Convert_To_Coordinate(new_x,new_y);
            Appleslist.push_back(new_pomme); //We add a new apple to the list
            int pos;
            for (int i=0;i<Appleslist.size();i++)
            {
                if ((Appleslist[i].X == coor.X)&&(Appleslist[i].Y ==coor.Y))
                {
                    pos=i;
                }
            }
            Appleslist.erase(Appleslist.begin()+pos); //We erase from the list the apple that was eaten
        }
    }
}

void snake_game::EatfoodSnake2(displayMsg display)
{
    int dx_back=0;
    int dy_back=0;
    for (int i=0;i<Appleslist.size();i++)
    {
        if ((display.x2 == display.x[i])&&(display.y2 == display.y[i]))
        {

            if (Snake2Length>=2)
            {
                dx_back=Snake2ListOfCoordinate[Snake2Length-1].X-Snake2ListOfCoordinate[Snake2Length-2].X;
                std::cout<<"dx "<<dx_back<<std::endl; //dx = 1/-1/0

                dy_back=Snake2ListOfCoordinate[Snake2Length-1].Y-Snake2ListOfCoordinate[Snake2Length-2].Y;
                std::cout<<"dy "<<dy_back<<std::endl;

            }
            Snake2Length+=1;
            COORDINATE coor;
            coor = Convert_To_Coordinate(display.x2,display.y2);
            COORDINATE coor2= Convert_To_Coordinate(Snake2ListOfCoordinate[Snake2Length-2].X+dx_back,Snake2ListOfCoordinate[Snake2Length-2].Y+dy_back);
            Snake2ListOfCoordinate.push_back(coor2);
            std::cout<<"new corps"<<std::endl;
            for (int i=0;i<Snake2ListOfCoordinate.size();i++)
            {
                Print_Coord(Snake2ListOfCoordinate[i]);
            }
            int new_x=rand()%80;
            int new_y=rand()%40;
            COORDINATE new_pomme;
            new_pomme = Convert_To_Coordinate(new_x,new_y);
            Appleslist.push_back(new_pomme);
            int pos;
            for (int i=0;i<Appleslist.size();i++)
            {
                if ((Appleslist[i].X == coor.X)&&(Appleslist[i].Y ==coor.Y))
                {
                    pos=i;
                }
            }
            Appleslist.erase(Appleslist.begin()+pos);
        }
    }

};


void snake_game::moveRandomlySnake1() //A function that gives a random direction to the snake
{
    int randomdir=rand()%4;
    int X=Snake1ListOfCoordinate[0].X;
    int Y=Snake1ListOfCoordinate[0].Y;
    switch (randomdir)
    {
    case 0 : //moving up
        Y=Y-1;
        break;
    case 1: //moving down
        Y=Y+1;
        break;
    case 2: //moving right
        X=X+1;
        break;
    case 3: //moving left
        X=X-1;
        break;
    }
    COORDINATE Head=Convert_To_Coordinate(X,Y);
    Snake1ListOfCoordinate.insert(Snake1ListOfCoordinate.begin(),Head);
}

bool snake_game::eat_itself1(int dir) //return true if the snake eat itself when doing a turn back
{
    switch (dir)
    {
    case 0 : //moving up
        if (Snake1ListOfCoordinate[0].Y+1==Snake1ListOfCoordinate[1].Y){return true;}
        break;
    case 1: //moving down
        if (Snake1ListOfCoordinate[0].Y-1==Snake1ListOfCoordinate[1].Y){return true;}
        break;
    case 2: //moving right
        if (Snake1ListOfCoordinate[0].X-1==Snake1ListOfCoordinate[1].X){return true;}
        break;
    case 3: //moving left
        if (Snake1ListOfCoordinate[0].X+1==Snake1ListOfCoordinate[1].X){return true;}
        break;
    }
    return false;
}

bool snake_game::eat_itself2(int dir)
{
    switch (dir)
    {
    case 0 : //moving up
        if (Snake2ListOfCoordinate[0].Y+1==Snake2ListOfCoordinate[1].Y){return true;}
        break;
    case 1: //moving down
        if (Snake2ListOfCoordinate[0].Y-1==Snake2ListOfCoordinate[1].Y){return true;}
        break;
    case 2: //moving right
        if (Snake2ListOfCoordinate[0].X-1==Snake2ListOfCoordinate[1].X){return true;}
        break;
    case 3: //moving left
        if (Snake2ListOfCoordinate[0].X+1==Snake2ListOfCoordinate[1].X){return true;}
        break;
    }
    return false;
}

/*void snake_game::testbouffagepommeSnake1()
{
    int randomdir=0;
    int X=Snake1ListOfCoordinate[0].X;
    int Y=Snake1ListOfCoordinate[0].Y;
    int obj_x = Appleslist[0].X;
    int obj_y = Appleslist[0].Y;
   // std::cout<<"Head avt deplacement"<<std::endl;
    //Print_Coord(Convert_To_Coordinate(X,Y));
    bool eat_itself;
    
    //if (X==obj_x && Y==obj_y)
    //{
    //    randomdir=random()%4;
    //    while(snake_game::eat_itself(randomdir))
    //    {
    //        randomdir=random()%4;
    //    }
    //}

    if (X != obj_x)
    {
        if (X - obj_x <0)
        {
            randomdir=2;
        }
        else
        {
            randomdir=3;
        }
    }
    else
    {
        if (Y - obj_y <0)
        {
            randomdir=1;
        }
        else
        {
            randomdir=0;
        }
    }
    switch (randomdir)
    {
    case 0 : //moving up
        Y=Y-1;
        break;
    case 1: //moving down
        Y=Y+1;
        break;
    case 2: //moving right
        X=X+1;
        break;
    case 3: //moving left
        X=X-1;
        break;
    }
    COORDINATE Head=Convert_To_Coordinate(X,Y);
    Snake1ListOfCoordinate.insert(Snake1ListOfCoordinate.begin(),Head);
    Snake1ListOfCoordinate.pop_back();
    std::cout<<"corps apres deplacement"<<std::endl;
    for (int i=0;i<Snake1ListOfCoordinate.size();i++)
    {
        Print_Coord(Snake1ListOfCoordinate[i]);
    }
    std::cout<<"Head apres deplacement"<<std::endl;
    Print_Coord(Head);
    std::cout<<"Pomme objectif"<<std::endl;
    Print_Coord(Appleslist[0]);

}
/*
void snake_game::go_target1(int obj_x,int obj_y) //the snake will go toward the coordinates (obj_x, obj_y)

{
    int dir;
    int X=Snake1ListOfCoordinate[0].X;
    int Y=Snake1ListOfCoordinate[0].Y;
    //std::cout<<"Head avant deplacement"<<std::endl;
    //Print_Coord(Snake1ListOfCoordinate[0]);
    if (X==obj_x && Y==obj_y)
    {
        dir=random()%4;
        while(snake_game::eat_itself1(dir))
        {
            dir=random()%4;
        }
    }

    if (X != obj_x)
    {
        if (X - obj_x <0)
        {
            dir=2;
        }
        else
        {
            dir=3;
        }
    }
    else
    {
        if (Y - obj_y <0)
        {
            dir=1;
        }
        else
        {
            dir=0;
        }
    }

    switch (dir)
    {
    case 0 : //moving up
        Y=Y-1;
        break;
    case 1: //moving down
        Y=Y+1;
        break;
    case 2: //moving right
        X=X+1;
        break;
    case 3: //moving left
        X=X-1;
        break;
    }
    COORDINATE Head=Convert_To_Coordinate(X,Y);
    Snake1ListOfCoordinate.insert(Snake1ListOfCoordinate.begin(),Head);
    Snake1ListOfCoordinate.pop_back();
    //std::cout<<"Head avant deplacement"<<std::endl;
    //Print_Coord(Head);
}
*/
void snake_game::go_target2(int obj_x,int obj_y)
{
    int dir;
    int X=Snake2ListOfCoordinate[0].X;
    int Y=Snake2ListOfCoordinate[0].Y;
    if (X==obj_x && Y==obj_y)
    {
        dir=random()%4;
        while(snake_game::eat_itself2(dir))
        {
            dir=random()%4;
        }
    }

    if (X != obj_x)
    {
        if (X - obj_x <0)
        {
            dir=2;
        }
        else
        {
            dir=3;
        }
    }
    else
    {
        if (Y - obj_y <0)
        {
            dir=1;
        }
        else
        {
            dir=0;
        }
    }
    switch (dir)
    {
    case 0 : //moving up
        Y=Y-1;
        break;
    case 1: //moving down
        Y=Y+1;
        break;
    case 2: //moving right
        X=X+1;
        break;
    case 3: //moving left
        X=X-1;
        break;
    }
    COORDINATE Head=Convert_To_Coordinate(X,Y);
    Snake2ListOfCoordinate.insert(Snake2ListOfCoordinate.begin(),Head);
    Snake2ListOfCoordinate.pop_back();
}


void snake_game::moveRandomlySnake2()
{
    int randomdir=rand()%4;
    int X=Snake2ListOfCoordinate[0].X;
    int Y=Snake2ListOfCoordinate[0].Y;
    switch (randomdir)
    {
    case 0 : //moving up
        Y=Y-1;
        break;
    case 1: //moving down
        Y=Y+1;
        break;
    case 2: //moving right
        X=X+1;
        break;
    case 3: //moving left
        X=X-1;
        break;
    }
    COORDINATE Head=Convert_To_Coordinate(X,Y);
    Snake2ListOfCoordinate.insert(Snake2ListOfCoordinate.begin(),Head);

};

bool snake_game::is_an_obstacle1(int dir) // dir = 0,1,2 or 3 : it represents the direction in which the snake is trying to go.
{
    COORDINATE Head=Convert_To_Coordinate(Snake1ListOfCoordinate[0].X,Snake1ListOfCoordinate[0].Y);
    switch(dir)
    {
    case 0:
        Head.Y-=1;
    case 1:
        Head.Y+=1;
    case 2:
        Head.X+=1;
    case 3:
        Head.X-=1;
    case 4:
        Head=Head;

    }

    if(Head.X<0||Head.X>40||Head.Y<0||Head.Y>80) //Beyond the grid dimensions
    {
        return true;
        std::cout<<"The snake wants to eat the wall"<<std::endl;
    }
    for(int i=1;i<Snake1Length-1;i++) //itself
    {
        if(Head.X==Snake1ListOfCoordinate[i].X && Head.Y==Snake1ListOfCoordinate[i].Y)
        {
            std::cout<<"The snake wants to eat its "<<i<<" body part"<<std::endl;
            return true;
        }
    }
    for(int i=0;i<Snake2Length-1;i++) //the other snake
    {
        if(Head.X==Snake2ListOfCoordinate[i].X && Head.Y==Snake2ListOfCoordinate[i].Y)
        {
            std::cout<<"The snake wants to eat the other "<<i<<" body part"<<std::endl;
            return true;
        }
    }
    return false;
};



int snake_game::avoid_obstacles1(int dir) //changes the direction to avoid an obstacle
{
    bool surrounded_by_obstacles = is_an_obstacle1(0) && is_an_obstacle1(1) && is_an_obstacle1(2) && is_an_obstacle1(3);
    if(surrounded_by_obstacles) return true;
    while(is_an_obstacle1(dir))
    {
       std::cout<<"Changing the direction"<<std::endl;
        dir=rand()%4;
    }
    return dir;

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

bool snake_game::isaliveSnake1bis(COORDINATE Head)
{
  bool state=true;
  if(Head.X<0||Head.Y<0||Head.X>80||Head.Y>40)
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
    is_alive = isaliveSnake1bis(next_Head);
    std::cout<<"alive"<<std::endl;
    std::cout<<is_alive<<std::endl;
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
        is_alive = isaliveSnake1bis(next_Head);
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
                if (isaliveSnake1bis(next_Head))
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

