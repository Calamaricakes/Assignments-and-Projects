from BoardMaker import *
from MazeSolver import *
from time import time


if __name__ == "__main__":

    maze = create_board("board4.txt")

    maze.print_maze()

    # initialise and assign maze to maze solver
    maze_solver = MazeSolver(maze)

    start = time()

    solution_path = maze_solver.solve_maze_bfs()

    end = time()

    print("\nTime taken: {}".format(end - start))

    maze.print_solution(solution_path)


