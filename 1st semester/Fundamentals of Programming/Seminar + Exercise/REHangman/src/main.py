from repository.text_repo import TextFileRepository
from services.hangman_services import HangmanService
from ui.console import HangmanConsole


def main():
    repo = TextFileRepository("hangman_senteces.txt")
    serivces = HangmanService(repo)
    ui = HangmanConsole(serivces)
    ui.run()

if __name__ == "__main__":
    main()