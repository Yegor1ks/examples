import turtle as t
import time


def Line(x0, y0, line_len, heading, pen_size=1, color="#662E1C"):
    t.ht()
    t.pu()
    t.goto(x0, y0)
    t.pd()
    t.color(color)
    t.pensize(pen_size)
    t.setheading(heading)
    t.forward(line_len)
    t.color("#662E1C")


def Circle(x0, y0, radius=75, pen_size=5):
    t.setheading(0)
    t.ht()
    t.pu()
    t.goto(x0, y0)
    t.pd()
    t.color("#DB9501")
    t.pensize(pen_size)
    t.circle(radius)
    t.color("#662E1C")


def Cross(x0, y0):
    Line(x0, y0, 212, 45, 5, "#C05805")
    Line(x0 + 150, y0, 212, 135, 5, "#C05805")


def gameUpdate():
    global x, win_positions, step, step1
    s.clear()
    s.tracer(0)
    x = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
    win_positions = [0, 0, 0, 0, 0, 0, 0, 0]
    s.bgcolor("#EBDCB2")
    t.color("#662E1C")
    for i in range(2):
        Line(-300, i * 200 - 100, 600, 0)
        Line(i * 200 - 100, -300, 600, 90)
    if step1 % 2 == 1:
        Circle(0, -75, 75, 5)
        x[1][1] = -1
        if step % 2 == 0:
            step += 1
    step1 += 1
    s.onclick(getPos)
    s.update()


def computerStep():
    global win_positions, x, step1
    x0, y0 = -1, -1
    counter_no_win = 0
    for i in range(7, -1, -1):
        if abs(win_positions[i]) == 2:
            if i < 3:
                for k in range(2, -1, -1):
                    if x[i][k] == 0:
                        x0 = i
                        y0 = k
            elif i < 6:
                for k in range(3):
                    if x[k][i % 3] == 0:
                        x0 = k
                        y0 = i % 3
            elif i == 6:
                for k in range(3):
                    if x[k][k] == 0:
                        x0 = k
                        y0 = k
            elif i == 7:
                for k in range(3):
                    if x[2 - k][k] == 0:
                        x0 = 2 - k
                        y0 = k
        else:
            counter_no_win += 1
    if counter_no_win == 8:
        k = -1
        for i in range(3):
            for j in range(3):
                if x[i][j] == 0 and k == -1:
                    x0 = i
                    y0 = j
                    k = 1
    Circle(y0 * 200 - 200, x0 * 200 - 275, 75, 5)
    x[x0][y0] = -1
    s.update()


def checkWin():
    global x, step, win_cross, win_circle, win_positions
    win = False
    counter_no_win = 0
    win_positions = [0, 0, 0, 0, 0, 0, 0, 0]
    for k in range(3):
        win_positions[0] += x[0][k]
        win_positions[1] += x[1][k]
        win_positions[2] += x[2][k]
        win_positions[3] += x[k][0]
        win_positions[4] += x[k][1]
        win_positions[5] += x[k][2]
        win_positions[6] += x[k][k]
        win_positions[7] += x[2-k][k]
    for i in range(8):
        if abs(win_positions[i]) == 3:
            win = True
    for i in range(3):
        for j in range(3):
            if x[i][j] == 0:
                counter_no_win += 1
    if win or counter_no_win == 0:
        time.sleep(1)
        s.clear()
        t.ht()
        s.bgcolor("#DDC5A2")
        t.pu()
        t.goto(0, 0)
        t.color("#662E1C")
        if win:
            if step % 2 == 0:
                win_cross += 1
                t.write(arg="   X won\nX: {:d}   O: {:d}".format(win_cross, win_circle),
                        align='center', font=("Tahoma", 50, 'normal'))
            else:
                win_circle += 1
                t.write(arg="   O won\nX: {:d}   O: {:d}".format(win_cross, win_circle),
                        align='center', font=("Tahoma", 50, 'normal'))
        else:
            t.write(arg="Nobody won\n X: {:d}   O: {:d}".format(win_cross, win_circle),
                    align='center', font=("Tahoma", 50, 'normal'))
        time.sleep(3)
        gameUpdate()


def getPos(x_click, y_click):
    global step, x, win_positions, step1
    if -300 < x_click < 300 and -300 < y_click < 300:
        x0 = round((x_click + 300) / 200 - 0.5)
        y0 = round((y_click + 300) / 200 - 0.5)
        if x[y0][x0] == 0:
            Cross(x0 * 200 - 275, y0 * 200 - 275)
            x[y0][x0] = 1
            s.update()
            checkWin()
            step += 1
            if step % 2 == 1:
                computerStep()
                checkWin()
                step += 1
        else:
            print("Занято!")
            print(x)
    return


s = t.Screen()
s.setup(600, 600)
step = 0
step1 = 0
x = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
win_positions = [0, 0, 0, 0, 0, 0, 0, 0]
win_cross = 0
win_circle = 0
while True:
    gameUpdate()
    t.done()
