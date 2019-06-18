from Maze import *


def create_board(board_file):
    file = open(board_file, "rt")

    # read the first line of the file to get the dimensions (vertical, horizontal

    dimensions = get_dimensions(file)

    maze = Maze(dimensions["vertical"], dimensions["horizontal"])

    maze_structure_txt = file.readlines()

    maze_structure_txt = [line.strip() for line in maze_structure_txt]

    maze.create_squares(maze_structure_txt)

    return maze


def get_dimensions(file):
    # get the dimensions that are in file on the first line
    # returns a dictionary containing it

    # dimensions are characters in a comma separated format i.e. vertical, horizontal e.g. "3,3"
    dimensions = file.readline().split(',')

    # assign the vertical and horizontal values
    vertical_dimension = int(dimensions[0])
    horizontal_dimension = int(dimensions[1])

    # create a dictionary to hold the two dimensions
    dimensions = {"vertical": vertical_dimension, "horizontal": horizontal_dimension}

    return dimensions



