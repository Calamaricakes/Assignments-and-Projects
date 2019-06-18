import constants 

class Board:

    def __init__(self):

        self.size = constants.BOARD_SIZE
        
        #Initialise the board to all empty first with the four corners
        self.board = {}
        self.pieces = {constants.BLACK: [], constants.WHITE: []}

        for i in range(self.size):
            for j in range(self.size):
                position = (i, j)
                self.board[position] = Square()

        #Determine where the column and rows start from to allow for shrinking
        self.column_start = 0
        self.row_start = 0
        
        #Now add the corner squares to the board  
        self.add_corners(self.column_start, self.row_start)

    #Update the current state of the board depending on what actions the 
    #opponent has made
    def update(self, action, symbol):

        #No move (Handle this first to prevent exception)
        if (action is None):
            return

        #Placed a piece
        elif (type(action[0]) is int):
            cur_pos = action
            self.board[(action[0], action[1])].set_type(symbol)
            self.pieces[symbol].append(action)
            
        #Moved a piece
        elif (type(action[0]) is tuple):
            initial_pos = action[0]
            cur_pos = action[1]

            #remove from board and pieces

            self.board[(initial_pos[0], initial_pos[1])].set_type(constants.EMPTY)
            self.pieces[symbol].remove(initial_pos)

            self.board[(cur_pos[0], cur_pos[1])].set_type(symbol)
            self.pieces[symbol].append(cur_pos)

        #Remove any pieces if they can be killed
        self.remove_killed()
            
    #Shrink the board 
    def shrink(self):
        #Remove the first and last columns
        for i in range(self.size-1):
            del self.board[(i, self.size-1)]
            del self.board[i, 0]
        
        #Remove the first and last row
        for i in range(self.size-1):
            try:
                del self.board[(0, i)]
                del self.board[(self.size-1, i)]
            except KeyError:
                pass
        
        #Update the column and row start positions and the current size of board
        self.size -= 2
        self.column_start += 1
        self.row_start += 1
        
        #Now add the new corners
        self.add_corners(self.column_start, self.row_start)

        # Helper method to add the corners to the board

    def add_corners(self, column_start, row_start):
        self.board[(column_start, row_start)].set_type(constants.CORNER)
        self.board[(column_start, row_start + (self.size - 1))].set_type(constants.CORNER)
        self.board[(column_start + (self.size - 1), row_start)].set_type(constants.CORNER)
        self.board[(column_start + (self.size - 1), row_start + (self.size - 1))].set_type(constants.CORNER)

    #Check if the newly updated board has any killable pieces
    #If there is a killable piece remove it from the board because it is 
    #likely that it has been removed in the real representation of the board
    def remove_killed(self):

        #Only need to check around the piece that is just recently put
        #Check if there is a opposite piece above it


        each_side = list(self.pieces.items())# a list of all pieces with their locations

        pieces_to_remove = []

        for pieces in each_side:
            for position in pieces[1]:
                pieces_to_remove.extend(self.detect_kill(pieces[0], position))  # piece[0] = key, piece[1] = position

        pieces_to_remove = set(pieces_to_remove)    #get rid of duplicates

        for dead_piece in pieces_to_remove:

            #remove from board representation
            self.board[dead_piece].set_type(constants.EMPTY)

            #remove from piece tracker
            if dead_piece in self.pieces[constants.WHITE]:
                self.pieces[constants.WHITE].remove(dead_piece)
            else:
                self.pieces[constants.BLACK].remove(dead_piece)


    '''    
    #Remove a piece based on the direction from the original piece if it has 
    #an ally on the opposite end
    #def kill_at_direction(self, direction, pos, symbol, enemy):
        next_pos = self.next_coords(direction, pos)

        if self.board[new_pos[0]][new_pos[1]] == enemy:

            next_pos2 = self.next_coords(direction, next_pos)

            if self.board[new_pos2[0]][new_pos2[1]] == symbol:
                # add to list to kill
                self.board[new_pos[0]][new_pos[1]] = None         
    '''

    def detect_kill(self, player_symbol, position):

        killed_opponents = []

        if player_symbol == constants.WHITE:
            opponent_symbol = constants.BLACK

        else:
            opponent_symbol = constants.WHITE

        opponent_pieces = self.pieces[opponent_symbol]

        for direction in constants.DIRECTIONS:

            position_in_direction = self.determine_position_in_direction(position, direction)

            if position_in_direction not in self.board or \
               self.board[position_in_direction].get_type is constants.CORNER:
                continue

            if position_in_direction in opponent_pieces:  # if an opponent is in an adjacent grid

                position_after_opponent = self.determine_position_in_direction(position_in_direction, direction)

                if position_after_opponent in self.board:

                    square_type = self.board[position_after_opponent].get_type()

                    if square_type is player_symbol or square_type is constants.CORNER:
                        killed_opponents.append(position_in_direction)

        return killed_opponents

    def determine_position_in_direction(self, position, direction):

        new_position = (position[0] + constants.DIRECTIONS[direction][0], position[1] + constants.DIRECTIONS[direction][1])

        return new_position



    #Print the board
    def __str__(self):
        print(self.board)


class Square:

    def __init__(self):
        self.type = constants.EMPTY

    def set_type(self, type):
        self.type = type

    def get_type(self):
        return self.type
