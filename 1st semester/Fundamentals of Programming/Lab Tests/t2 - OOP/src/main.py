from src.repository.driver_repo import DriverRepoFile
from src.repository.address_repo import AddressRepoFile
from src.services.taxi_services import TaxiService
from src.ui.console import ConsoleUI

def main():
    driver_repo = DriverRepoFile("drivers.txt")
    address_repo = AddressRepoFile("addresses.txt")

    service = TaxiService(driver_repo, address_repo)
    ui = ConsoleUI(service)

    ui.run()

if __name__ == "__main__":
    main()
