class TextFileRepo:
    def __init__(self, filename):
        self.filename = filename
        self.board = []
        self._load_file()

    def _load_file(self):
        self.board = []
        try:
            with open(self.filename, "r") as file:
                for line in file:
                    line = line.strip()
                    if line == "":
                        continue
                    row = [int(x) for x in line.split()]
                    self.board.append(row)
        except FileNotFoundError:
            pass

    def _save_file(self):
        with open(self.filename, "w") as f:
            for line in self.board:
                f.write(" ".join(str(x) for x in line) + "\n")

    def get_board(self):
        return self.board.copy()


