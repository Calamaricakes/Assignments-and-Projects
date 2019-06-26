from Square import *
from NodeQueue import *
from copy import copy


class MazeSolver:
# Singleton class designed to solve simple maze puzzles

    def __init__(self, maze):
        self.maze = maze
        self.horizontal, self.vertical = maze.maze_dimensions()
        self.maze_entry = maze.entry_square
        self.graph = {}
        self.construct_graph()

    def assign_new_maze(self, new_maze):
    # assign a maze to the solver, reinitialises the the variables to the new maze
        self.maze = new_maze
        self.horizontal, self.vertical = new_maze.maze_dimensions()
        self.maze_entry = new_maze.entry_square
        self.graph.clear()
        self.construct_graph()

    def solve_maze_bfs(self):
    # uses breadth first search to find the path from the starting square '~'
    # to the end square '%'
    # The input maze has a possibility of cycles
    # return: A list of Square objects in sequencial order from the start to the end
    #         of the maze

        start_square = self.maze.return_entry_square()

        if start_square is None:
            return False

        start_node = Node([start_square])

        # prepared the queue
        queue = NodeQueue()

        # pop the start node into the queue
        queue.enqueue(start_node)

        # since each step is of uniform cost, do not explore alternate paths
        explored = set()

        explored.add(start_square)

        while queue:

            node = queue.dequeue()

            # find the latest square in the current path
            previous_square = node.path[-1]

            # check each of the edges that can spawn from the previous square
            for adjacent_square in self.graph[previous_square]:

                # latter prevents cycles in the path
                # former prevents unnecessary node expansions
                if adjacent_square not in node.current_path() and\
                    adjacent_square not in explored:

                    explored.add(adjacent_square)

                    # copy the path that lead to the current square
                    extended_path = copy(node.current_path())

                    # add the square to the previous path,
                    # thereby forming a path to the current square
                    extended_path.append(adjacent_square)

                    new_node = Node(extended_path)

                    # solution is found,
                    # return the list of Square objects that lead to the exit
                    if isinstance(adjacent_square, Exit):

                        return new_node.path

                    # else keep looking
                    queue.enqueue(new_node)


    def construct_graph(self):
    # consructs the dictionary of edge from traversable squares in the graph
    # the graph could include cycles

        for square in self.maze.squares.values():
            if self.traversable_square(square):
                self.construct_edge_from_square(square)

    def traversable_square(self, square):
        if isinstance(square, Path) or \
                isinstance(square, Entry) or \
                isinstance(square, Exit):
            return True

        return False

    def construct_edge_from_square(self, square):
    # function determines the squares that can be reached from the current square
    # and adds it to the dictionary
    # Dictionary is of the form dict[Square] = [Square, Square,...]

        position = square.return_position()

        # obtain a list of possible paths from the square
        possible_path_positions = self.possible_paths(position)

        while possible_path_positions:
            adjacent_position = possible_path_positions.pop()

            adjacent_square = self.maze.squares[adjacent_position]

            if self.traversable_square(adjacent_square):

                # if the key already exists in the dict, just append the result to the list
                if self.graph.get(square, None):
                    self.graph[square].append(adjacent_square)

                # create a key value pair with a single item in the list
                else:
                    self.graph[square] = [adjacent_square]

    def possible_paths(self, position):
    # function generates a list of positions that could be reached from position
    # e.g. if position is at (0,0), it will generate the positions (1,0)(right) and (0,1)(down)
    # in a list

        possible_positions = []

        horizontal, vertical = position

        # check up
        if self.within_maze((horizontal, vertical - 1)):
            possible_positions.append((horizontal, vertical - 1))

        # check down
        if self.within_maze((horizontal, vertical + 1)):
            possible_positions.append((horizontal, vertical + 1))

        # check right
        if self.within_maze((horizontal + 1, vertical)):
            possible_positions.append((horizontal + 1, vertical))

        # check left
        if self.within_maze((horizontal - 1, vertical)):
            possible_positions.append((horizontal - 1, vertical))

        return possible_positions

    def within_maze(self, position):
    # checks if a position is within the bounds of the maze
        pos_x, pos_y = position

        if 0 <= pos_x < self.horizontal and 0 <= pos_y < self.vertical:
            return True

        return False

    def print_graph(self):
        for square, adjacent_squares in self.graph.items():
            print("{}: ".format(square.return_position()), end='')
            for adjacent_square in adjacent_squares:
                print(adjacent_square.return_position(), end=" ")
            print()


class Node:

    def __init__(self, path):
        self.path = path

    def current_path(self):
        return self.path


