from BoardMaker import *
from MazeSolver import *


if __name__ == "__main__":

    maze = create_board("board4.txt")

    maze.print_maze()

    # initialise and assign maze to maze solver
    maze_solver = MazeSolver(maze)

    solution_path = maze_solver.solve_maze()

    print()

    maze.print_solution(solution_path)


