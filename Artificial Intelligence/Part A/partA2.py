import copy

DIRECTIONS = {'DOWN': (0, 1), 'UP': (0, -1), 'RIGHT': (1, 0), 'LEFT': (-1, 0)}
WHITE_SYMBOL = "O"
BLACK_SYMBOL = "@"
CORNER_SYMBOL = "X"
EMPTY_SYMBOL = "-"
WHITE_INDICATOR = True
BLACK_INDICATOR = False

class InputReader:
    
    def make_square(self, char, col, row):

        if char is EMPTY_SYMBOL:
            return Empty(col, row, char)

        elif char is CORNER_SYMBOL:
            return Corner(col, row, char)

        elif char is WHITE_SYMBOL:
            return White(col, row, char)

        elif char is BLACK_SYMBOL:
            return Black(col, row, char)

        return None

    def read_line(self, board, cur_row, cur_col):
        line = input()
        split_line = line.split()
        board.size = len(split_line)

        #Make the squares
        for char in split_line:
            board.board[(cur_col, cur_row)] = self.make_square(char, cur_col, cur_row)
            if char is BLACK_SYMBOL:
                board.black_pieces[(cur_col, cur_row)] = board.board[(cur_col, cur_row)]

            elif char is WHITE_SYMBOL:
                board.white_pieces[(cur_col, cur_row)] = board.board[(cur_col, cur_row)]

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
        self.black_pieces = {}
        self.white_pieces = {}

    def __str__(self):
        
        str = ""
        for row in range(self.size):
            for col in range(self.size):
                str += self.board[col, row].symbol
                str += " "

            str += "\n"

        return str

    def print_black_pieces(self):
        print(str(self.black_pieces.keys()))

    def find_next_pos(self, pos, direction):
        cur_col = pos[0]
        cur_row = pos[1]

        movement_col = direction[0]
        movement_row = direction[1]

        new_col = cur_col + movement_col
        new_row = cur_row + movement_row

        return new_col, new_row

    def check_dir_with_jumps(self, pos, direction):
        """
        Check the next position whether it is a legal move or not 
        """

        #Calculate the new position 
        new_pos = self.find_next_pos(pos, DIRECTIONS[direction])
        
        #New position is an empty square
        if new_pos in self.board:
            if isinstance(self.board[new_pos], Empty):
                return True

            #If the new position is a piece then check the next square
            elif isinstance(self.board[new_pos], Piece):
                new_pos2 = self.find_next_pos(new_pos, DIRECTIONS[direction])

                #If next square is empty, there is a legal move
                if new_pos2 in self.board and isinstance(self.board[new_pos2], Empty):
                    return True

        return False

    def piece_capture_position_for_white(self, pos):

        list_of_capture_positions = []

        list_of_capture_positions += self.horizontal_capture_positions_for_white(pos)
        list_of_capture_positions += self.vertical_capture_positions_for_white(pos)

        return list_of_capture_positions

    def horizontal_capture_positions_for_white(self, pos):

        left = self.find_next_pos(pos, DIRECTIONS["LEFT"])
        right = self.find_next_pos(pos, DIRECTIONS["RIGHT"])

        if left in self.board.keys() and right in self.board.keys():

            # "Corner" cases first
            if isinstance(self.board[left], Corner) and (isinstance(self.board[right], White) or isinstance(self.board[right], Empty)):

                return [right]

            elif isinstance(self.board[right], Corner) and (isinstance(self.board[left], White) or isinstance(self.board[left], Empty)):
                return [left]

            # If there was a black piece on either side
            if isinstance(self.board[left], Black) or isinstance(self.board[right], Black):
                return []

            # return both left and right since the two positions are still targets

            return [left, right]

        return []

    def vertical_capture_positions_for_white(self, pos):

        up = self.find_next_pos(pos, DIRECTIONS["UP"])
        down = self.find_next_pos(pos, DIRECTIONS["DOWN"])

        if up in self.board.keys() and down in self.board.keys():

            # "Corner" cases first
            if isinstance(self.board[up], Corner) and (isinstance(self.board[down], White) or isinstance(self.board[down], Empty)):

                return [down]

            elif isinstance(self.board[down], Corner) and (isinstance(self.board[up], White) or isinstance(self.board[up], Empty)):
                return [up]

            # If there was a black piece on either side
            if isinstance(self.board[up], Black) or isinstance(self.board[down], Black):
                return []

            # return both up and down since the two positions are still targets

            return [up, down]

        return []

    def calc_legal_moves(self):

        white_legal_moves = 0
        black_legal_moves = 0

        for pos in self.board.keys():
            #Check white
            if isinstance(self.board[pos], White):

                for direction in DIRECTIONS.keys():
                    if self.check_dir_with_jumps(pos, direction):
                        white_legal_moves += 1
            
            elif isinstance(self.board[pos], Black):
                for direction in DIRECTIONS.keys():
                    if self.check_dir_with_jumps(pos, direction):
                        black_legal_moves += 1

        #Now print the legal moves
        print(white_legal_moves)
        print(black_legal_moves)

    def update_board(self, piece_initial_position, piece_final_position):
        # make_square not in board, swapping the the empty and the white

        temp = self.board.pop(piece_final_position)
        self.board[piece_final_position] = self.board.pop(piece_initial_position)
        self.board[piece_initial_position] = temp

    def determine_moves_to_eliminate_black(self):
        target_squares = self.target_squares_for_white()

        for white_piece_pos in self.white_pieces:
            if white_piece_pos in target_squares:
                target_squares.remove(white_piece_pos)

        for white_piece in self.white_pieces:
            queue = []
            start = {"current_pos": white_piece, "visited": [white_piece]}
            queue.append(start)

            while queue and target_squares:

                current_state = queue.pop(0)
                current_position = current_state["current_pos"]
                current_visited = current_state["visited"]

                if current_position in target_squares:
                    current_visited.append(current_position)
                    output = ""

                    for step in range(len(current_visited) - 2):
                        next_pos = current_visited[step+1]
                        output += str(current_visited[step]) + " " + "->" + " " + str(current_visited[step+1]) + "\n"

                    self.update_board(current_visited[0], current_visited[-1])   # "moves" the piece from initial to final Note: mutates board
                    target_squares.remove(current_position) #safe to do since there would be only one instance of position
                    print(output)

                    break

                for dir in DIRECTIONS.values():
                    next_pos = self.find_next_pos(current_position, dir)

                    if next_pos not in self.board or next_pos in current_visited:
                        continue

                    new_visited = copy.copy(current_visited)
                    new_visited.append(next_pos)
                    state_add = {"current_pos": next_pos, "visited": new_visited}
                    queue.append(state_add)

    def white_targets(self):
        print(self.determine_target_squares_for_white())

    def target_squares_for_white(self):
        list_of_targets = []

        for black_piece in self.black_pieces:
            list_of_targets += self.piece_capture_position_for_white(black_piece)

        return list(set(list_of_targets))


class Square:

    def __init__(self, col, row, symbol):
        self.position = (col, row)
        self.symbol = symbol

class Empty(Square):
    
    def __init__(self, col, row, symbol):
        self.position = (col, row)
        self.symbol = symbol

class Piece:

    def __init__(self, col, row, symbol):
        self.position = (col, row)
        self.symbol = symbol

class White(Piece):

    def __init__(self, col, row, symbol):
        super().__init__(col, row, symbol)

    def indicator(self):
        return WHITE_INDICATOR

class Black(Piece):

    def __init__(self, col, row, symbol):
        super().__init__(col, row, symbol)

    def indicator(self):
        return BLACK_INDICATOR

class Corner(Square):

    def __init__(self, col, row, symbol):
        super().__init__(col, row, symbol)

if __name__ == '__main__':

    board = Board()

    input_reader = InputReader()

    input_reader.read_input(board)

    print(str(board))

    board.print_black_pieces()

    board.target_squares_for_white()

    board.calc_legal_moves()

    board.determine_moves_to_eliminate_black()