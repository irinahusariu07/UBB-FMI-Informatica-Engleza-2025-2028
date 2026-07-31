class GameBoard:
    def __init__(self, matrix):
        self._matrix = matrix
        self._rows = len(matrix)
        self._cols = len(matrix[0])

    @property
    def matrix(self):
        return self._matrix

    @property
    def rows(self):
        return self._rows

    @property
    def cols(self):
        return self._cols