#include "UI.h"



UI::UI(Service& service) :service( service )
{
}

void UI::printMenu()
{
	std::cout << "\n\nCARS\n\n";
	std::cout << "1.Add a new car\n";
	std::cout << "2.Remove a car\n";
	std::cout << "3.List all cars sorted by manufacturer and model\n";
	std::cout << "4.Vintage cars (older than 45) by color\n";
	std::cout << "0.Exit\n";
	std::cout << "\n\n\n";
}

std::string UI::toLower(const std::string& txt)
{
	std::string result = txt; 
	for (char c : result) c = std::tolower(c);
	return result;
}

std::string UI::strip(const std::string& txt)
{
	size_t start = 0; 
	while (start < txt.size() && std::isspace(txt[start])) start++;
	size_t end = txt.size() - 1; 
	while (end >= start && std::isspace(txt[end])) end--; 
	if (txt.empty()) return txt; 
	return txt.substr(start, end - start + 1); 
}

int UI::readInt(const std::string& msg)
{
	std::string input; 
	std::cout << msg;
	std::getline(std::cin, input);
	if (input.empty()) throw std::runtime_error("No input");
	for (char c : input)
		if (!std::isdigit(c)) throw std::runtime_error("Invalid number format");
	return std::stoi(input);
}

void UI::run()
{
	while (true)
	{
		printMenu();
		int cmd = readInt("Choose cmd: ");
	
		try
		{
			if (cmd == 1) //add
			{
				std::string manufacturer, model, color;
				int year;

				std::cout << "Enter manufacturer: ";
				std::getline(std::cin, manufacturer);
				manufacturer = toLower(strip(manufacturer));
				std::cout << "\n";

				std::cout << "Enter model: ";
				std::getline(std::cin, model);
				model = toLower(strip(model));
				std::cout << "\n";

				year = readInt("Enter fabrication year: ");
				std::cout << "\n";

				std::cout << "Enter color: ";
				std::getline(std::cin, color);
				color = toLower(strip(color));
				std::cout << "\n";

				service.addCar(manufacturer, model, year, color);
				std::cout << "Car added!";
			}

			else if (cmd == 2) //remove
			{
				std::string model;
				int year;
				std::cout << "Enter model: ";
				std::getline(std::cin, model);
				model = toLower(strip(model));
				std::cout << "\n";

				year = readInt("Enter fabrication year: ");
				std::cout << "\n";

				service.removeCar(model, year);
			}

			else if (cmd == 3) //list ordered 
			{
				service.sortCars();
				Car* cars = service.allCars();

				int size = service.numberOfCars();
				std::cout << "MANUFACTURER | MODEL | YEAR | COLOR ";
				std::cout << "\n";
				for (int i = 0; i < size; i++)
				{

					std::cout << cars[i].getManufacturer() << " | " << cars[i].getModel() << "| " <<
						cars[i].getYear() << " | " << cars[i].getColor() << "\n";
				}

			}

			else if (cmd == 4) //filter 45 years or older
			{
				std::vector<Car> result = service.filter();
				int n = result.size();
				for (int i = 0; i < n; i++)
					std::cout << result[i].getManufacturer() << " | " << result[i].getModel() << "| " <<
					result[i].getYear() << " | " << result[i].getColor() << "\n";
			}

			else if (cmd == 0)
			{
				std::cout << "exiting";
				break;
			}

			else std::cout << "unknown command!";
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: " << e.what();
		}
	}
}
