"""
The text file based repository
"""
from domain.expenses import Expenses

class TextFileRepo:
    def __init__(self, filename):
        """
        :param filename: the name of the text file
        """
        self.filename = filename
        self.data = []
        self.load_from_file()

    def load_from_file(self):
        """
        Reads all expenses from the file into memory.
        If file doesnt exist or is empty, loads an empty list
        (Like the default list from memory)
        """
        try:
            with open(self.filename, "r") as file:
                for line in file:
                    line = line.strip()
                    if not line:
                        continue
                    # every line should be of type "day, amount, category"
                    parts = line.split(",")
                    if len(parts) != 3: #that means we dont have the correct format
                        continue

                    day = int(parts[0])
                    amount = int(parts[1])
                    category = parts[2]

                    self.data.append(Expenses(day, amount, category))

        except FileNotFoundError:
            # No file - start with empty repository
            self.data = []

    def save_to_file(self):
        """
        Writes all expenses back into the text file
        """
        with open(self.filename, "w") as file:
            for expense in self.data:
                file.write(f"{expense.day}, {expense.amount}, {expense.category}\n")

    def add(self, expense: Expenses):
        """
        Add a new expense and save it to the text file
        :param expense: the new expense
        """
        self.data.append(expense)
        self.save_to_file()

    def get_all(self):
        """
        :return: a copy of all expenses stored into memory
        """
        return list(self.data)

    def set_all(self, new_list):
        """
        Replace all internal expenses and save them to the text file
        Used by undo
        :param new_list: the new list of expenses
        """
        self.data = list(new_list)
        self.save_to_file()

        