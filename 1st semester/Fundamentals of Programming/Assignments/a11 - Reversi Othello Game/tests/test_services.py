"""
Tests for the services part
"""
import unittest

from domain.board import Board
from domain.player import Player
from services.reversi_services import GameService


class TestReversiService(unittest.TestCase):

    def setUp(self):
        self.board = Board()
        self.human = Player(-1, "human")
        self.computer = Player(1, "computer")
        self.service = GameService(self.board, self.human, self.computer)


    def test_validate_move(self):
        # human can play (4,2) initially
        self.assertTrue(self.service.validate_move(self.human, 4, 2))
        # human cant play (3,3) because its occupied
        self.assertFalse(self.service.validate_move(self.human, 3, 3))
        # human cant play (8, 0) because its out of borders
        self.assertFalse(self.service.validate_move(self.human, 8, 0))

    def test_apply_move_flips(self):
        # Apply move at (4,2)
        self.service.apply_move(self.human, 4, 2)
        # Check that (4,3) flipped from 1 -> -1
        self.assertEqual(self.board.get_cell(4, 3), -1)
        # Check the new piece
        self.assertEqual(self.board.get_cell(4, 2), -1)

    def test_possible_moves_initial(self):
        moves = self.service.possible_moves(self.human)
        # Human has moves at 4 positions at start
        expected = [(2, 4), (4, 2), (3, 5), (5, 3)]
        for move in expected:
            self.assertIn(move, moves)
        self.assertEqual(len(moves), 4)

    def test_count_flips(self):
        flip = self.service.count_flips(self.human, 2, 4)
        self.assertEqual(flip, 1)

    def test_switch_player(self):
        self.assertEqual(self.service.current_player, self.human)
        self.service.switch_player()
        self.assertEqual(self.service.current_player, self.computer)
        self.service.switch_player()
        self.assertEqual(self.service.current_player, self.human)

    def test_game_over(self):
        # Fill the board with black pieces, no moves left
        for r in range(self.board.size):
            for c in range(self.board.size):
                self.board.set_cell(r, c, -1)
        self.assertTrue(self.service.game_over())

    def test_choose_computer_move(self):
        move = self.service.computer_strategy(self.computer)
        self.assertIn(move, self.service.possible_moves(self.computer))
