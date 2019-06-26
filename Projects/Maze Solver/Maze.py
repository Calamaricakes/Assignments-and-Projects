from Square import *
from copy import deepcopy
from colorama import Fore


class Maze:

    # squares is a dictionary with the position as keys
    # and values as the Square objects at the position
    squares = {}

    def __init__(self, horizontal_dimension, vertical_dimension):
        self.horizontal_dimension = horizontal_dimension
        self.vertical_dimension = vertical_dimension
        self.entry_square = None

    def create_squares(self, maze_structure_txt):

        for vertical_index in range(self.vertical_dimension):
            for horizontal_index in range(self.horizontal_dimension):
                symbol = maze_structure_txt[vertical_index][horizontal_index]
                position = horizontal_index, vertical_index
                self.squares[position] = self._create_square(horizontal_index, vertical_index, symbol)
                if symbol is '~':
                    self.entry_square = self.squares[position]

    def _create_square(self, horizontal_position, vertical_position, symbol):

        # creates an object for every type then returns the object corresponding to the symbol
        # slightly inefficient, but cleaner than if...elif...else combination
        # garbage collector will take care of the rest.

        square_dictionary = {'@': Path(horizontal_position, vertical_position),
                             '+': Wall(horizontal_position, vertical_position),
                             '%': Exit(horizontal_position, vertical_position),
                             '~': Entry(horizontal_position, vertical_position)}

        return square_dictionary.get(symbol, None)

    def return_entry_square(self):
        return self.entry_square

    def maze_dimensions(self):
        return self.horizontal_dimension, self.vertical_dimension

    def print_maze(self):

        for vertical_index in range(self.vertical_dimension):
            for horizontal_index in range(self.horizontal_dimension):
                square = self.squares[horizontal_index, vertical_index]
                if isinstance(square, Path):
                    print(Fore.RED + '{}'.format(square.return_symbol()), end='')

                elif isinstance(square, Entry) or isinstance(square, Exit):
                    print(Fore.BLUE + '{}'.format(square.return_symbol()), end='')

                else:
                    print(Fore.GREEN + '{}'.format(square.return_symbol()), end='')

            print()

    def print_solution(self, path_solution):
    # path solution is a list of Square objects in sequence from entry to exit

        # creates a copy of the Square objects
        solution = deepcopy(self.squares)

        # replace all the Path squares with Solution squares in the copy
        for square in path_solution:

            position = horizontal_pos, vertical_pos = square.return_position()

            solution[position] = Solution(horizontal_pos, vertical_pos)

        for vertical_index in range(self.vertical_dimension):
            for horizontal_index in range(self.horizontal_dimension):
                square = solution[horizontal_index, vertical_index]

                if isinstance(square, Solution):
                    print(Fore.RED + '{}'.format(square.return_symbol()), end='')

                else:
                    print(Fore.GREEN + '{}'.format(square.return_symbol()), end='')
            print()


