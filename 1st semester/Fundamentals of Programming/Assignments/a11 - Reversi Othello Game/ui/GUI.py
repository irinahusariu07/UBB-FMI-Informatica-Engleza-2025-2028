"""
GUI Console
"""
import tkinter as tk
from tkinter import messagebox
class GUI_Console:

    def __init__(self, game_service):
        self.root = tk.Tk()
        self.root.title("Reversi (Othello)")
        self.game_service = game_service

        self.board_frame = tk.Frame(self.root)
        self.board_frame.grid(row=0, column=0, padx=10, pady=10)

        self.score_label = tk.Label(self.root, text="", font=("Times New Roman", 16, "bold"))
        self.score_label.grid(row=1, column=0, pady=10)

        self.buttons = []
        self.create_board()
        self.update_board()

    def start(self):
        self.root.mainloop()

    def create_board(self):
        size = self.game_service.board.size
        for row in range(size):
            button_row = []
            for col in range(size):
                btn = tk.Button(self.board_frame, width=4, height=2, font=("Times New Roman", 20, "bold"),
                                command =lambda r=row, c=col: self.on_click(r,c))
                btn.grid(row=row, column=col, padx=1, pady=1)
                button_row.append(btn)
            self.buttons.append(button_row)

    def update_board(self):
        size = self.game_service.board.size
        for row in range(size):
            for col in range(size):
                value = self.game_service.board.get_cell(row, col)
                btn = self.buttons[row][col]
                bg_color = "salmon"
                if value == 0:
                    btn.config(text="", bg=bg_color)
                elif value == -1:
                    btn.config(text="", bg="black")
                elif value == 1:
                    btn.config(text="", bg="white")

        player = self.game_service.current_player
        if player.type == "human":
            self.highlight_moves(player)

        self.update_score()

        if self.game_service.game_over():
            self.show_game_over()

    def on_click(self, row, col):
        player = self.game_service.current_player
        if player.type != "human":
            return
        if not self.game_service.validate_move(player, row, col):
            return # ignore invalid clicks
        self.game_service.apply_move(player, row, col)
        self.game_service.switch_player()
        self.update_board()
        self.root.after(500, self.computer_turn)

    def computer_turn(self):
        player = self.game_service.current_player
        if player.type != "computer":
            return
        if not self.game_service.has_moves(player):
            self.game_service.switch_player()
            return

        row, col = self.game_service.computer_strategy(player)
        self.game_service.apply_move(player, row, col)
        self.game_service.switch_player()
        self.update_board()

    def highlight_moves(self, player):
        moves = self.game_service.possible_moves(player)
        for row, col in moves:
            btn = self.buttons[row][col]
            if self.game_service.board.get_cell(row, col) == 0:
                btn.config(text="⃣", fg="black", bg="salmon")

    def update_score(self):
        black, white = self.game_service.board.count_pieces()
        self.score_label.config(text=f"Black: {black} White: {white}")

    def show_game_over(self):
        black, white = self.game_service.board.count_pieces()
        size = self.game_service.board.size
        empty = size ** 2 - black - white

        if black > white:
            black += empty  # give all remaining empty tiles to black
            winner = "Black wins!"
        elif white > black:
            white += empty  # give all remaining empty tiles to white
            winner = "White wins!"
        else:
            winner = "Draw!"

        messagebox.showinfo(
            "Game Over",
            f"Game over!\n{winner}\nBlack: {black}, White: {white}"
        )
