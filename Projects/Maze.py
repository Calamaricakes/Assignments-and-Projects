from Square import *


class Maze:

    squares = {}

    def __init__(self, horizontal_dimension, vertical_dimension):
        self.horizontal_dimension = horizontal_dimension
        self.vertical_dimension = vertical_dimension
        self.entry_point = None

    def create_squares(self, maze_structure_txt):

        for horizontal_index in range(self.horizontal_dimension):
            for vertical_index in range(self.vertical_dimension):
                symbol = maze_structure_txt[horizontal_index][vertical_index]
                position = horizontal_index, vertical_index
                self.squares[position] = self._create_square(horizontal_index, vertical_index, symbol)

    def _create_square(self, horizontal_position, vertical_position, symbol):

        if symbol == '+':
            return Wall(horizontal_position, vertical_position)
        elif symbol == '@':
            return Path(horizontal_position, vertical_position)
        elif symbol == '%':
            return Exit(horizontal_position, vertical_position)
        elif symbol == '~':
            self.entry_point = horizontal_position, vertical_position
            return Entry(horizontal_position, vertical_position)
        else:
            return None

    def print_maze(self):

        for horizontal_index in range(self.horizontal_dimension):
            for vertical_index in range(self.vertical_dimension):
                square = self.squares[horizontal_index, vertical_index]
                print(square.return_symbol(), end='')
            print()

    def return_entry_position(self):
        if self.entry_point is None:
            return None
        else:
            return self.entry_point

