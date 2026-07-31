#
# Functions section
#

def create_flights(code, duration, departure, destination):
    """
    A function that creates a flight
    :param code: the code of the flight
    :param duration: the length of the flight
    :param departure: departure city of the flight
    :param destination: destination city of the flight
    :return: a new dictionary entry
    """

    return{
        "code": code,
        "duration" : duration,
        "departure" : departure,
        "destination" : destination
    }

def default_flights_list():
    """
    A function that returns a list of default flights
    :return: default list of 3 flights hard coded
    """
    default_flights = [
        create_flights("0B3002", 45, "Cluj-Napoca", "London"),
        create_flights("4A5005", 75, "Bucharest", "Prague"),
        create_flights("7C3007", 60, "Cluj-Napoca", "Milan")
    ]
    return default_flights

def get_code(flight):
    """
    A function that gets the code of a flight
    :param flight: dict entry
    :return: code of the flight
    """
    return flight["code"]

def get_duration(flight):
    """
    A function that gets the duration of a flight
    :param flight: dict entry
    :return: duration of the flight
    """
    return flight["duration"]

def get_departure(flight):
    """
    A function that gets the departure of a flight
    :param flight: dict entry
    :return: departure city
    """
    return flight["departure"]

def get_destination(flight):
    """
    A function that gets the destination of a flight
    :param flight: dict entry
    :return: destination city
    """
    return flight["destination"]

def set_duration(flight, new_duration):
    """
    A function that sets the duration of a flight
    :param flight: dict entry
    :param new_duration: the new duration
    :return: modifies the duration of the flight
    """
    flight["duration"] = new_duration

def set_destination(flight, new_destination):
    """
    A function that sets the destination of a flight
    :param flight: dict entry
    :param new_destination: the new destination city
    :return: modifies the destination of the flight
    """
    flight["destination"] = new_destination

def format_flight(flight):
    """
    A function that formats a flight
    :param flight: dict entry
    :return: hides the internal representation
    """
    return f"{flight['code']} {flight['duration']} {flight['departure']} {flight['destination']}"

def normalize_input(text):
    """
    A function that normalizes the input
    :param text: a text
    :return: the text but normalized
    """
    return " ".join(text.lower().strip().split())

def add_flight(default_flights, code, duration, departure, destination):
    """
    A function that adds a flight used for task 1.
    :param default_flights: the list of existing flights
    :param code: the code of flight
    :param duration: the duration of flight
    :param departure: the departure city of flight
    :param destination: the destination city of flight
    :return: the list of flights
    """
    if not (len(code) >= 3):
        raise ValueError("Code is too short")
    if not (len(destination) >= 3):
        raise ValueError("Destination name is too short")
    if not (len(departure) >= 3):
        raise ValueError("Departure name is too short")
    if not (int(duration) > 20):
        raise ValueError("Duration must be a number greater than 0")

    flight = create_flights(code, duration, departure, destination)
    default_flights.append(flight)

    return default_flights

def modify_duration(default_flights, code, new_duration):
    """
    A function that modifies the duration of a flight
    :param default_flights: list of flights
    :param code: the code of the flight
    :param new_duration: the new duration of the flight
    :return: the modified list of flights
    """

    if new_duration <= 20:
        raise ValueError("Duration must be greater than 20.")

    # Normalize: codes should always be uppercase, no extra spaces
    normalized_code = code.strip().upper()

    found = False

    for f in default_flights:
        if get_code(f).strip().upper() == normalized_code:
            set_duration(f, new_duration)
            found = True
            break

    if not found:
        raise ValueError("Flight not found.")

    return default_flights



def change_destination(default_flights, initial_destination, new_destination):
    """
    A function that changes the initial destination of a flight
    :param default_flights: list of flights
    :param initial_destination: the initial destination city
    :param new_destination: the new destination city
    :return: modified list of flights
    """
    initial_destination = normalize_input(initial_destination)
    new_destination = normalize_input(new_destination)

    found = False

    if not (len(new_destination) >= 3):
        raise ValueError("Destination name is too short")
    if not (len(initial_destination) >= 3):
        raise ValueError("Destination name is too short")

    for f in default_flights:
        if normalize_input(get_destination(f)) == initial_destination:
            set_destination(f, new_destination)
            found = True
    if not found:
        raise ValueError("Destination not found.")

    return default_flights

def show_by_departure(default_list, departure):
    """
    A function that shows the flights ordered increasingly by duration
    :param default_list: list of flights
    :param departure: departure city
    :return: the flights ordered by duration
    """
    departure = normalize_input(departure)
    results = []
    for f in default_list:
        if (normalize_input(get_departure(f)) == departure):
            results.append(f)

    results = sorted(results, key=lambda f: get_duration(f))





