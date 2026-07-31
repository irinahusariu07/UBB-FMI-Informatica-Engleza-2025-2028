import string
import random

from texttable import Texttable


class GameService:
    def __init__(self, board):
        self.board = board

    def print_board(self):
        table = Texttable()
        table.set_cols_align(['c'] * (self.board.cols + 1))
        header = [" "] + [str(i+1) for i in range(self.board.cols)]
        row_labels = list(string.ascii_uppercase)
        table.add_row(header)
        for i in range (self.board.rows):
            row = [row_labels[i]]

            for j in range(self.board.cols):
                if self.board.matrix[i][j] == 0:
                    row.append(" ")
                elif self.board.matrix[i][j] == 1:
                    row.append("*")
                elif self.board.matrix[i][j] == 2:
                    row.append("E")
                elif self.board.matrix[i][j] == 3:
                    row.append("B")

            table.add_row(row)
        return table.draw()

    def place_stars(self):
        no_stars = 0
        while no_stars < 10:
            x = random.randint(0, self.board.rows - 1)
            y = random.randint(0, self.board.cols - 1)
            if self.board.matrix[x][y] == 0:
                ok = True
                for dx in [-1, 0, 1]:
                    for dy in [-1, 0, 1]:
                        if dx == 0 and dy == 0:
                            continue
                        if 0 <= dx + x < self.board.rows and 0 <= dy + y < self.board.cols:
                            if self.board.matrix[x + dx][y + dy] == 1:
                                ok = False

                if ok == True:
                    no_stars += 1
                    self.board.matrix[x][y] = 1

    def place_E(self):
        no_E = 0
        while no_E < 1:
            x = random.randint(0, self.board.rows - 1)
            y = random.randint(0, self.board.cols - 1)
            if self.board.matrix[x][y] == 0:
                no_E += 1
                self.board.matrix[x][y] = 2

    def get_E(self):
        for x in range(self.board.rows):
            for y in range(self.board.cols):
                if self.board.matrix[x][y] == 2:
                    return(x, y)
        return None

    def place_B(self):
        no_B = 0
        while no_B < 3:
            x = random.randint(0, self.board.rows - 1)
            y = random.randint(0, self.board.cols - 1)
            if self.board.matrix[x][y] == 0:
                no_B += 1
                self.board.matrix[x][y] = 3

    def move(self, to_row, to_col):
        init_row, init_col = self.get_E()
        if init_row == to_row and init_col == to_col:
            raise ValueError("End position is the same as current position")
        if not (0 <= to_row < self.board.rows and 0 <= to_col < self.board.cols):
            raise ValueError("Invalid row or column")
        if self.board.matrix[to_row][to_col] == 1:
            raise ValueError("End position is a star")
        if self.board.matrix[to_row][to_col] == 3:
            raise ValueError("Landed on an enemy ship! YOU LOST")

        same_check = False

        for dx in [-1, 0, 1]:
            for dy in [-1, 0, 1]:
                if dx == 0 and dy == 0:
                    continue

                nx = init_row
                ny = init_col
                star_path = False

                while True:
                    nx += dx
                    ny += dy

                    if not (0 <= nx < self.board.rows and 0 <= ny < self.board.cols):
                        break

                    if self.board.matrix[nx][ny] == 1:
                        star_path = True

                    if nx == to_row and ny == to_col and not star_path:
                        same_check = True
                        break

                if same_check:
                    break

        if not same_check:
            raise ValueError("Not a valid move")

        self.board.matrix[init_row][init_col] = 0
        self.board.matrix[to_row][to_col] = 2














