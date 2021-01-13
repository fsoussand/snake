#!/usr/bin/env python
import sys
sys.path.insert(1, sys.argv[1])
from duels import Subscriber
import pygame
from time import time
import os


game = Subscriber() 
init_msg = game.get_init() 

#we define the different colors 
white = (255,255,255)
gray=(240,240,240)
yellow = (255,255,0)
magenta = (255,0,255)
cyan = (0,200,200)
blue = (0,0,255)
black = (0,0,0)
seashell = (255,245,238)
gold = (255,215,0)
pink = (255,192,203)
brown = (165,42,42)
purple = (160,32,240)
red = (213, 50, 80)
green=(50,213,80)

display_width = 800
display_height = 400

pygame.init()
fill_color=white


# prepare initial state / display
display = pygame.display.set_mode((display_width, display_height)) #we create a display of the size we want
pygame.display.set_caption('Snake Game') #we write a title 
<<<<<<< HEAD
display.fill(fill_color) #the display will be white
=======
display.fill(white) #the display screen will be white
>>>>>>> 69eb526ab32773a578124e64a7322dc4646f02ad
pygame.display.update()
apple=pygame.image.load("/home/ecn/snake_project/snake/images/Apple.png")
block_size = 10 #size of one square of the snake 
apple = pygame.transform.scale(apple, (block_size, block_size))
font_style = pygame.font.SysFont("arial", 25) #we define the style of writing
score_font = pygame.font.SysFont("arial", 15)
clock = pygame.time.Clock()

for i in range (int(display_width/10)):
    for j in range (int(display_height/10)):
        if (i%2==j%2):
            pygame.draw.rect(display, gray, [i*10, j*10,10,10])
        

def Player1_score(score): #the function that will show the score of Player1
    value = score_font.render("Player1 Score: " + str(score), True, white) #we display "Player1 Score : 3" in white
    display.blit(value, [650, 0])
def Player2_score(score):
    value = score_font.render("Player2 Score: " + str(score), True, white)
    display.blit(value, [650, 30])
    

#draw the snake, and remove the trajectory
def draw_snake1(block_size, snake_body1, Length_of_snake1):
    #if the length of the list snake_body is bigger than length_of_snake, it means no apple was eaten. We thus delete the tail from the list snake_body after having displayed it. 
    if len(snake_body1) > Length_of_snake1: 
        #we draw a rectangle on the display in pink. Its back left corner will be in 10*snake_body1[0][0], 10*snake_body1[0][1] and its width and height will be 10 
<<<<<<< HEAD
           pygame.draw.rect(display, fill_color, [10*snake_body1[0][0], 10*snake_body1[0][1],block_size,block_size]) 
=======
           if  int(snake_body1[0][0])%2== int(snake_body1[0][1])%2:
               pygame.draw.rect(display, gray,[block_size*snake_body1[0][0], block_size*snake_body1[0][1],block_size,block_size])
           else:
               pygame.draw.rect(display,white, [block_size*snake_body1[0][0], block_size*snake_body1[0][1],block_size,block_size])  
                   
               
>>>>>>> 69eb526ab32773a578124e64a7322dc4646f02ad
           
           del snake_body1[0] #we delete snake_body[0] from the list because it has been displayed
           #snake_body is constructed so that the tail is in position 0 and the head at the end of the list  
                     
    for x in snake_body1: #we keep displaying the rest of the snake, without deleting x from the list 
           pygame.draw.rect(display, green, [block_size*x[0], block_size*x[1], block_size, block_size])
         #  pygame.draw.circle(display,white,[10*x[0]-5,10*x[1]-5,block_size/5,block_size/5])

def draw_snake2(block_size, snake_body2, Length_of_snake2): #we draw the second snake in the same way as the first one
     if len(snake_body2) > Length_of_snake2:
<<<<<<< HEAD
            pygame.draw.rect(display, fill_color, [10*snake_body2[0][0], 10*snake_body2[0][1],block_size,block_size])
            del snake_body2[0]
