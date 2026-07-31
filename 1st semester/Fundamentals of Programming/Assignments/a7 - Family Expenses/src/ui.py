#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#
from texttable import Texttable
from functions import list_all, list_category, list_category_amount
from functions import filter_category_amount,  filter_category
from functions import add_expense, insert_expense
from functions import remove_category, remove_day, remove_day_interval
import copy

def show_expense_table(expenses_list):
    table = Texttable()
    table.header(["Day", "Amount", "Category"])

    for expense in expenses_list:
        table.add_row([expense["day"], expense["amount"], expense["category"]])
    print(table.draw())



def save_history(expenses_list, undo_stack):
    """
    A function that stores a copy of list
    :param expenses_list: the default list of expenses
    :param undo_stack: the history
    :return: the history
    """
    undo_stack.append(copy.deepcopy(expenses_list))

def handle_A_command(expenses_list, command_words, undo_stack, current_day):
    """
    The UI function for A
    :param expenses_list: the default list of expenses
    :param command_words: what user inputs
    :param undo_stack: the history
    :return: a message if the element was added or inserted successfully
    """
    try:
        # Case: add <sum> <category>
        if command_words[0] == "add" and len(command_words) == 3:
            amount = int(command_words[1])
            category = command_words[2]

            save_history(expenses_list, undo_stack)
            add_expense(expenses_list, amount, category, current_day)
            print("Expense added successfully")
            return

        # Case: insert <day> <sum> <category>
        if command_words[0] == "insert" and len(command_words) == 4:
            day = int(command_words[1])
            amount = int(command_words[2])
            category = command_words[3]

            save_history(expenses_list, undo_stack)
            insert_expense(expenses_list, day, amount, category)
            print("Expense inserted successfully")
            return

        print("Invalid add/insert command")

    except ValueError as ve:
        print("Error:", ve)

def handle_B_command(expenses_list, command_words, undo_stack):
    """
    The UI function for B
    :param expenses_list: the default list of expenses
    :param command_words: what user inputs
    :param undo_stack: the history
    :return: A message if the element was removed successfuly
    """
    try:
        # Case: remove <day> or <category>
        if len(command_words) == 2:
            if command_words[1].isdigit():
                day = int(command_words[1])

                save_history(expenses_list, undo_stack)
                remove_day(expenses_list, day)
                print("Removed expenses for day", day)
                return
            else:
                category = command_words[1]

                save_history(expenses_list, undo_stack)
                remove_category(expenses_list, category)
                print("Removed expenses for category", category)
                return
        # Case: remove <start> to <end>
        if len(command_words) == 4 and command_words[2] == "to":
            start = int(command_words[1])
            end = int(command_words[3])

            save_history(expenses_list, undo_stack)
            remove_day_interval(expenses_list, start, end)
            print(f"Removed expenses from day {start} to {end}")
            return

        print("Invalid remove command")
    except ValueError as ve:
        print("Error:", ve)

def handle_C_command(expenses_list, command_words):
    """
    The UI function for option C
    :param expenses_list: the default list of expenses
    :param command_words: what the user inputs
    :return: a table
    """
    # Case: list
    if len(command_words) == 1:
        result = list_all(expenses_list)
        show_expense_table(result)
        return
    # Case: List <category>
    if len(command_words) == 2:
        category = command_words[1]
        result = list_category(expenses_list, category)
        show_expense_table(result)
        return
    # Case: List <category> <operator> <value>
    if len(command_words) == 4:
        category = command_words[1]
        operator = command_words[2]
        amount = int(command_words[3])
        result = list_category_amount(expenses_list, category, operator, amount)
        show_expense_table(result)
        return

    print("Invalid list command!")
def handle_D_command(expenses_list, command_words, undo_stack):
    """
    The UI function for option D
    :param expenses_list: the default list of expenses
    :param command_words: what user inputs
    :param undo_stack: the history
    :return: a list of expenses
    """
    # Case: Filter <category>
    if len(command_words) == 2:
        category = command_words[1]

        save_history(expenses_list, undo_stack)
        filter_category(expenses_list, category)
        return

    # Case: Filter <category> <operator> <value>
    if len(command_words) == 4:
        category = command_words[1]
        operator = command_words[2]
        amount = int(command_words[3])

        save_history(expenses_list, undo_stack)
        filter_category_amount(expenses_list, category, operator, amount)
        return

    print("Invalid filter command!")

def handle_undo(expenses_list, undo_stack):
    if not undo_stack:
        print("Nothing to undo!")
        return

    last_state = undo_stack.pop() #remove and get last saved list
    expenses_list.clear()
    expenses_list.extend(last_state)
    print("Undo successful")

def run_ui(expenses_list, undo_stack, current_day):
    print("\n===FAMILY EXPENSES. ASSIGNMENT 07 ===")
    print("Possible instructions:")
    print("add <sum> <category>")
    print("insert <day> <sum> <category>")
    print("remove <day>")
    print("remove <start day> to <end day>")
    print("remove <category>")
    print("list")
    print("list <category>")
    print("list <category> [ < | = | > ] <value>")
    print("filter <category>")
    print("filter <category> [ < | = | > ] <value>")
    print("undo")
    print ("\n The default category list: housekeeping, food, transport, clothing, internet, others")
    while True:
        command = input("Enter your command: ").lower().strip()
        command_words = command.split()

        if len(command_words) == 0:
            continue

        cmd = command_words[0]

        if cmd in ["add", "insert"]:
            handle_A_command(expenses_list, command_words, undo_stack, current_day)

        elif cmd == "remove":
            handle_B_command(expenses_list, command_words, undo_stack)

        elif cmd == "list":
            handle_C_command(expenses_list, command_words)

        elif cmd == "filter":
            handle_D_command(expenses_list, command_words, undo_stack)

        elif cmd == "undo":
            handle_undo(expenses_list, undo_stack)

        elif cmd == "exit":
            break

        else:
            print("Unknown command!")