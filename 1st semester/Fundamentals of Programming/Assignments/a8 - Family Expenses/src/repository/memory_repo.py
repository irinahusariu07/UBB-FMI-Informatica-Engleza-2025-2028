"""
The memory based repository
"""
from domain.expenses import Expenses

class MemoryRepository:

    def __init__(self):
        """
        An internal list
        """
        self.data = []

    def add(self, expense: Expenses):
        """
        Add a new expemse to the repository
        :param expense: an Expenses object
        """
        if not isinstance(expense, Expenses):
            raise ValueError("Only Expenses objects are allowed")
        self.data.append(expense)

    def get_all(self):
       """
       :return: a list of all expenses
       """
       return list(self.data)

    def set_all(self, new_list):
        """
        Replace all stored expenses with the ones in the new list
        :param new_list: list of Expenses objects
        """
        self.data = list(new_list)

