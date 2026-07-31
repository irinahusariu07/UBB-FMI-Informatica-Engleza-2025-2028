"""
Tests for the first functionality - Adding an expense
"""
from domain.expenses import Expenses
from services.expenses_services import ExpensesService
from repository.memory_repo import MemoryRepository
from repository.textfile_repo import TextFileRepo
from repository.binary_repo import BinaryRepository
import os

def test_add_valid_memory():
    repo = MemoryRepository()
    service = ExpensesService(repo)

    service.add_expense(10, 100, "food")
    all_exp = service.list_expenses()

    assert len(all_exp) == 1
    assert all_exp[0].day == 10
    assert all_exp[0].amount == 100
    assert all_exp[0].category == "food"

def test_add_valid_text():
    filename = "test_expenses.txt"
    #i check if there is a file with the same name and delete it
    if os.path.exists(filename):
        os.remove(filename)

    repo = TextFileRepo(filename)
    service = ExpensesService(repo)

    service.add_expense(10, 100, "food")
    items = repo.get_all()
    assert len(items) == 1
    assert items[0].day == 10
    assert items[0].category == "food"

    os.remove(filename)

def test_add_valid_binary():
    filename = "test_expenses.bin"

    if os.path.exists(filename):
        os.remove(filename)

    repo = BinaryRepository(filename)
    service = ExpensesService(repo)

    service.add_expense(10, 100, "food")
    items = repo.get_all()
    assert len(items) == 1
    assert items[0].day == 10
    assert items[0].category == "food"
    assert items[0].amount == 100

    os.remove(filename)

def run_tests():
    test_add_valid_memory()
    test_add_valid_text()
    test_add_valid_binary()
    print("All tests passed")
