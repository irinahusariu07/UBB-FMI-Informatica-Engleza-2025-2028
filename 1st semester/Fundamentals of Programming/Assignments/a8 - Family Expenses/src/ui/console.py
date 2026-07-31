"""
The user interference part
"""
from domain import expenses
from services.expenses_services import ExpensesService
class Console:
    def __init__(self, service):
        self.service = service

    def start(self):
        while True:
            print("\n === Expenses. Object Oriented Programming ===")
            print("1. Add expense")
            print("2. List all expenses")
            print("3. Filter expenses. Keep only the expenses over a given value")
            print("4. Undo")
            print("0. Exit")

            cmd = input("Choose an option: ").strip()
            try:
                if cmd == "1":
                    self.ui_add_expense()
                elif cmd == "2":
                    self.ui_list_all()
                elif cmd == "3":
                    self.ui_filter()
                elif cmd == "4":
                    self.ui_undo()
                elif cmd == "0":
                    print("Exiting!")
                    break
                else:
                    print("Invalid command!")
            except ValueError as e:
                print("Error: ", e)

    def ui_add_expense(self):
        """
        Calls the add service from the Services module
        """
        day = int(input("Enter day: "))
        if day not in range(1,30):
            print("Error: Invalid day!")
            return
        amount = int(input("Enter amount: "))
        if amount <= 0:
            print("Error: Invalid amount!")
            return
        category = input("Enter category: ").strip()

        self.service.add_expense(day, amount, category)
        print("Expenses added successfully!")

    def ui_list_all(self):
        """
        Calls the list all service from the Services module
        """
        expense_list = self.service.list_expenses()
        if not expenses:
            print("No expenses found!")
            return
        print("Expenses: ")
        for e in expense_list:
            print(f"Day {e.day}: {e.amount} {e.category}")

    def ui_filter(self):
        """
        Calls the filter service from the Services module
        """
        limit = int(input("Enter limit:"))
        self.service.filter_expenses(limit)
        print("Expenses filtered successfully!")

    def ui_undo(self):
        """
        Calls the undo service from the Services module
        """
        self.service.undo()
        print("Undo successfully!")









