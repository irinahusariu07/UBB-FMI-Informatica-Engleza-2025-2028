"""
The JSON repo - Bonus
"""
import json
from fileinput import filename

from domain.expenses import Expenses

class JSONRepository:
    def __init__(self, filename):
        self.filename = filename
        self.data = []
        self.load_from_file()

    def load_from_file(self):
        """
        Load expenses from JSON file
        If file is missing start with empty list
        """
        try:
            with open(self.filename) as f:
                raw_list = json.load(f)

            self.data = [
                Expenses(item["day"], item["amount"], item["category"])
                for item in raw_list
            ]

        except (FileNotFoundError, json.JSONDecodeError):
            self.data = []

    def save_to_file(self):
        """
        Save expenses to JSON file
        """
        data_list = [
            {
                "day":e.day,
                "amount":e.amount,
                "category":e.category
            }
            for e in self.data
        ]
        with open(self.filename, 'w') as f:
            json.dump(data_list, f, indent=4)

    def add(self, expense:Expenses):
        """
        Add an expense
        :param expense: the expense
        """
        if not isinstance(expense, Expenses):
            raise ValueError("Expenses must be of type Expenses")
        self.data.append(expense)
        self.save_to_file()

    def get_all(self):
        """
        :return: a list of all expenses
        """
        return list(self.data)

    def set_all(self, new_list):
        self.data = list(new_list)
        self.save_to_file()

