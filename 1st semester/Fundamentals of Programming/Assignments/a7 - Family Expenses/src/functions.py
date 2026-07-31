#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#
category_list = ["housekeeping", "food", "transport", "clothing", "internet", "others"]
def create_expense(day, amount, category):
    """
    Creates an expense entry - day, amount and category
    :param day: The day in which the expense will be created (1-30)
    :param amount: The amount of the expense (>0)
    :param category: The category of the expense from the category list
    :return: A new expense entry
    """
    return {
        "day": day,
        "amount": amount,
        "category": category
    }
import random


def generate_random_expenses(n=10):
    """
    A function that generates a random default list with expenses
    :param n: number of desired default expenses
    :return: the random expenses list
    """
    expenses_list = []

    for i in range(n):
        day = random.randint(1, 30)
        amount = random.randint(1, 500)
        category = random.choice(category_list)
        expense = create_expense(day, amount, category)
        expenses_list.append(expense)

    return expenses_list

def get_day(expense):
    """
    A function that gets the day from a dictionary
    :param expense: dictionary data
    :return: the day (1-30)
    """
    return expense["day"]

def set_day(expense, new_day):
    """
    A function that sets the day of a dictionary
    :param expense: dictionary data
    :param new_day: new day we want to set
    :return: changes the day (1-30)
    """
    expense["day"] = new_day

def get_amount(expense):
    """
    A function that gets the amount from a dictionary
    :param expense: dictionary data
    :return: the amount (>0)
    """
    return expense["amount"]

def set_amount(expense, new_amount):
    """
    A function that sets the amount from a dictionary
    :param expense: dictionary data
    :param new_amount: new amount we want to set (>0)
    :return: changes the amount
    """
    expense["amount"] = new_amount

def get_category(expense):
    """
    A function that gets the category from a dictionary
    :param expense: dictionary data
    :return: the category (from category_list)
    """
    return expense["category"]

def set_category(expense, new_category):
    """
    A function that sets the category from a dictionary
    :param expense: dictionary data
    :param new_category: new category we want to set (from category_list)
    :return: changes the category
    """
    expense["category"] = new_category

def validate_day(day):
    """
    Validates the day entered by the user
    :param day: The day entered by the user
    :return: Value Error if the day in the month is invalid
    """
    if not (1 <= day <= 30):
        raise ValueError("Invalid day. Day must be between 1 and 30.")

def validate_amount(amount):
    """
    Validates the amount entered by the user
    :param amount: The amount entered by the user
    :return: Value Error if the amount is less than 0
    """
    if not (amount > 0):
        raise ValueError("Invalid amount. Amount must be greater than 0.")

def validate_category(category):
    """
    Validates the category entered by the user
    :param category: The category entered by the user
    :return: Value Error if the category is not in the possible list of categories
    """
    if category not in category_list:
        raise ValueError(f"Invalid category. Category must be in {category_list}.")

def add_expense(expenses_list, amount, category, current_day):
    """
    Adds an expense to the list of expenses. Used at point A.
    :param expenses_list: the default list of expenses
    :param amount: the amount of the expense
    :param category: the category of the expense
    :param current_day: the current day of the expense
    :return: appends to the list of expenses the new entry
    :raises: Value Error if validation of the expense fails
    """
    validate_day(current_day)
    validate_amount(amount)
    validate_category(category)

    expense = create_expense(current_day, amount, category)
    expenses_list.append(expense)

def insert_expense(expenses_list, day, amount, category):
    """
    Inserts a new expense for the given day
    :param expenses_list: the default list of expenses
    :param day: the day of the expense
    :param amount: the amount of the expense
    :param category: the category of the expense
    :return: appends to the list of expenses the new entry
    :raises: Value Error if validation of the expense fails
    """
    validate_day(day)
    validate_amount(amount)
    validate_category(category)

    expense = create_expense(day, amount, category)
    expenses_list.append(expense)

def remove_day(expenses_list, day):
    """
    Removes all expenses from the list from the day mentioned by the user
    :param expenses_list: the default list of expenses
    :param day: the day that you want to remove the expenses from
    :return: removes the expenses from the list from the day mentioned by the user
    :raises: Value Error if the day in the month is invalid
    """
    validate_day(day)
    new_expenses_list = [] # makes a new list with the expenses we want to keep

    for expense in expenses_list:
        if get_day(expense) != day:
            new_expenses_list.append(expense)

    expenses_list.clear()
    expenses_list.extend(new_expenses_list)
    # i did it like this because if i wouldve simply written exp_list = new_exp_list, my list wouldntve changed for all the functions using my default list

