﻿#include "include/duels/snake/snake_game.h"
#include <duels/snake/msg.h>
#include "include/duels/snake/snake_ia.h"
#include<time.h>
#include<stdlib.h>
#include <vector>


#include <duels/local.h>

using duels::Player;
using namespace duels::snake;

std::vector <COORDINATE> snake_game::Appleslist;


snake_game::snake_game(){

}

snake_game::snake_game(displayMsg display) //constructor of snake_game : creates the display of the two snakes and the apples
{

    srand(time(NULL));
    //create snake1 head
    display.x1=rand()%WIDTH;
    display.y1=rand()%HEIGHT;
    while (display.x1>=WIDTH-15 && display.y1<5)
    {
        display.x1=rand()%WIDTH;
        display.y1=rand()%HEIGHT;
    }
    //create snake2 head
    display.x2=rand()%WIDTH;
    display.y2=rand()%HEIGHT;
    while (display.x2>=WIDTH-15 && display.y2<5)
    {
        display.x2=rand()%WIDTH;
        display.y2=rand()%HEIGHT;
    }
    //create apples
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
    //initialize snake
    Snake1Length=1;
    Snake2Length=1;
    this->Snake1ListOfCoordinate.push_back(Convert_To_Coordinate(display.x1,display.y1));
    this->Snake2ListOfCoordinate.push_back(Convert_To_Coordinate(display.x2,display.y2));
}

