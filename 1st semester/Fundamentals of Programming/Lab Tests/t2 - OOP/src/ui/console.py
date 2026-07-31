class ConsoleUI:
    def __init__(self, service):
        self.__service = service

    def run(self):
        while True:
            print("Choose one of the following commands: display, drivers, closest, exit")
            print("display - displays a list of all drivers and all addresses.txt")
            print("drivers - displays a list of all drivers sorted by distance to given coordinates")
            print("closest - for each address prints the closest driver")
            print("exit - exit the program")

            cmd = input("> ").lower().strip()

            if cmd == "display":
                for d in self.__service.get_sorted_drivers():
                    print(d)
                for a in self.__service.get_sorted_addresses():
                    print(a)


            elif cmd == "drivers":

                address_id = int(input("Address id: "))
                try:
                    result = self.__service.drivers_by_distance_to_address_id(address_id)

                    for pair in result:
                        print(pair[0], "distance =", pair[1])
                except ValueError as e:
                    print(e)

            elif cmd == "closest":
                result = self.__service.closest_driver_for_each_address()
                for item in result:
                    print(item[0], "->", item[1], "distance =", item[2])

            elif cmd == "exit":
                break

            else:
                print("Invalid command")