#
# User interface section
#
from functions import create_flights, default_flights_list, add_flight
from functions import format_flight, modify_duration, change_destination




def show_menu():

    print("\n === AIRPORT ===")
    print("1. Add a flight - code, duration, departure city, destination city")
    print("2. Modify duration of a given flight - enter code and new duration")
    print("3. Rerout flights - enter initial destination city and new destination city")
    print("4. Show all flights with a given departure city sorted increasingly by duration")
    print("0. Exit")

def check_task():
    n = input("Choose the task: ")
    if n.isdigit() and 0 <= int(n) <= 4:
        return int(n)
    else:
        print("Invalid input. Choose an existing task")

def run():
    flights_list = default_flights_list()
    while True:
        show_menu()
        choice = check_task()

        if choice == 0:
            print("Exiting!")
            break

        if choice == 1:
            # Add a new flight
            code = input("Enter code: ")
            if (len(code) < 3):
                print("Length of code is too short. Must be greater than 3")
                continue
            duration = input("Enter duration: ")
            try:
                duration = int(duration)
                if duration < 20:
                    print("Duration must be a number greater than 20")
                    continue
            except ValueError:
                print("Error: Must be a number.")
                continue

            departure = input("Enter departure city: ")
            if (len(departure) < 3):
                print("Length of departure is too short. Must be greater than 3")
                continue
            destination = input("Enter destination city: ")
            if (len(destination) < 3):
                print("Length of destination is too short. Must be greater than 3")
                continue

            add_flight(flights_list, code, duration, departure, destination)
            print("Flight added!")

            for f in flights_list:
                print(format_flight(f))

        if choice == 2:
            # Modify duration
            code = input("Enter code: ").strip()
            new_duration = input("Enter the new duration: ")

            try:
                new_duration = int(new_duration)
                results = modify_duration(flights_list, code, new_duration)
                print("Duration updated successfully!")

            except ValueError as e:
                print("Error:", e)
                continue

            for f in results:
                print(format_flight(f))



        if choice == 3:
            # Modify destination
            initial_destination = input("Enter initial destination: ")
            if (len(initial_destination) < 3):
                print("Length of destination is too short. Must be greater than 3")
                continue

            new_destination = input("Enter new destination: ")
            if (len(new_destination) < 3):
                print("Length of destination is too short. Must be greater than 3")
                continue
            try:
                flights_list = change_destination(flights_list, initial_destination, new_destination)
                results = flights_list
                print("Destination changed successfully!")

            except ValueError as e:
                print("Error:", e)
                continue

            for f in  results:
                print(format_flight(f))



        if choice == 4:
            # Show all flights with a given destination
            pass


if __name__ == '__main__':
    run()