=======
         if  int(snake_body2[0][0])%2== int(snake_body2[0][1])%2:
             pygame.draw.rect(display, gray,[block_size*snake_body2[0][0], block_size*snake_body2[0][1],block_size,block_size])
         else:
             pygame.draw.rect(display,white, [block_size*snake_body2[0][0], block_size*snake_body2[0][1],block_size,block_size])  
        
         del snake_body2[0]
>>>>>>> 69eb526ab32773a578124e64a7322dc4646f02ad
                       
     for x in snake_body2:
             pygame.draw.rect(display, cyan, [block_size*x[0], block_size*x[1], block_size, block_size])
             

def Choosing_Level():
    pygame.draw.rect(display, red,[200,100,400,200])
    Levelchoice = score_font.render("What level do you want to play ?", True, white)
    display.blit(Levelchoice, [225, 150])
    button_1 = BUTTON(300, 200, '1')
    button_2 = BUTTON(400, 200, '2')
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        Choosed_level=False
        while(not(Choosed_level)):
            if event.type == pygame.MOUSEBUTTONUP:
                if button_1.collidepoint(pygame.mouse.get_pos()):
                    display.blit(score_font.render("Choosed", True, white), [300, 200])
                    Choosed_level=True
                    Level=1
                elif button_2.collidepoint(pygame.mouse.get_pos()):
                    Choosed_level=True
                    Level=2
            clock.tick(60)
            pygame.display.update()
        return Level
        
def BUTTON(x,y, level):
    pygame.draw.circle(display, black,(x,y),25)
    Leveli = score_font.render(level, True, white)
    return display.blit(Leveli, (x,y))
        
        

#if __name__ == '__main__':
    
    # init display / structure from init_msg

snake1_Body = []
snake2_Body = []

Length_of_snake1 = 1
Length_of_snake2 = 1
            
    #init_msg.p1
    #init_msg.p2
    # init_msg.<other fields>
    

game.ready()

t0 = time()


while True:
    
    #Level=Choosing_Level()
    
    t0 = time()
    msg = game.refresh()
    
    
    

    
    for i in range(10): #we add the 10 apples to the display
<<<<<<< HEAD
        pygame.draw.rect(display,black,[10*msg.x[i],10*msg.y[i],block_size ,block_size])
=======
        display.blit(apple,[block_size*msg.x[i],block_size*msg.y[i],1,1])
        
        #pygame.draw.rect(display,black,[block_size*msg.x[i],block_size*msg.y[i],block_size ,block_size])
>>>>>>> 69eb526ab32773a578124e64a7322dc4646f02ad
        
    
    snake1_Head = []
    snake1_Head.append(msg.x1)#we use the display_msg from the C++ file to build the head of the snake  
    snake1_Head.append(msg.y1)
    snake1_Body.append(snake1_Head)#we add the head of the snake to the body list

    snake2_Head = []
    snake2_Head.append(msg.x2)
    snake2_Head.append(msg.y2)
    snake2_Body.append(snake2_Head)

    pygame.draw.rect(display, blue, [650, 0, 150, 50]) #we create a rectangle in which we will display the score
    Player1_score(Length_of_snake1 - 1) #we use the function Player_score defined earlier
    Player2_score(Length_of_snake2 - 1)

    draw_snake1(block_size,snake1_Body,Length_of_snake1) #we draw the snake with its head and delete the tail 
    draw_snake2(block_size,snake2_Body,Length_of_snake2)
        
    for i in range(10): #we check if one of the apples was eaten 
         if  msg.x1 == msg.x[i] and msg.y1 == msg.y[i]:
             Length_of_snake1 = Length_of_snake1+ 1 #snake1 ate an apple and its length is enhanced by one 
         if  msg.x2 == msg.x[i] and msg.y2 == msg.y[i]:
             Length_of_snake2 = Length_of_snake2 + 1
    
    print('the length of snake',len(snake1_Body), 'snake1_Body',snake1_Body,'snake1_Head',snake1_Head) #we print the length of each snake
    winner = msg.winner
    pygame.display.update()
    
    if winner:
        break
    
    
#update display from winner
print('(Python) Player {} has won!'.format(winner)) #end of the game, we print the name of the winner
pygame.display.update()
#pygame.quit()
