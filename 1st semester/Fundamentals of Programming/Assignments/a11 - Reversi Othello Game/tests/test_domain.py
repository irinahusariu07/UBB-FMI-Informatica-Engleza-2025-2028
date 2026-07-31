"""
Tests for the domain part - board actions
"""
import unittest
from domain.board import Board


class TestBoard(unittest.TestCase):
    def setUp(self):
        self.board = Board()

    def test_initial_setup(self):
        self.assertEqual(self.board.get_cell(3,3), -1)
        self.assertEqual(self.board.get_cell(4,4), -1)
        self.assertEqual(self.board.get_cell(3, 4), 1)
        self.assertEqual(self.board.get_cell(4, 3), 1)

        for row in range(self.board.size):
            for col in range(self.board.size):
                if (row, col) not in [(3,3), (4,4), (3,4), (4,3)]:
                    self.assertEqual(self.board.get_cell(row, col), 0)

    def test_get_set(self):
        self.board.set_cell(0, 0, -2)
        self.assertEqual(self.board.get_cell(0, 0), -2)

    def test_is_inside_borders(self):
        self.assertTrue(self.board.is_inside_borders(3,3))
        self.assertTrue(self.board.is_inside_borders(0,0))
        self.assertFalse(self.board.is_inside_borders(9,4))
        self.assertFalse(self.board.is_inside_borders(0,8))

    def test_count_pieces(self):
        black, white = self.board.count_pieces()
        self.assertEqual(black, 2)
        self.assertEqual(white, 2)
        self.board.set_cell(6, 7, -1)
        black, white = self.board.count_pieces()
        self.assertEqual(black, 3)
        self.assertEqual(white, 2)

