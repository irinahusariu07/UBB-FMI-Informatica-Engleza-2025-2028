"""
The binary file based repository
"""
import pickle
from domain.expenses import Expenses

class BinaryRepository:
    def __init__(self, filename):
        """
        :param filename: the name of the binary file
        """
        self.filename = filename
        self.data = []
        self.load_from_file()

    def load_from_file(self):
        """
        Loads expenses from the binary file
        If the file doesnt exist, starts with empty list
        """
        try:
            with open(self.filename, "rb") as f:
                self.data = pickle.load(f)

                #if not everything is an object from Expenses returns ampty list
                if not all(isinstance(e, Expenses) for e in self.data):
                    self.data = []

        except (FileNotFoundError, EOFError, pickle.UnpicklingError):
            #file is empty or corrupted -> start fresh
            self.data = []

    def save_to_file(self):
        """
        Saves expenses to the binary file
        """
        with open(self.filename, "wb") as f:
            pickle.dump(self.data, f)

    def add(self, expense:Expenses):
        """
        Adds expenses to the binary file
        :param expense: the new expense
        """
        if not isinstance(expense, Expenses):
            raise ValueError("Only Expenses objects can be added")
        self.data.append(expense)
        self.save_to_file()

    def get_all(self):
        """
        :return: a copy of all stored expenses
        """
        return list(self.data)

    def set_all(self, new_list):
        """
        Replace the current list with new_list and saves to file
        Used by undo
        :param new_list: the new list of expenses
        """
        self.data = list(new_list)
        self.save_to_file()