#!/usr/bin/env python
import sys
sys.path.insert(1, sys.argv[1])
from duels import Subscriber

game = Subscriber()
init_msg = game.get_init()

white = (255,255,255)
yellow = (255,255,0)
magenta = (255,0,255)
cyan = (0,255,255)
blue = (0,0,255)
black = (0,0,0)
seashell = (255,245,238)
gold = (255,215,0)
pink = (255,192,203)
brown = (165,42,42)
purple = (160,32,240)
red = (213, 50, 80)

display_width = 800
display_height = 400


# prepare initial state / display
display = pygame.display.set_mode((display_width, display_height))
pygame.display.set_caption('Snake Game')
display.fill(pink)
pygame.display.update()
block_size = 10
font_style = pygame.font.SysFont("arial", 25)
score_font = pygame.font.SysFont("arial", 35)

def Player1_score(score):
    value = score_font.render("Player1 Score: " + str(score), True, cyan)
    display.blit(value, [500, 0])
def Player2_score(score):
    value = score_font.render("Player2 Score: " + str(score), True, cyan)
    display.blit(value, [500, 30])

#draw the snake, and remove the trajectory
def draw_snake1(block_size, snake_body1,Length_of_snake1):
    if len(snake_body1) > Length_of_snake1:
           pygame.draw.rect(display, pink, [10*snake_body1[0][0], 10*snake_body1[0][1],10,10])
           del snake_body1[0]
                     
    for x in snake_body1:
           pygame.draw.rect(display, red, [10*x[0], 10*x[1], block_size, block_size])

def draw_snake2(block_size, snake_body2,Length_of_snake2):
     if len(snake_body2) > Length_of_snake2:
            pygame.draw.rect(display, pink, [10*snake_body2[0][0], 10*snake_body2[0][1],10,10])
            del snake_body2[0]
                       
     for x in snake_body2:
             pygame.draw.rect(display, black, [10*x[0], 10*x[1], block_size, block_size])

class dict_to_obj(object):
  def __init__(self, adict):
    self.__dict__.update(adict)

class Listener:
    def __init__(self):
        self.fifo = '/tmp/duels_snake'
        if os.path.exists(self.fifo):
            os.remove(self.fifo)
            
        os.mkfifo(self.fifo)
        
    def read(self, display = False):
        with open(self.fifo) as fifo:
            data = yaml.load(fifo.read(),Loader=yaml.FullLoader)
            if display:
                print('(Python) Just read: {}'.format(data))
            return dict_to_obj(data)
        
if __name__ == '__main__':
    
    # main function
    
    listener = Listener()
    
    # init_msg has the same structure as C++ initMsg
    init_msg = listener.read(True)
    
    # init display / structure from init_msg

    snake1_Body = []
    snake2_Body = []

    Length_of_snake1 = 1
    Length_of_snake2 = 1
            
# init_msg.p1
# init_msg.p2
# init_msg.<other fields>


game.ready()
orient = 1
t0 = time()

turn = 2

iter_count = 0

while True:
    msg = game.refresh()
    if msg.winner:
        break
    
    # update display from fields
    else 
    # display_msg has the same structure as C++ displayMsg
        display_msg = listener.read(True)

        FPS=120
        FPSClock=pygame.time.Clock()
        pygame.display.update()

        pygame.draw.rect(display,gold,[10*display_msg.x[0],10*display_msg.y[0],10,10])

        snake1_Head = []
        snake1_Head.append(display_msg.x1)
        snake1_Head.append(display_msg.y1)
        snake1_Body.append(snake1_Head)

        snake2_Head = []
        snake2_Head.append(display_msg.x2)
        snake2_Head.append(display_msg.y2)
        snake2_Body.append(snake2_Head)

        Player1_score(Length_of_snake1 - 1)
        Player2_score(Length_of_snake2 - 1)
        pygame.display.update()

        draw_snake1(block_size, snake1_Body,Length_of_snake1)
        draw_snake2(block_size, snake2_Body, Length_of_snake2)

        if  display_msg.x1 == display_msg.x[0] and display_msg.y1 == display_msg.y[0]:
            Length_of_snake1 = Length_of_snake1+ 1
        if  display_msg.x2 == display_msg.x[0] and display_msg.y2 == display_msg.y[0]:
            Length_of_snake2 = Length_of_snake2 + 1

        print('the length of snake1',len(snake1_Body), 'snake1_Body',snake1_Body,'snake1_Head',snake1_Head)
        print('the length of snake2',len(snake2_Body), 'snake1_Body',snake2_Body,'snake2_Head',snake2_Head)

        msg.winner = display_msg.winner
        pygame.display.update()
        

    display.fill(pink)
    font_style = pygame.font.SysFont("arial", 50)
    result = font_style.render("Player " + str(msg.winner) + " win!", True, gold)
    display.blit(result, [123, 222])
    
    
# update display from winner
 print('(Python) Player {} has won!'.format(msg.winner))
    pygame.display.update()
    pygame.quit()
