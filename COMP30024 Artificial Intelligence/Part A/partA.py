class InputReader:
    
    def make_square(self, char, col, row):
        
        if char is '-':
            return Square(col, row, char)

        elif char is 'X':
            return Corner(col, row, char)

        elif char is 'O':
            return White(col, row, char)

        elif char is '@':
            return Black(col, row, char)

        return None

    def read_line(self, board, cur_row, cur_col):
        line = input()
        split_line = line.split()
        board.size = len(split_line)

        #Make the squares
        for char in split_line:
            board.board[(cur_col, cur_row)] = self.make_square(char, cur_col, cur_row)

            cur_col += 1

    def read_input(self, board):

        cur_col = 0
        cur_row = 0

        #read a line first to get the size of the board
        self.read_line(board, cur_row, cur_col)
        cur_row += 1

        while cur_row < board.size:

            self.read_line(board, cur_row, cur_col)
            cur_row += 1


class Board:

    size = 0

    def __init__(self):
        self.board = {}

    def __str__(self):
        
        str = ""
        for row in range(self.size):
            for col in range(self.size):
                str += self.board[col, row].symbol
                str += " "

            str += "\n"

        return str

class Square:

    def __init__(self, col, row, symbol):
        self.position = (col, row)
        self.symbol = symbol

class White(Square):

    def __init__(self, col, row, symbol):
        super().__init__(col, row, symbol)

class Black(Square):
    
    def __init__(self, col, row, symbol):
        super().__init__(col, row, symbol)

class Corner(Square):

    def __init__(self, col, row, symbol):
        super().__init__(col, row, symbol)

if __name__ == '__main__':

    board = Board()

    input_reader = InputReader()

    input_reader.read_input(board)

    print(str(board))
