import constants
from board import Board
from math import pi
from math import cos
import copy

class Player:
    
    def __init__(self, colour):
        #Initialise the correct symbol to the player

        self.symbol = None
        self.opponent = None
        self.num_turns = 0

        if (colour == 'white'):
            self.symbol = constants.WHITE
            self.opponent = constants.BLACK

        elif (colour == 'black'):
            self.symbol = constants.BLACK
            self.opponent = constants.WHITE
            
        self.board = Board()


    #Return an action to the referee.py
    def action(self, turns):
        #If the board shrunk during opponents turn, shrink the board first
        #If the current turn is to shrink then, shrink at the end of the turn

        if turns == (constants.SHRINK_1+1) or turns == (constants.SHRINK_2+1):
            self.board.shrink()

        print("TURNS: " + str(self.num_turns))
        if turns <= constants.END_PLACING_PHASE:
            self.num_turns += 1

        if self.num_turns < constants.END_PLACING_PHASE/2:

            action = self.action_in_placing_phase()
            self.board.board[action].set_type(self.symbol)
            self.board.pieces[self.symbol].append(action)
            self.board.remove_killed()

        else:
            action = self.action_in_moving_phase()

            if action is not None:
                self.board.board[action[0]] = constants.EMPTY
                self.board.board[action[1]] = self.symbol
                self.board.remove_killed()

        #Shrink at the end of the turn if the current turn is the last

        if turns == constants.SHRINK_1 or turns == constants.SHRINK_2:
            self.board.shrink()

        return action
        
    
    #Update the internal representation of the board given the opponents action
    def update(self, action):
        self.board.update(action, self.opponent)

    def action_in_placing_phase(self):

        white_y_range = range(0, 6)
        black_y_range = range(2, 8)

        weights_of_positions = []

        player_pieces = self.board.pieces[self.symbol]

        #check for kill-able opponents

        for piece in player_pieces:

            for direction in constants.DIRECTIONS:

                position_in_direction = self.board.determine_position_in_direction(piece, direction)

                if position_in_direction in self.board.board:

                    if self.board.board[position_in_direction].get_type is self.opponent:

                        position_after_opponent = self.board.determine_position_in_direction(position_in_direction, direction)

                        if position_after_opponent in self.board.board:

                            if self.board.board[position_after_opponent].get_type() is constants.EMPTY:

                                print("above")

                                return position_after_opponent

        if self.num_turns < 5:

            if self.symbol == constants.WHITE:

                board_copy = self.board.board.copy()

                for x_position in range(0, constants.BOARD_SIZE - 1):

                    for y_position in white_y_range:

                        position = (x_position, y_position)

                        if self.board.board[position].get_type() is not constants.CORNER:

                            position_weight = self.calculate_position_weight(position)

                            weights_of_positions.append((position_weight, (x_position, y_position)))

            else:

                for x_position in range(0, constants.BOARD_SIZE - 1):

                    for y_position in black_y_range:

                        position = (x_position, y_position)

                        if self.board.board[position].get_type() is not constants.CORNER:

                            position_weight = self.calculate_position_weight(position)

                            weights_of_positions.append((position_weight, position))

            weights_of_positions.sort(key=lambda x: x[0], reverse=True)

            for position in weights_of_positions:

                if position[1] in self.board.pieces[self.opponent] or position[1] in self.board.pieces[self.symbol]:
                    continue

                for direction in constants.DIRECTIONS:

                    position_in_direction = self.board.determine_position_in_direction(position[1], direction)

                    if position_in_direction in self.board.board:

                        if self.board.board[position_in_direction].get_type is self.opponent:

                            break

                    return position[1]

        else:
            board_copy = copy.copy(self.board)

            possible_moves = []

            if self.symbol is constants.WHITE:

                for x_position in range(0, constants.BOARD_SIZE):

                    for y_position in range(0, constants.BOARD_SIZE - 2):

                        position = (x_position, y_position)

                        if board_copy.board[position].get_type() is constants.CORNER:

                            continue

                        if board_copy.board[position].get_type() is constants.EMPTY and not self.enemies_around(position):

                            board_copy.board[position].set_type(self.symbol)

                            board_copy_evaluation = self.evaluate_space(board_copy)

                            possible_moves.append((board_copy_evaluation, position))

                            board_copy.board[position].set_type(constants.EMPTY)

            else:

                for x_position in range(0, constants.BOARD_SIZE):

                    for y_position in range(2, constants.BOARD_SIZE):

                        position = (x_position, y_position)

                        if board_copy.board[position].get_type() is constants.CORNER:
                            continue

                        if board_copy.board[position].get_type() is constants.EMPTY and not self.enemies_around(position):
                            board_copy.board[position].set_type(self.symbol)

                            board_copy_evaluation = self.evaluate_space(board_copy)

                            possible_moves.append((board_copy_evaluation, position))

                            board_copy.board[position].set_type(constants.EMPTY)

            possible_moves.sort(key=lambda x: x[0], reverse=True)

            return possible_moves[0][1]



    def evaluate_space(self, board):

        player_space_controlled = []
        opponent_space_controlled = []

        for player_piece in board.pieces[self.symbol]:

            for direction in constants.DIRECTIONS:

                position_in_direction = board.determine_position_in_direction(player_piece, direction)

                if position_in_direction not in board.board:
                    continue

                if board.board[position_in_direction] is constants.EMPTY:
                    player_space_controlled.appened(position_in_direction)

        for opponent_piece in board.pieces[self.opponent]:

            for direction in constants.DIRECTIONS:

                position_in_direction = board.determine_position_in_direction(opponent_piece, direction)

                if position_in_direction not in board.board:
                    continue

                if board.board[position_in_direction] is constants.EMPTY:
                    opponent_space_controlled.appened(position_in_direction)

        player_space_controlled = set(player_space_controlled)
        opponent_space_controlled = set(opponent_space_controlled)

        contested = len(player_space_controlled.intersection(opponent_space_controlled))

        return len(player_space_controlled) - contested

    def enemies_around(self, position):

        for direction in constants.DIRECTIONS.keys():

            position_in_direction = self.board.determine_position_in_direction(position, direction)

            if position_in_direction not in self.board.board:
                continue

            if self.board.board[position_in_direction] is self.opponent:

                return True

        return False



    def calculate_position_weight(self, position):

        board_weights = constants.BOARD_WEIGHTS

        x_value = board_weights[position[0]]
        y_value = board_weights[position[1]]

        weight = 2 - cos(x_value) - cos(y_value)

        return weight


    def action_in_moving_phase(self):

        pieces = self.board.pieces
        board = self.board.board

        possible_actions = []

        for piece_position in pieces[self.symbol]:

            for direction in constants.DIRECTIONS:

                board_copy = copy.copy(self.board)
                board_of_copy = board_copy.board
                black_pieces = board_copy.pieces[constants.BLACK]
                white_pieces = board_copy.pieces[constants.WHITE]

                position_in_direction = self.board.determine_position_in_direction(piece_position, direction)

                if position_in_direction in board:

                    if board[position_in_direction].get_type() is constants.EMPTY:

                        #make move
                        board_of_copy[piece_position].set_type(constants.EMPTY)
                        board_of_copy[position_in_direction].set_type(self.symbol)

                        #detect kills
                        board_copy.remove_killed()

                        board_evaluation = self.space_evaluation_moving_phase(self.symbol, board_copy)

                        #create data tuple
                        evaluation_and_move = (board_evaluation, (piece_position, position_in_direction))

                        #add to possible moves
                        possible_actions.append(evaluation_and_move)

                    elif board[position_in_direction].get_type() is self.opponent:

                        position_after_opponent = board_copy.determine_position_in_direction(position_in_direction, direction)

                        if board[position_in_direction].get_type() is constants.EMPTY:

                            #make move
                            board_of_copy[piece_position].set_type(constants.EMPTY)
                            board_of_copy[position_after_opponent].set_type(self.symbol)

                            #detect kills
                            board_copy.remove_killed()

                            board_evaluation = self.space_evaluation_moving_phase(self.symbol, board_copy)

                            #create data tuple
                            evaluation_and_move = (board_evaluation, (piece_position, position_in_direction))

                            #add to possible moves
                            possible_actions.append(evaluation_and_move)

        possible_actions.sort(key=lambda x: x[0], reverse=True)   #sort with the highest evaluations first

        if not possible_actions:
            return None

        print([possible_actions[0]])
        return possible_actions[0][1]

    def space_evaluation_placing_phase(self, board):

        num_player_control = 0
        num_opponent_control = 0

        player_control_positions = []
        opponent_control_positions = []

        '''
        for pieces_on_board in board.pieces[self.symbol]:

            for direction in constants.DIRECTIONS.values():

                position_in_direction = self.board.determine_position_in_direction(pieces_on_board, direction)

                if position_in_direction in self.board.board:

                    if self.board.board[position_in_direction] is constants.EMPTY:

                        num_player_control += 1

                        player_control_positions.append(position_in_direction)

        for pieces_on_board in board.pieces[self.opponent]:

            for direction in constants.DIRECTIONS.values():

                position_in_direction = self.board.determine_position_in_direction(pieces_on_board, direction)

                if position_in_direction in self.board.board:

                    if self.board.board[position_in_direction] is constants.EMPTY:

                        num_opponent_control += 1

                        opponent_control_positions.append(position_in_direction)
        
        '''

        return num_player_control - num_opponent_control



    def space_evaluation_moving_phase(self, player_symbol, board):

        white_influence = []
        black_influence = []

        directions = constants.DIRECTIONS.values()

        white_pieces = board.pieces[constants.WHITE]
        black_pieces = board.pieces[constants.BLACK]

        for white_position in white_pieces:

            for direction in directions:

                position = board.determine_position_in_direction(white_position, direction)

                if position in board:

                    square_type_in_position = board[position].get_type()

                    if square_type_in_position is constants.EMPTY:

                        white_influence.append(position)

                '''
                    if square_type_in_position is constants.BLACK:

                        position_after_black = self.board.determine_position_in_direction(position, direction)

                        if position_after_black in self.board.board and\
                            square_type_in_position is not constants.CORNER:

                            white_influence.append(position)
                '''

        for black_position in black_pieces:

            for direction in directions:

                position = board.determine_position_in_direction(black_position, direction)

                if position in board:

                    square_type_in_position = board[position].get_type()

                    if square_type_in_position is constants.EMPTY:

                        black_influence.append(position)

        num_white_pieces = len(self.board.pieces[constants.WHITE])
        num_black_pieces = len(self.board.pieces[constants.BLACK])

        white_influence = set(white_influence)
        black_influence = set(black_influence)

        num_contested = len(white_influence.intersection(black_influence))

        num_white_control = len(white_influence) - num_contested
        num_black_control = len(black_influence) - num_contested


        if player_symbol == constants.WHITE:

            evaluation = ((num_white_control + num_white_pieces) - (num_black_control + num_black_pieces), num_contested)
            return evaluation

        else:

            evaluation = ((num_black_control + num_black_pieces) - (num_white_control + num_white_pieces), num_contested)
            return evaluation
















