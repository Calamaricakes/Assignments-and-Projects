from math import pi

EMPTY = '.'
BLACK = 'B'
WHITE = 'W'
CORNER = 'X'

#Change in coordinates for each direction where pos1 is column and pos2 is row
DIRECTIONS = {'UP': (0, -1), 'DOWN': (0, 1), 'LEFT': (-1, 0), 'RIGHT': (1, 0)}

#Constants for number of moves in which a certain event happens
END_PLACING_PHASE = 24
SHRINK_1 = 128
SHRINK_2 = 196
BOARD_SIZE = 8

BOARD_WEIGHTS = {0: 0, 7: 0, 1: pi/8, 6: pi/8, 2: pi/4, 5: pi/4, 3: pi/2, 4: pi/2}