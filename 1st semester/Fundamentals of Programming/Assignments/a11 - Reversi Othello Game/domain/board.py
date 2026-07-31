"""
Reversi board is an 8*8 matrix
At start it has the 4 most central squares occupied by 2 of each colour
Black = -1
White = 1
Empty = 0
"""
from exceptions import InvalidCellError


class Board:
    def __init__(self):
        """
        Initialize the board
        """
        self.size = 8
        self.board = [[0 for i in range(8)] for j in range(8)]

        self.board[4][4] = -1 #initial black piece 1
        self.board[4][3] = 1  #initial white piece 1
        self.board[3][3] = -1 #initial black piece 2
        self.board[3][4] = 1  #initial white piece 2


    def get_cell(self, row, col):
        """
        Gets a cell from the board
        :param row: the row number
        :param col: the column number
        :return: board[row][col]
        """
        return int(self.board[row][col])

    def set_cell(self, row, col, value):
        """
        Sets a value to a cell in the board
        :param row: the row number
        :param col: the column number
        :param value: the value to set
        :return: changes the value of the cell
        """
        self.board[row][col] = int(value)

    def is_inside_borders(self, row, col):
        """
        Checks if a cell is inside the borders
        :param row: the row number
        :param col: the column number
        :return: True if the cell is inside the borders else False
        """
        if not (0 <= row < self.size and 0 <= col < self.size):
            return False
        return  True

    def count_pieces(self):
        """
        Counts the number of pieces of each colour
        :return: the number of black pieces , white pieces
        """
        count_black = 0
        count_white = 0
        for row in range(self.size):
            for col in range(self.size):
                if self.get_cell(row, col) == -1:
                    count_black += 1
                elif self.get_cell(row, col) == 1:
                        count_white += 1
        return count_black, count_white