#include "UI.h"
#include <iostream>

UI::UI(Service& service) : service{ service }
{
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

void UI::printMenu()
{
	std::cout << "\n\n";
	std::cout << "1. Add protein \n";
	std::cout << "2. All\n";
	std::cout << "3. All with a name sorted by organism \n";
	std::cout << "4. Show proteins with name containing string\n";
	std::cout << "\n\n\n";
}

void UI::run()
{
	std::cout << "---Protein Manager --- \n\n\n";
	while (true)
	{
		printMenu();
		try
		{
			int cmd = readInt("Choose ");

			if (cmd == 0) break;
			else if (cmd == 1) //add
			{
				std::string organism, name, sequence;
				std::cout << "Organism: ";
				std::getline(std::cin, organism);
				std::cout << "\n";

				std::cout << "Name: ";
				std::getline(std::cin, name);
				std::cout << "\n";

				std::cout << "Sequence: ";
				std::getline(std::cin, sequence);
				std::cout << "\n";

				service.addProtein(organism, name, sequence);
				std::cout << "Added!\n";

			}

			else if (cmd == 2) //all
			{
				int n = service.getSize();
				Protein* all = service.listAll();
				std::cout << "ORGANISM | NAME | SEQUENCE \n";
				for (int i = 0; i < n; i++)
				{
					std::cout << all[i].getOrganism() << " | " << all[i].getName() << " | " << all[i].getSequence() << "\n";
				}
			}

			else if (cmd == 3) //sorted
			{
				std::string name; 
				std::cout << "Name: ";
				std::getline(std::cin, name);
				std::cout << "\n";

				std::vector<Protein> all = service.getNameSorted(name);
				for (int i = 0; i < all.size(); i++)
				{
					std::cout << all[i].getOrganism() << " | " << all[i].getName() << " | " << all[i].getSequence() << "\n";
				}
			}
		}

		catch (std::exception& e)
		{
			std::cout << "ERROR: " << e.what();
		}
	}
}


