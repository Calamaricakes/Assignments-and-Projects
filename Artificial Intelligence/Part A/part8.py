DIRECTIONS = {'DOWN': (0, 1), 'UP': (0, -1), 'RIGHT': (1, 0), 'LEFT': (-1, 0)}
WHITE_SYMBOL = "O"
BLACK_SYMBOL = "@"
CORNER_SYMBOL = "X"
EMPTY_SYMBOL = "-"
COL = 0
ROW = 1

class InputReader:
    """ 
    The input reader class which takes in input from stdin and creates 
    objects and pieces to be stored in the Board class
    """

    def __init__(self):
        self.analysis_method = ""
    
    def make_piece(self, char, col, row):
        """
        Returns an object given the symbol parsed from stdin, the column and
        the row
        """

        if char is WHITE_SYMBOL:
            return White(col, row, char)

        elif char is BLACK_SYMBOL:
            return Black(col, row, char)

        return None

    def read_line(self, board, row, col):
        """ 
        Reads a line from stdin 
        """

        line = input()
        split_line = line.split()
        board.size = len(split_line)

        #Make the squares
        for char in split_line:
            board.board[(col, row)] = char

            #If the char is a piece then store in the piece dictionary in the
            #board
            if char == WHITE_SYMBOL:
                board.whites[(col, row)] = self.make_piece(char, col, row)

            elif char == BLACK_SYMBOL:
                board.blacks[(col, row)] = self.make_piece(char, col, row)

            col += 1

    def read_input(self, board):
        """ 
        Reads the whole input parsed through stdin
        """

        cur_col = 0
        cur_row = 0

        #read a line first to get the size of the board
        self.read_line(board, cur_row, cur_col)
        cur_row += 1

        #Read the remaining lines from stdin
        while cur_row < board.size:

            self.read_line(board, cur_row, cur_col)
            cur_row += 1

        #Read the last line which tells us the analysis method
        self.analysis_method = input()


class Board:
    """
    Represents the board where the pieces are supposed to be placed on 
    """
    size = 0

    def __init__(self):
        self.board = {}
        self.blacks = {}
        self.whites = {}

    def __str__(self):
        
        string = ""
        for row in range(self.size):
            for col in range(self.size):
                string += self.board[col, row]
                string += " "

            string += "\n"

        return string

    @staticmethod
    def find_next_pos(pos, direction):
        """
        Find the next position of the piece if it has moved in the 
        corresponding direction
        """
        cur_col = pos[COL]
        cur_row = pos[ROW]

        chg_in_direction = DIRECTIONS[direction]
        movement_col = chg_in_direction[COL]
        movement_row = chg_in_direction[ROW]

        new_col = cur_col + movement_col
        new_row = cur_row + movement_row

        return new_col, new_row

    def check_dir_with_jumps(self, pos, direction):
        """
        Check the next position whether it is a legal move or not 
        """

        #Calculate the new position 
        new_pos = self.find_next_pos(pos, direction)

        #New position is an empty square
        if new_pos in self.board:
            if self.board[new_pos] == EMPTY_SYMBOL:
                return True

            #If the new position is a piece then check the next square
            elif self.board[new_pos] == BLACK_SYMBOL or\
                    self.board[new_pos] == WHITE_SYMBOL:
                new_pos2 = self.find_next_pos(new_pos, direction)

                #If next square is empty, there is a legal move
                if new_pos2 in self.board and\
                        self.board[new_pos2] == EMPTY_SYMBOL:
                    return True

        return False

    def calc_legal_moves(self):
        """
        Calculate the total number of moves for all available pieces for a 
        given colour
        """

        white_legal_moves = 0
        black_legal_moves = 0

        #Calculate legal moves for white
        for pos in board.whites.keys():

            for direction in DIRECTIONS.keys():
                if self.check_dir_with_jumps(pos, direction):
                    white_legal_moves += 1


        #Caculate legal moves for black
        for pos in board.blacks.keys():

            for direction in DIRECTIONS.keys():
                if self.check_dir_with_jumps(pos, direction):
                    black_legal_moves += 1

        #Now print the legal moves
        print(white_legal_moves)
        print(black_legal_moves)

