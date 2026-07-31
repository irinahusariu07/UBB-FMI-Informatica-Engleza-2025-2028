"""
The SQL based repo
"""

import sqlite3
from domain.expenses import Expenses
from repository.json_repo import JSONRepository


class SQLRepo:
    def __init__(self, db_file = "expenses_file.db"):
        self.db = sqlite3.connect(db_file)
        self.cursor = self.db.cursor()

        self.cursor.execute('''CREATE TABLE IF NOT EXISTS expenses (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        day INTEGER,
        amount INTEGER,
        category TEXT
        )
        ''')
        self.db.commit()

    def add(self, expense):
        self.cursor.execute('''INSERT INTO expenses (day, amount, category)
        VALUES (?, ?, ?)''', (expense.day, expense.amount, expense.category))
        self.db.commit()

    def get_all(self):
        rows = self.cursor.execute(''' SELECT day, amount, category FROM expenses''').fetchall()
        return [Expenses(day, amount, category) for (day, amount, category) in rows]

    def filter_expenses(self, value):
        self.cursor.execute( '''
        DELETE FROM expenses WHERE amount <= ? ''')
        self.db.commit()


    def clear(self):
        self.cursor.execute('''DELETE FROM expenses''')
        self.db.commit()


