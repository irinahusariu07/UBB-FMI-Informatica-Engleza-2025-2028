from functions import add_expense, insert_expense
from functions import get_day, get_amount, get_category
from functions import remove_day, remove_day_interval, remove_category
from functions import category_list
from functions import create_expense
from functions import list_all, list_category, list_category_amount


def test_add_expense():
    expenses = []
    add_expense(expenses, 50, "food", 10)
    assert len(expenses) == 1
    assert get_day(expenses[0]) == 10
    assert get_amount(expenses[0]) == 50
    assert get_category(expenses[0]) == "food"

def test_insert_expense():
    expenses = []
    insert_expense(expenses, 25, 100, "internet")
    assert len(expenses) == 1
    assert get_day(expenses[0]) == 25
    assert get_amount(expenses[0]) == 100
    assert get_category(expenses[0]) == "internet"

def test_remove_day():
    expenses = [
        create_expense(10, 50, "food"),
        create_expense(11, 50, "others"),
        create_expense(20, 50, "food"),
        create_expense(23, 50, "internet"),
        create_expense(10, 50, "others")
    ]
    remove_day(expenses, 10)
    assert len(expenses) == 3

def test_remove_day_interval():
    expenses = [
        create_expense(10, 50, "food"),
        create_expense(11, 50, "others"),
        create_expense(20, 50, "food"),
        create_expense(23, 50, "internet"),
        create_expense(10, 50, "others")
    ]
    remove_day_interval(expenses, 7, 12)
    assert len(expenses) == 2

def test_remove_category():
    expenses = [
        create_expense(10, 50, "food"),
        create_expense(11, 50, "others"),
        create_expense(20, 50, "food"),
        create_expense(23, 50, "internet"),
        create_expense(10, 50, "others")
    ]
    remove_category(expenses, "food")
    assert len(expenses) == 3

def run_tests():
    test_add_expense()
    test_insert_expense()
    test_remove_day()
    test_remove_day_interval()
    test_remove_category()
    print("All tests passed!")

if __name__ == '__main__':
    run_tests()
