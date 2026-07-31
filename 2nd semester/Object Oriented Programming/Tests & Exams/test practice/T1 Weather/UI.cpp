#include "UI.h"
#include<iostream>

UI::UI(Service& s) : s{ s }
{
}

void UI::run()
{
	while (true)
	{
		printMenu();
		int cmd = readInt("Choose: ");
		try
		{
			if (cmd == 1) //add
			{
				std::string location, name, sensors;
				std::getline(std::cin, location);
				std::cout << "\n";

				std::getline(std::cin, name);
				std::cout << "\n";

				std::getline(std::cin, sensors);
				std::cout << "\n";

				s.addStation(location, name, sensors);
				std::cout << "OK!\n";
			}

			else if (cmd == 2) //show all
			{
				Weather* all = s.listAll();
				int n = s.getSize();
				std::cout << "\n\n";
				for (int i = 0; i < n; i++)
				{
					std::cout << all[i].getLocation() << "|" << all[i].getName() << "|" << all[i].getSensors() << "\n";
				}
			}

			else if (cmd == 3) //get containing substr
			{
				std::string sensors;
				std::getline(std::cin, sensors);
				std::cout << "\n";
				DynamicVector containing = s.filterSensor(sensors);
				int n = containing.getSize();
				if (n == 0)
				{
					std::cout << "No matching\n";
					continue;
				}
				for (int i = 0; i < n; i++)
				{
					std::cout << containing.getElem(i).getLocation() << "\n";
				}
			}

			else if (cmd == 0)
			{
				break;
			}

			else std::cout << "Invalid\n";
			
		}
		catch (std::exception& e)
		{
			std::cout << "ERROR: " << e.what();
		}
	}
}

void UI::printMenu()
{
	std::cout << "1.add\n";
	std::cout << "2.all\n";
	std::cout << "3.containing\n";
	std::cout << "0.exit\n\n\n\n";
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