class Strategy:
    """
    Represents the strategy taken to implement massacre to calculate the 
    optimal path required to take all the pieces on the board given 
    the starting colour
    """
   
    def __init__(self):
        self.targets = {}

    def can_be_killed(self, board, coords, formation, enemy_piece_symbol):
        """
        Determine if a piece can be killed 
        """

        #check if the enemy can be killed through a vertical formation
        if formation == "VERTICAL":
            pos1 = board.find_next_pos(coords, "UP")
            pos2 = board.find_next_pos(coords, "DOWN")

            if pos1 not in board.board or pos2 not in board.board:
                return False
            
            if board.board[pos1] == enemy_piece_symbol:
                return False
            
            if board.board[pos2] == enemy_piece_symbol:
                return False
       
        #horizontal formation
        elif formation == "HORIZONTAL":
            pos1 = board.find_next_pos(coords, "LEFT")
            pos2 = board.find_next_pos(coords, "RIGHT")

            if pos1 not in board.board or pos2 not in board.board:
                return False

            if board.board[pos1] == enemy_piece_symbol:
                return False
            
            if board.board[pos2] == enemy_piece_symbol:
                return False

        return True

    def find_targets(self, board, piece_symbol):
        """
        Find targets for the different pieces 
        """

        if piece_symbol == WHITE_SYMBOL:
            self.find_targets_for_white(board)

    def find_targets_for_white(self, board):
        """
        Find empty spaces which serve as targets for the white pieces
        """
        
        self.targets = {}

        for coords in board.blacks.keys():
            
            targets = []

            #Check whether can be killed vertically
            if self.can_be_killed(board, coords, "VERTICAL", BLACK_SYMBOL):

                up_pos = board.find_next_pos(coords, "UP")
                down_pos = board.find_next_pos(coords, "DOWN")

                #Only record if the space is empty
                positions = []
                if board.board[up_pos] == EMPTY_SYMBOL:
                    positions.append(up_pos)

                if board.board[down_pos] == EMPTY_SYMBOL:
                    positions.append(down_pos)
            
                targets.append(positions)

            #Check whether can be killed horizontally
            if self.can_be_killed(board, coords, "HORIZONTAL", BLACK_SYMBOL):
                left_pos = board.find_next_pos(coords, "LEFT")
                right_pos = board.find_next_pos(coords, "RIGHT")


                #Only record if the space is empty
                positions = []
                if board.board[left_pos] == EMPTY_SYMBOL:
                    positions.append(left_pos)

                if board.board[right_pos] == EMPTY_SYMBOL:
                    positions.append(right_pos)

                targets.append(positions)

            self.targets[coords] = targets


    def find_first_target_to_go(self):
        """
        Find the first optimal target to go to based on the targets 
        """
        
        #Find the targets where the number of targets surrounding the black
        #piece is one first since it allows the other pieces not to move
        
        target = None

        for piece in self.targets.keys():

            #Get the targets with only one target for a piece first since
            #there is a piece or corner on the other side

            if len(self.targets[piece]) == 1:
                target = self.targets[piece]
                break

        if target is None:
            piece = list(self.targets.keys())[0]
            target = self.targets[piece]
        
        #Remove the target from the dictionary
        del self.targets[piece]

        return target


    def filter_targets(self):
        """ 
        Choose optimal targets for the pieces 
        """
        
        #Loop through all the pieces target
        for coords in self.targets.keys():

            #Only filter for those where there are two different formations 
            #which can be used
            if len(self.targets[coords]) == 2:

                #Determine the number of pieces needed to complete the 
                #different formations
                n_first_formation = len(self.targets[coords][0])
                n_second_formation = len(self.targets[coords][1])

                #Remove the list with more targets to be filled by the pieces
                if n_second_formation < n_first_formation:
                    self.targets[coords] = self.targets[coords][1]

                else:
                    self.targets[coords] = self.targets[coords][0]

            #Just make the targets dictionary cleaner and remove nested 
            #lists
            else:
                self.targets[coords] = self.targets[coords][0]

        
        #Sort targets based on their priority of which to take first


    def is_blocked(self, board, pos, symbol):
        """ 
        Check if a piece with the given symbol can be taken with that position
        """

        if board.board[pos] != EMPTY_SYMBOL and board.board[pos] != symbol:
            return True 

        return False 

    def make_path(self, parents, start, end):
        """ 
        Constructs a path based on the parents obtained during the breadth
        first search
        """

        path = [end]

        #Continue to make the path until the start is reached
        while path[-1] != start:
            path.append(parents[path[-1]])

        return path

    def bfs(self, board, start, piece_symbol):
        """ 
        Do breadth first search from all the targets to determine the closest
        pieces to be able to occupy the target
        """

        parents = {}
        visited = []
        queue = []
        queue.append(start)

        #keep going until queue is empty or once found a solution
        while queue:

            pos = queue.pop(0)
            visited.append(pos)

            #Found the piece which is nearby so return the path taken
            if piece_symbol is WHITE_SYMBOL and pos in board.whites.keys():
                return self.make_path(parents, start, pos)

            elif piece_symbol is BLACK_SYMBOL and pos in board.blacks.keys():
                return self.make_path(parents, start, pos)
    
            #Loop through all the directions and find a new path 
            for direction in DIRECTIONS.keys():

                new_pos_move = Board.find_next_pos(pos, direction)

                #Check if the new pos is valid
                if new_pos_move not in board.board:
                    continue
                
                #Check if the piece is killed if it goes to that position
                if Piece.can_be_killed(board, new_pos_move, piece_symbol):
                    continue

                #Add the new position to the queue if it is not in the queue
                #and it hasnt been visited and if it is an empty spcae
                if new_pos_move not in queue and new_pos_move not in visited\
                        and not self.is_blocked(board, new_pos_move, 
                                piece_symbol):
                        
                        parents[new_pos_move] = pos
                        queue.append(new_pos_move)

            #visited.append(pos)


    def print_movements(self, pos, new_pos):
        """ 
        Print the movements taken by the pieces 
        """
        
        print("{} -> {}".format(pos, new_pos))

    def move_according_to_path(self, board, path, symbol):
        """ 
        Move the corresponding pieces according to the path calculated
        """
        
        pos = path.pop(0)

        if symbol == WHITE_SYMBOL:
    
            #Loop through all the next positions and update the board
            for next_pos in path:

                white_piece = board.whites[pos]

                white_piece.move(board, next_pos)


                #Print the movement to screen
                self.print_movements(pos, next_pos)
                
                pos = next_pos

                #Find surrounding targets whehter can be killed on the way to
                #the target
                for direction in DIRECTIONS:

                    new_pos = board.find_next_pos(pos, direction)

                    if new_pos in board.board:

                        #Check if the new_pos is a piece
                        if board.board[new_pos] == BLACK_SYMBOL:
                            
                            white_piece.kill(board, new_pos)

        elif symbol == BLACK_SYMBOL:
            
            for next_pos in path:
                
                black_piece = board.blacks[pos]

                black_piece.move(board, next_pos)

                #Update the black piece in the blacks dictionary in the board
                #class
                del board.blacks[pos]
                board.blacks[next_pos] = black_piece

                pos = next_pos

                #Find surrounding targets whehter can be killed on the way to
                #the target
                for direction in DIRECTIONS:

                    new_pos = board.find_next_pos(pos, direction)

                    #Check if the new_pos is a piece
                    if board.board[new_pos] == BLACK_SYMBOL:
                        
                        black_piece.kill(board, new_pos)


    def find_paths_for_all_targets(self, board, symbol):
        """
        Find paths for all the targets on the board
        """
    
        while board.blacks.values():

            self.find_targets(board, symbol)
            self.filter_targets()

            while self.targets.values():

                set_target = self.find_first_target_to_go()
                for target in set_target:

                    path = self.bfs(board, target, symbol)

                    self.move_according_to_path(board, path, symbol)

    def print_targets(self):
        """ 
        Helper method to print all targets found on the board 
        """

        print(self.targets)


