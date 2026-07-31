from src.domain.address import Address
import os

class AddressRepoFile:
    def __init__(self, filename):
        self.__filename = filename
        self.__ensure_file_exists()

    def __ensure_file_exists(self):
        if not os.path.exists(self.__filename):
            with open(self.__filename, "w"):
                pass

    def list_all(self):
        addresses = []
        with open(self.__filename, "r") as f:
            for line in f:
                line = line.strip()
                if line == "":
                    continue

                parts = line.split(",")
                addr_id = int(parts[0])
                name = parts[1]
                x = int(parts[2])
                y = int(parts[3])

                addresses.append(Address(addr_id, name, x, y))
        return addresses
