
class MazeSolver:
# Singleton class designed to solve simple maze puzzles

    maze_solver = None

    class __MazeSolver:

        def __init__(self, maze):
            self.maze = maze
            self.maze_entry = None

        def assign_new_maze(self, new_maze):
            self.maze = new_maze

        def find_entry_point(self):
            self.maze_entry = self.maze.entry_point()

        def solve_maze(self):

            self.find_entry_point()

        def construct_graph(self):
            


    def __init__(self, maze):

        if not MazeSolver.maze_solver:
            self.maze_solver = MazeSolver.__MazeSolver(maze)

        else:
            self.maze_solver.assign_new_maze(maze)

