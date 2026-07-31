#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#
from functions import generate_random_expenses
from ui import run_ui

def start_program():
    expenses_list = generate_random_expenses(10)
    undo_stack = []

    # i should set a random current day
    current_day = 20
    run_ui(expenses_list, undo_stack, current_day)

if __name__ == "__main__":
    start_program()
