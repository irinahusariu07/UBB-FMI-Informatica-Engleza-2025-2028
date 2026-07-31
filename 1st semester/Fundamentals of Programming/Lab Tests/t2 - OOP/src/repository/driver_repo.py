from src.domain.driver import Driver
import os

class DriverRepoFile:
    def __init__(self, filename):
        self.__filename = filename
        self.__ensure_file_exists()

    def __ensure_file_exists(self):
        if not os.path.exists(self.__filename):
            with open(self.__filename, "w"):
                pass

    def list_all(self):
        drivers = []
        with open(self.__filename, "r") as f:
            for line in f:
                line = line.strip()
                if line == "":
                    continue

                parts = line.split(",")
                name = parts[0]
                x = int(parts[1])
                y = int(parts[2])

                drivers.append(Driver(name, x, y))
        return drivers
