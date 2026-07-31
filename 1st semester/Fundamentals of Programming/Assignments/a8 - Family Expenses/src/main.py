from repository.memory_repo import MemoryRepository
from repository.sql_repo import SQLRepo
from repository.textfile_repo import TextFileRepo
from repository.binary_repo import BinaryRepository
from services.expenses_services import ExpensesService
from ui.console import Console
from testing.tests import run_tests
from repository.json_repo import JSONRepository
from settings_reader import load_settings
from repository.sql_repo import SQLRepo

def main():
    try:
        run_tests()
    except AssertionError:
        print("Tests failed")

    # Read settings
    settings = load_settings()

    repo_type = settings.get("repo", "memory").lower()
    file_name = settings.get("file", "expenses_file.txt")

    # Choose repository automatically
    if repo_type == "memory":
        repo = MemoryRepository()
        print("Using memory repository")

    elif repo_type == "textfile":
        repo = TextFileRepo(file_name)
        print("Using text file repository")

    elif repo_type == "binaryfile":
        repo = BinaryRepository(file_name)
        print("Using binary repository")

    elif repo_type == "json":
        repo = JSONRepository(file_name)
        print("Using JSON repository")

    elif repo_type == "sql":
        repo = SQLRepo(file_name)
        print("Using SQL database repository")

    else:
        print("Invalid repository in settings! Using memory.")
        repo = MemoryRepository()

    # Create service
    service = ExpensesService(repo)

    # Generate 10 default expenses
    service.generate_default_Expenses()

    # Start console
    ui = Console(service)
    ui.start()

if __name__ == "__main__":
    main()