class Square:
    """
    Parent of an empty or corner square which is present on the board 
    """

    def __init__(self, col, row, symbol):
        self.position = (col, row)
        self.symbol = symbol

class Empty(Square):
    """
    Represents an empty square on the board which has no properties and can 
    be occupied by a black or white piece 
    """
    
    def __init__(self, col, row, symbol):
        self.position = (col, row)
        self.symbol = symbol

class Piece:
    """ 
    Represents the super class of all pieces on the board
    Childs are either black or white pieces 
    """

    def __init__(self, col, row, symbol):
        self.position = (col, row)
        self.symbol = symbol


    @staticmethod
    def can_be_killed(board, pos, piece_symbol):
        """
        Check if the piece can be killed if it is at that position on the 
        board 
        """

        #Get the enemy symbol
        if piece_symbol == WHITE_SYMBOL:
            enemy_symbol = BLACK_SYMBOL

        elif piece_symbol == BLACK_SYMBOL:
            enemy_symbol = WHITE_SYMBOL

        pos_up = Board.find_next_pos(pos, "UP")
        pos_down = Board.find_next_pos(pos, "DOWN")
        pos_left = Board.find_next_pos(pos, "LEFT")
        pos_right = Board.find_next_pos(pos, "RIGHT")

        #Check if piece can be killed
        if pos_up in board.board and pos_down in board.board:
            
            if board.board[pos_up] == enemy_symbol and\
                    board.board[pos_down] == enemy_symbol:
                    
                    #But cannot be killed if it kills a black piece first
                    if self.check_opposite_side(board, pos_up):
                        return False

                    if self.check_opposite_side(board, pos_down):
                        return False

                    return True

        if pos_left in board.board and pos_right in board.board:

            if board.board[pos_left] == enemy_symbol and\
                    board.board[pos_right] == enemy_symbol:

                    if self.check_opposite_side(board, pos_up):
                        return False

                    if self.check_opposite_side(board, pos_down):
                        return False

                    return True

        return False


    def move(self, board, new_pos):
        """ 
        Move the piece on the board to the new position
        """

        #Move the piece only when the space is free
        if board.board[new_pos] == EMPTY_SYMBOL:

            board.board[new_pos] = self.symbol
            board.board[self.position] = EMPTY_SYMBOL

    def check_opposite_side(self, board, target):

        col_chg = target[COL] - self.position[COL]
        row_chg = target[ROW] - self.position[ROW]

        opposite_col = target[COL] + col_chg
        opposite_row = target[ROW] + row_chg

        if (opposite_col, opposite_row) not in board.board:
            return False

        if board.board[opposite_col, opposite_row] == self.symbol or\
                board.board[opposite_col, opposite_row] == CORNER_SYMBOL:

            return True

        return False

    @staticmethod
    def can_be_killed(board, pos, piece_symbol):

        if piece_symbol is WHITE_SYMBOL:
            enemy_symbol = BLACK_SYMBOL

        else:
            enemy_symbol = WHITE_SYMBOL

        #check for friendly pieces first
        for dir in DIRECTIONS.values():

            # check the pieces that are a skip away
            pos_opposite = (pos[0] + 2 * dir[0], pos[1] + 2 * dir[1])

            if pos_opposite not in board.board:
                continue

            square_symbol = board.board[pos_opposite]

            if square_symbol is piece_symbol or square_symbol is CORNER_SYMBOL:
                return False

        #check for enemy pieces
        pos_up = (pos[0] + DIRECTIONS["UP"][0], pos[1] + DIRECTIONS["UP"][1])
        pos_down = (pos[0] + DIRECTIONS["DOWN"][0], pos[1] + DIRECTIONS["DOWN"][1])

        if pos_up in board.board and pos_down in board.board:

            up_piece_symbol = board.board[pos_up]
            down_piece_symbol = board.board[pos_down]

            if (up_piece_symbol is enemy_symbol or up_piece_symbol is CORNER_SYMBOL) and\
                (down_piece_symbol is enemy_symbol or down_piece_symbol is CORNER_SYMBOL):
                return True

        pos_left = (pos[0] + DIRECTIONS["LEFT"][0], pos[1] + DIRECTIONS["LEFT"][1])
        pos_right = (pos[0] + DIRECTIONS["RIGHT"][0], pos[1] + DIRECTIONS["RIGHT"][1])

        if pos_left in board.board and pos_right in board.board:

            left_piece_symbol = board.board[pos_left]
            right_piece_symbol = board.board[pos_right]

            if (left_piece_symbol is enemy_symbol or left_piece_symbol is CORNER_SYMBOL) and \
                    (right_piece_symbol is enemy_symbol or right_piece_symbol is CORNER_SYMBOL):
                return True

        return False

    def kill(self, board, piece):

        if self.check_opposite_side(board, piece):

            if self.symbol == WHITE_SYMBOL:
                del board.blacks[piece]
                board.board[piece] = EMPTY_SYMBOL

            elif self.symbol == BLACK_SYMBOL:

                del board.whites[piece]
                board.board[piece] = EMPTY_SYMBOL



