import turtle as t
import time
from random import randrange


def statistic_output(food_apples=0, in_game_time=0):
    t.clear()
    t.ht()
    t.pu()
    t.goto(0, 320)
    t.write(arg="Apples: {:3.0f}, time: {:0.1f} s ".format(food_apples, in_game_time),
            move=False, align='center', font=("Calibri", 32, 'normal'))


print("Hello")
screen = t.Screen()
screen.bgcolor('#00d000')
screen.setup(1000, 730)
screen.tracer(0)

brd = t.Turtle()
brd.ht()
brd.pu()
brd.goto(-311, -311)
brd.pd()
for i in range(4):
    brd.fd(2 * 311)
    brd.left(90)

snake = []
for i in range(3):
    snake_segment = t.Turtle()
    snake_segment.shape('square')
    snake_segment.pu()
    if i > 0:
        snake_segment.color('#008cee')
    snake.append(snake_segment)

food = t.Turtle()
food.pu()
food.shape('circle')
food.color('#ff7700')
food.goto(randrange(-300, 300, 20), randrange(-300, 300, 20))

screen.onkeypress(lambda: snake[0].setheading(90), 'w')
screen.onkeypress(lambda: snake[0].setheading(270), 's')
screen.onkeypress(lambda: snake[0].setheading(0), 'd')
screen.onkeypress(lambda: snake[0].setheading(180), 'a')
screen.listen()

end_flag = False
apples = 0
game_time = 0
while True:
    if snake[0].distance(food) < 10:
        food.goto(randrange(-300, 300, 20), randrange(-300, 300, 20))
        snake_segment = t.Turtle()
        snake_segment.pu()
        snake_segment.color('#008cee')
        snake_segment.shape('square')
        snake.append(snake_segment)
        apples += 1
    for i in range(len(snake) - 1, 0, -1):
        y = snake[i - 1].ycor()
        x = snake[i - 1].xcor()
        if -301 < x < 301 and -301 < y < 301:
            snake[i].goto(x, y)
        else:
            screen.bgcolor('red')
            end_flag = True
            break
    snake[0].forward(20)
    for i in snake[1:]:
        i = i.position()
        if snake[0].distance(i) < 19:
            screen.bgcolor('red')
            end_flag = True
            break
    if end_flag:
        break

    screen.update()
    statistic_output(apples, game_time)
    game_time += 0.2
    time.sleep(0.2)

t.done()
