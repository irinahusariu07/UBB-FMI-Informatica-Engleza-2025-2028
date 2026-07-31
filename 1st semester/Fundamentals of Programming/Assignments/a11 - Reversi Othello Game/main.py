from domain.board import Board
from domain.player import Player
from services.reversi_services import GameService
from ui.GUI import GUI_Console
from ui.console import Console

def main():
    board = Board()
    human = Player(-1, "human")
    computer = Player(1, "computer")
    game_service = GameService(board, human, computer)
    print("What UI do you want to use?")
    print("1. Basic UI")
    print("2. GUI")
    choice = int(input("> "))
    try:
        if choice == 1:
            console = Console(game_service)
            console.run()
        elif choice == 2:
            console = GUI_Console(game_service)
            console.start()
    except ValueError:
        print("Invalid choice. Using default Basic UI")
        console = Console()
        console.run()


if __name__ == "__main__":
    main()