class White(Piece):
    """
    Represents a white piece on the board
    Properties:
    """

    def __init__(self, col, row, symbol):
        super().__init__(col, row, symbol)

    def move(self, board, new_pos):
        """ 
        Move the piece to the new position
        """
        super().move(board, new_pos)
        
        #Update the white piece in the whites dictionary in the board
        #class
        del board.whites[self.position]
        board.whites[new_pos] = self

        self.position = new_pos

    def kill(self, board, target):
        """ 
        Kill target
        """
        super().kill(board, target)


class Black(Piece):
    """
    Represents a black piece on the board 
    Properties:
    """

    def __init__(self, col, row, symbol):
        super().__init__(col, row, symbol)

    def move(self, board, new_pos):
        """ 
        Move the piece to the new position
        """
        super().move(board, new_pos)

        #Update the white piece in the whites dictionary in the board
        #class
        del board.whites[self.position]
        board.whites[new_pos] = self

        self.position = new_pos

    def kill(self, board, target):
        """ 
        Kill target
        """
        super().kill(board, target)

class Corner(Square):
    """ 
    Represents a corner square on the board 
    Properties:
    """

    def __init__(self, col, row, symbol):
        super().__init__(col, row, symbol)

if __name__ == '__main__':

    board = Board()
    input_reader = InputReader()

    #Read the input
    input_reader.read_input(board)

    print(str(board))

    #Calculate Moves or Massacre
    if input_reader.analysis_method == "Moves":
        board.calc_legal_moves()

    elif input_reader.analysis_method == "Massacre":

        strategy = Strategy()
        strategy.find_paths_for_all_targets(board, WHITE_SYMBOL)
