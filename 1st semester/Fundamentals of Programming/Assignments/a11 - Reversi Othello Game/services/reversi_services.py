"""
The functional part of the game
It should validate a move (meaning that i placed my piece next to at least one opponent piece and i "sandwich"
the opponent pieces between 2 of mine
It should flip the pieces
It should suggest possible positions for the move - both for human player (shown in UI) and for the computer
"""
import random

from exceptions import InvalidCellError


class GameService:
    def __init__(self, board, player1, player2):
        """
        Initialize the game service
        :param board: the board
        :param player1: first player (human)
        :param player2: second player (computer)
        """
        self.board = board
        self.player1 = player1
        self.player2 = player2
        self.current_player = self.player1  # black starts so human player starts
        self.directions = [(-1, -1), (1, 1), (1, -1), (-1, 1), (-1, 0), (0, -1), (0, 1), (1, 0)]


    def switch_player(self):
        """
        Switch the player
        """
        if self.current_player == self.player1:
            self.current_player = self.player2
        else:
            self.current_player = self.player1

    def validate_move(self, player, row, col):
        """
        If its an empty cell and will sandwich the other colored pieces
        :param player: the player
        :param row: the row
        :param col: the column
        """
        current_color = player.color
        opponent_color = -1 * (player.color)
        if not self.board.is_inside_borders(row, col):
            return False
        if self.board.get_cell(row, col) != 0:
            return False
        else:
            for (dx, dy) in self.directions:
                r = row + dx
                c = col + dy
                if not self.board.is_inside_borders(r, c): #out of the board
                    continue
                if self.board.get_cell(r, c) != opponent_color: #wont sandwich anything in this direction
                    continue

                # enters only if we have at least one opponent_cell to sandwich
                while True:
                    r += dx
                    c += dy
                    if not self.board.is_inside_borders(r, c):
                        break
                    current_cell = self.board.get_cell(r, c)
                    if current_cell == 0:
                        break #reached an empty cell - not good since were looking for a cell with current_color
                    if current_cell == current_color:
                        return True #found sandwich --> valid move

        return False


    def apply_move(self, player, row, col):
        """
        1. Place the piece on the board
        2. Flip the sandwiched pieces
        :param player: the player object
        :param row: the row where to place the piece
        :param col: the column where to place the piece
        """
        #1.
        self.board.set_cell(row, col, player.color)

        #2.
        self.flip_pieces(player, row, col)

    def flip_pieces(self, player, row, col):
        """
        Flip the sandwiched pieces
        :param player: the player object
        :param row: the row where to place the piece
        :param col: the column where to place the piece
        :return:
        """
        current_color = player.color
        opponent_color = -1 * (player.color)

        for (dx, dy) in self.directions:
            r = row + dx
            c = col + dy
            pieces_to_flip = []

            # Check if first adjacent cell is opponent
            while self.board.is_inside_borders(r, c) and self.board.get_cell(r, c) == opponent_color:
                pieces_to_flip.append((r, c))
                r += dx
                c += dy

            # Check if we found a sandwich (ended on our own color)
            if self.board.is_inside_borders(r, c) and self.board.get_cell(r, c) == current_color:
                # Flip all pieces in between
                for flip_r, flip_c in pieces_to_flip:
                    self.board.set_cell(flip_r, flip_c, current_color)

    def count_flips(self, player, row, col):
        """
        Count the number of flips made
        Will use this in optimizing computer choice - by choosing the move that will make the most flips and prefer the moves in the corners
        :param player: the player object
        :param row: the row where to place the piece
        :param col: the column where to place the piece
        :return: the number of total flips made for a move
        """
        if self.board.get_cell(row, col) != 0:
            return 0

        total_flips = 0
        current_color = player.color
        opponent_color = -current_color

        for dx, dy in self.directions:
            r, c = row + dx, col + dy
            flips_in_dir = 0

            # Count opponent pieces in this direction
            while self.board.is_inside_borders(r, c) and self.board.get_cell(r, c) == opponent_color:
                flips_in_dir += 1
                r += dx
                c += dy

            # Only if we reach a piece of the same color, add the flips
            if self.board.is_inside_borders(r, c) and self.board.get_cell(r, c) == current_color:
                total_flips += flips_in_dir

        return total_flips

    def computer_strategy(self, player):
        """
        Implement the strategy for the computer
        :param player: the player object
        :return: the best move - the one that makes the most flips and prefer the moves in the corners
        if not possible then random
        """
        moves = self.possible_moves(player)
        # corner priority
        corners = [(0, 0), (0, 7), (7, 0), (7, 7)]
        corner_moves = [m for m in moves if m in corners]
        if corner_moves:
            return random.choice(corner_moves)

        max_flips = max(self.count_flips(player, r, c) for r, c in moves)
        best_moves = [(r,c) for r, c in moves if self.count_flips(player, r, c) == max_flips]
        return random.choice(best_moves)

    def possible_moves(self, player):
        """
        Suggest next moves 
        :param player: the player object
        :return: a list of possible moves 
        """
        possible_moves = []
        for row in range(self.board.size):
            for col in range(self.board.size):
                if self.validate_move(player, row, col):
                    possible_moves.append((row, col))
        return possible_moves

    def has_moves(self, player):
        """
        Check if the player still has moves left
        :param player: the player object
        :return: true or false depending on if the player has moves
        """
        if self.possible_moves(player) == []:
            return False
        return True

    def game_over(self):
        """
        Check if the game is over
        :return: True only if both players dont have any moves left
        """
        return (
                not self.has_moves(self.player1) and
                not self.has_moves(self.player2)
        )
