from BoardMaker import *
from MazeSolver import *


if __name__ == "__main__":

    maze = create_board("board1.txt")

    # initialise and assign maze to maze solver
    maze_solver = MazeSolver(maze)