def remove_day_interval(expenses_list, start_date, end_date):
    """
    Removes all expenses from the list from the interval mentioned by the user
    :param expenses_list: the default list of expenses
    :param start_date: the start date of the interval
    :param end_date: the end date of the interval
    :return: removes the expenses from the list from the interval mentioned by the user
    :raises: Value Error if the days in the month is invalid
    """
    validate_day(start_date)
    validate_day(end_date)

    if start_date > end_date:
        raise ValueError("Start date must be <= than end date.")

    new_expenses_list = []
    for expense in expenses_list:
        if get_day(expense) < start_date or get_day(expense) > end_date:
            new_expenses_list.append(expense)
    expenses_list.clear()
    expenses_list.extend(new_expenses_list)

def remove_category(expenses_list, category):
    """
    Removes all expenses from the list from the category mentioned by the user
    :param expenses_list: the default list of expenses
    :param category: the category of the expense
    :return: removes the expenses from the list from the category mentioned by the user
    :raises: Value Error if the category is invalid
    """
    validate_category(category)

    new_expenses_list = []
    for expense in expenses_list:
        if get_category(expense) != category:
            new_expenses_list.append(expense)
    expenses_list.clear()
    expenses_list.extend(new_expenses_list)

def list_all(expenses_list):
    """
    A funcion that lists all the existing expenses
    :param expenses_list: the default list of expenses
    :return: all the existing expenses
    """
    return expenses_list

def list_category(expenses_list, category):
    """
    A funcion that lists all the existing expenses from a given category
    :param expenses_list: the default list of expenses
    :param category: the category of the expense
    :return: all the existing expenses from a given category
    :raises: Value Error if the category is invalid
    """
    validate_category(category)
    all_categ_expenses = []
    for expense in expenses_list:
        if get_category(expense) == category:
            all_categ_expenses.append(expense)
    return all_categ_expenses

def list_category_amount(expenses_list, category, operator, amount):
    """
    A funcion that lists all the existing expenses from a given category where the amount checks a given condition
    :param expenses_list: the default list of expenses
    :param category: the category of the expense
    :param operator: the operator that gives the condition
    :param amount: the value for the condition
    :return: all the existing expenses from the given category that check the given condition
    :raises: Value Error if validation of the expense fails
    """
    validate_category(category)
    validate_amount(amount)

    result = []

    for expense in expenses_list:
        if get_category(expense) != category:
            continue
        if operator == "<" and get_amount(expense) < amount:
            result.append(expense)
        if operator == ">" and get_amount(expense) > amount:
            result.append(expense)
        if operator == "=" and get_amount(expense) == amount:
            result.append(expense)
    return result

def filter_category(expenses_list, category):
    """
    A function that keeps only the expenses that match the given category
    :param expenses_list: the default list of expenses
    :param category: the category we want to keep
    :return: deletes all the expenses that arent from the given category
    :raises: Value Error if category is invalid
    """
    validate_category(category)

    new_expenses_list = []
    for expense in expenses_list:
        if get_category(expense) == category:
            new_expenses_list.append(expense)
    expenses_list.clear()
    expenses_list.extend(new_expenses_list)

def filter_category_amount(expenses_list, category, operator,  amount):
    """
    A function that keeps only the expenses from one category that match a condition based on the amount
    :param expenses_list: the default list of expenses
    :param category: the category we want to keep
    :param operator: the operator that gives the condition
    :param amount: the value for the condition
    :return: deletes all the expenses that arent from the given category and that dont check the given condition
    :raises: Value Error if validation of the expense fails
    """
    validate_category(category)
    validate_amount(amount)

    new_expenses_list = []
    for expense in expenses_list:
        if get_category(expense) != category:
            continue

        if operator == "<" and get_amount(expense) < amount:
                new_expenses_list.append(expense)
        elif operator == ">" and get_amount(expense) > amount:
                new_expenses_list.append(expense)
        elif operator == "=" and get_amount(expense) == amount:
                new_expenses_list.append(expense)
    expenses_list.clear()
    expenses_list.extend(new_expenses_list)


