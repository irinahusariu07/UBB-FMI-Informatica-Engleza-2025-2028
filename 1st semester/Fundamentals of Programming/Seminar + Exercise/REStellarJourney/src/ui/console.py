from src.domain.stellar_class import GameBoard
from src.repository.text_repo import TextFileRepo
from src.services.stellar_services import GameService

class StellarConsole:

   def __init__(self, service):
        self.service = service

   def run(self):
        while True:
            try:
                command_line = input("enter your command ").strip()
                parts = command_line.split(maxsplit=1)
                if not parts:
                    continue
                command = parts[0]
                if len(parts) > 1:
                    args = parts[1]
                else:
                    args = ""
                if command == "display":
                    game_board = self.service.print_board()
                    print(game_board)
                elif command == "place":
                    self.service.place_stars()
                    game_board = self.service.print_board()
                    print(game_board)
                elif command == "ship":
                    self.service.place_E()
                    game_board = self.service.print_board()
                    print(game_board)
                    e_x, e_y = self.service.get_E()
                    print(e_x, e_y)
                elif command == "cruisers":
                    self.service.place_B()
                    game_board = self.service.print_board()
                    print(game_board)
                elif command == "move":
                    try:
                        l = args[0]
                        c = int(args[1])
                        l = ord(l) - ord('A')
                        c = c - 1
                        self.service.move(l, c)
                        game_board = self.service.print_board()
                        print(game_board)
                    except ValueError as ve:
                        print(ve)
            except ValueError as ve:
                print(ve)
if __name__ == "__main__":
    r = TextFileRepo(r"C:\Users\irina\PycharmProjects\REStellarJourney\src\repository\board.txt")
    matrix = r.get_board()
    c = GameBoard(matrix)
    s = GameService(c)
    co = StellarConsole(s)
    co.run()
