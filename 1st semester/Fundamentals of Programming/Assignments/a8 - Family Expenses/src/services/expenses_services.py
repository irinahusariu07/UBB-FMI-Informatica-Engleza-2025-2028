"""
This is where i write the logic of the program
"""
from domain.expenses import Expenses
import random

class ExpensesService:
    def __init__(self, repo):
        """
        The list of expenses
        :param repo: expenses repository
        """
        self.repo = repo
        self.history = []

    def validate_expense(self, day, amount, category):
        """
        Where i check if everything that was inputed is ok
        :param day: the day of the expense
        :param amount: the amount of the expense
        :param category: the category of the expense
        :raises: ValueError for everything that doesnt check the conditions
        """
        if not (1 <= day <= 30):
            raise ValueError("Day must be between 1 and 30")

        if amount <= 0:
            raise ValueError("Amount must be positive")

        if category.strip() == "":
            raise ValueError("Category must not be empty")


    def save_copy(self):
        """
        Save a copy of the stored expenses
        :return: appends in history
        """
        current = self.repo.get_all()

        snapshot = [Expenses(e.day, e.amount, e.category) for e in current]
        self.history.append(snapshot)

    def undo(self):
        """
        Performs the undo action
        :return: the list without the last action
        """
        if not self.history:
            raise ValueError("Nothing to undo")
        last_state = self.history.pop()
        self.repo.set_all(last_state)

    def add_expense(self, day, amount, category):
        """
        Creates and stores a new expense
        :param day: the day of the expense
        :param amount: the amount of the expense
        :param category: the category of the expense
        :return: adds a new expense
        """
        self.validate_expense(day, amount, category)
        self.save_copy()

        expense = Expenses(day, amount, category)
        self.repo.add(expense)

    def list_expenses(self):
        """
        List all expenses
        :return: a list of all stored expenses
        """
        return self.repo.get_all()

    def filter_expenses(self, value):
        """
        Filters expenses where amount > given value
        :param value: min value
        :return: Expenses over a certain value
        """
        #copy for undo
        self.save_copy()

        current = self.repo.get_all() #toata lista
        filtered = [e for e in current if e.amount > value] #le iau doar pe cele care indeplinesc criteriul
        self.repo.set_all(filtered) #replace the current list where it is stored with filtered

    def generate_default_Expenses(self, n=10):
        """
        Generates 10 default expenses
        :param n: 10 = no of expenses
        """
        categories = ["food", "transport", "housekeeping", "clothing", "internet", "others"]
        for i in range(n):
            day = random.randint(1, 30)
            amount = random.randint(1, 500)
            category = random.choice(categories)

            expense = Expenses(day, amount, category)
            self.repo.add(expense)



