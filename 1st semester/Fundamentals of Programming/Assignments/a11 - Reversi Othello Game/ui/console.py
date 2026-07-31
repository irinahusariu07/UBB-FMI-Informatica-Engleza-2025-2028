"""
UI part
"""
from exceptions import InvalidCellError
import random

class Console:
    def __init__(self, game_service):
        self.game_service = game_service
        self.symbols = {0: ".", -1: "B", 1: "W"}

    def print_board(self):
        size = self.game_service.board.size

        # column header
        print("  ", end="")
        for col in range(size):
            print(col, end=" ")
        print()

        # rows
        for row in range(size):
            print(row, end=" ")
            for col in range(size):
                value = self.game_service.board.get_cell(row, col)
                print(self.symbols[value], end=" ")
            print()

    def print_possible_moves(self, player):
        moves = self.game_service.possible_moves(player)
        if not moves:
            print("No moves possible")
        else:
            print("Possible moves:")
            print("Row | Column")
            for (x, y) in moves:
                print(x , y)

    def print_game_over(self):
        print("\nGame over!")

        black, white = self.game_service.board.count_pieces()
        empty = self.game_service.board.size ** 2 - (black + white)

        if black > white:
            black += empty
            print("Black wins!")
        elif white > black:
            white += empty
            print("White wins!")
        else:
            print("Draw!")

        print(f"Black pieces: {black}")
        print(f"White pieces: {white}")

    def read_human_input(self):
        user_input = input("Enter your move (row, column): ")
        # remove parentheses
        user_input = user_input.replace("(", "").replace(")", "")
        # replace commas with spaces
        user_input = user_input.replace(",", " ")

        parts = user_input.split()
        if len(parts) != 2:
            raise ValueError("Invalid input format")
        row = int(parts[0])
        col = int(parts[1])

        return row, col

    def human_turn(self, player):
        print("\nYour turn")
        if not self.game_service.has_moves(player):
            print("No possible moves. Pass")
            return
        self.print_board()
        self.print_possible_moves(player)
        while True:
            try:
                row, column = self.read_human_input()
                if not self.game_service.board.is_inside_borders(row, column):
                    raise InvalidCellError("Move outside of board")
                if not self.game_service.validate_move(player, row, column):
                    raise InvalidCellError("Not a valid move")

                self.game_service.apply_move(player, row, column)
                break  # exit loop

            except ValueError:
                print("Invalid format. Please enter 2 natural numbers")
            except InvalidCellError as e:
                print(e)
        self.print_board()

    def computer_turn(self, player):
        print("\nComputers turn")
        if not self.game_service.has_moves(player):
            print("Computer has no possible moves. Pass")
            return
        row, col = self.game_service.computer_strategy(player)
        print(f"Computers choice: ({row}, {col})")
        self.game_service.apply_move(player, row, col)

    def run(self):
        print("Let's play Reversi (Othello)!")
        print("Your color: Black")
        print("Computer's color: White")
        while not self.game_service.game_over():
            current_player = self.game_service.current_player
            if current_player.type == "human":
                self.human_turn(current_player)
            else :
                self.computer_turn(current_player)
            self.game_service.switch_player()

        self.print_game_over()
        self.print_board()