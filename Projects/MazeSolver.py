from Square import *


class MazeSolver:
# Singleton class designed to solve simple maze puzzles

    maze_solver = None

    class __MazeSolver:

        def __init__(self, maze):
            self.maze = maze
            self.horizontal, self.vertical = maze.maze_dimensions()
            self.maze_entry = maze.entry_point()

        def assign_new_maze(self, new_maze):
            self.maze = new_maze

        def solve_maze(self):

        def construct_graph(self):

            for square in self.maze.squares:
                if self.traversable_square(square):

                    self.get_path_from_square(square)

        def traversable_square(self, square):

            if isinstance(square, Path) or\
                    isinstance(square, Entry) or\
                        isinstance(square, Exit):
                return True

            return False

        def get_path_from_square(self, square):

            position = square.return_position()

            # obtain a list of possible paths from the square
            possible_path_positions = self.possible_paths(position)

            while possible_path_positions:
                adjacent_position = possible_path_positions.pop()

                if self.square[adjacent_position]



        def possible_paths(self, position):
            possible_positions = []

            horizontal = position[0]
            vertical = position[1]

            # check up
            if self.within_maze( (horizontal, vertical - 1) ):
                possible_positions.append((horizontal, vertical - 1))

            # check down
            if self.within_maze( (horizontal, vertical + 1) ):
                possible_positions.append((horizontal, vertical + 1))

            # check right
            if self.within_maze( (horizontal + 1, vertical) ):
                possible_positions.append((horizontal + 1, vertical))

            # check left
            if self.within_maze( (horizontal - 1, vertical) ):
                possible_positions.append((horizontal - 1, vertical))

            return possible_positions

        def within_maze(self, position):

            pos_x, pos_y = position

            if 0 <= pos_x < self.horizontal and 0 <= pos_y < self.vertical:
                    return True

            return False





    def __init__(self, maze):

        if not MazeSolver.maze_solver:
            self.maze_solver = MazeSolver.__MazeSolver(maze)

        else:
            self.maze_solver.assign_new_maze(maze)

