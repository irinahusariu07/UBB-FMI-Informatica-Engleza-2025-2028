"""
This is where i define the domain in Task 2 - Expenses
"""

class Expenses:
    def __init__(self, day, amount, category):
        self.day = day
        self.amount = amount
        self.category = category

    def __str__(self):
        return f"Day: {self.day}, Amount:{self.amount}, Category:{self.category}"