COORDINATE snake_game::generate_random_apple()
{
    COORDINATE new_apple;
    //generate apple
    new_apple.X=rand()%WIDTH;
    new_apple.Y=rand()%HEIGHT;
    //check if in score part
    while(new_apple.X>=WIDTH-15 && new_apple.Y<5)
    {
        new_apple.X=rand()%WIDTH;
        new_apple.Y=rand()%HEIGHT;
    }
    //check if in snake1
    for(int i=0;i<Snake1Length-1;i++)
    {

        while(new_apple.X==Snake1ListOfCoordinate[i].X && new_apple.Y==Snake1ListOfCoordinate[i].Y)
        {
            new_apple.X=rand()%WIDTH;
            new_apple.Y=rand()%HEIGHT;
        }
    }
    //check if in snake2
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



displayMsg snake_game::updateDisplay(displayMsg display)
{
    //update positions snakes
    display.x1=Snake1ListOfCoordinate[0].X;
    display.y1=Snake1ListOfCoordinate[0].Y;
    display.x2=Snake2ListOfCoordinate[0].X;
    display.y2=Snake2ListOfCoordinate[0].Y;
    //update positions apples
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
    for(int i=0;i<Appleslist.size();i++)
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

void snake_game::UpdateGame(int int1,int int2,snake_IA snake1, snake_IA snake2)
{
    while(Appleslist.size()<20)
    {
        COORDINATE new_apple=generate_random_apple();
        Appleslist.push_back(new_apple);
    }

    int X1=Snake1ListOfCoordinate[0].X;
    int Y1=Snake1ListOfCoordinate[0].Y;
    int X2=Snake2ListOfCoordinate[0].X;
    int Y2=Snake2ListOfCoordinate[0].Y;
    switch(int1)
    {
    case UP : //moving up
        Y1=Y1-1;
        break;
    case DOWN: //moving down
        Y1=Y1+1;
        break;
    case RIGHT: //moving right
        X1=X1+1;
        break;
    case LEFT: //moving left
        X1=X1-1;
        break;

    }
    switch(int2)
    {
    case UP : //moving up
        Y2=Y2-1;
        break;
    case DOWN: //moving down
        Y2=Y2+1;
        break;
    case RIGHT: //moving right
        X2=X2+1;
        break;
    case LEFT: //moving left
        X2=X2-1;
        break;
    }
    //update snakes bodies
    COORDINATE Head1=Convert_To_Coordinate(X1,Y1);
    Snake1ListOfCoordinate.insert(Snake1ListOfCoordinate.begin(),Head1);
    Snake1ListOfCoordinate.pop_back();
    COORDINATE Head2=Convert_To_Coordinate(X2,Y2);
    Snake2ListOfCoordinate.insert(Snake2ListOfCoordinate.begin(),Head2);
    Snake2ListOfCoordinate.pop_back();
    snake1.SnakeListOfCoordinate = Snake1ListOfCoordinate;
    snake2.SnakeListOfCoordinate = Snake2ListOfCoordinate;
}

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


bool snake_game::EatfoodSnake(snake_IA *self,snake_IA *other, feedbackMsg msg) //THe function that deals with the snake eating an apple
{

    std::vector<COORDINATE> SnakeListOfCoordinate;
    int SnakeLength;
    bool has_eaten=false;
    if(self->SnakeNumber==1)
    {
        SnakeListOfCoordinate=Snake1ListOfCoordinate;
        SnakeLength=Snake1Length;
    }
    else
    {
     SnakeListOfCoordinate=Snake2ListOfCoordinate;
     SnakeLength=Snake2Length;
    }
    int dx_back=0;
    int dy_back=0;
    int pos;
    for (int i=0;i<Appleslist.size();i++)
    {
        if ((SnakeListOfCoordinate[0].X == Appleslist[i].X)&&(SnakeListOfCoordinate[0].Y == Appleslist[i].Y)) //If the snake head is on one of the apples
        {

            if (SnakeLength>=2) //We want to obtain the direction of the tail to add a new body part after the current tail
            {
                dx_back=SnakeListOfCoordinate[SnakeLength-1].X-SnakeListOfCoordinate[SnakeLength-2].X;
                dy_back=SnakeListOfCoordinate[SnakeLength-1].Y-SnakeListOfCoordinate[SnakeLength-2].Y;
            }
            SnakeLength+=1;
            COORDINATE coor2= Convert_To_Coordinate(SnakeListOfCoordinate[SnakeLength-2].X+dx_back,SnakeListOfCoordinate[SnakeLength-2].Y+dy_back);
            SnakeListOfCoordinate.push_back(coor2); //We add the new body part to the list of coordinates

            COORDINATE new_apple;
            new_apple.X=rand()%WIDTH;
            new_apple.Y=rand()%HEIGHT;
            while(new_apple.X>=WIDTH-15 && new_apple.Y<5)
            {
                new_apple.X=rand()%WIDTH;
                new_apple.Y=rand()%HEIGHT;
            }
            for(int i=0;i<SnakeLength-1;i++)
            {

                while(new_apple.X==SnakeListOfCoordinate[i].X && new_apple.Y==SnakeListOfCoordinate[i].Y)
                {
                    new_apple.X=rand()%WIDTH;
                    new_apple.Y=rand()%HEIGHT;
                }
            }
            for(int i=0;i<other->SnakeLength-1;i++)
            {

                while(new_apple.X==other->SnakeListOfCoordinate[i].X && new_apple.Y==other->SnakeListOfCoordinate[i].Y)
                {
                    new_apple.X=rand()%WIDTH;
                    new_apple.Y=rand()%HEIGHT;
                }
            }

            Appleslist.push_back(new_apple);


            for (int i=0;i<Appleslist.size();i++)
            {
                if ((Appleslist[i].X == SnakeListOfCoordinate[0].X)&&(Appleslist[i].Y ==SnakeListOfCoordinate[0].Y))
                {
                    pos=i;
                }
            }
            Appleslist.erase(Appleslist.begin()+pos); //We erase from the list the apple that was eaten
        }

    }
    if(self->SnakeNumber==1)
    {
        if(SnakeLength>Snake1Length) has_eaten=true;
        Snake1ListOfCoordinate=SnakeListOfCoordinate;
        Snake1Length=SnakeLength;
    }
    else
    {
        if(SnakeLength>Snake2Length) has_eaten=true;
        Snake2ListOfCoordinate=SnakeListOfCoordinate;
        Snake2Length=SnakeLength;
    }
    return has_eaten;

}

