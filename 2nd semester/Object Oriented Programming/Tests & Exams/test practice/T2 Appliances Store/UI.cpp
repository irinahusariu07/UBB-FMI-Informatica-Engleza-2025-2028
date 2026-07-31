#include "UI.h"
#include <iostream>

void UI::printMenu()
{
	std::cout << "1. Add\n";
	std::cout << "2. All\n";
	std::cout << "3. Show inefficient \n";
	std::cout << "4. Write to file sorted < value \n";
	std::cout << "\n\n";
}

void UI::run()
{
	while (true)
	{
		printMenu();
		try {
			std::string input;
			std::cout << "\n> ";
			std::getline(std::cin, input); 
			int cmd = std::stoi(input); 

			if (cmd == 0) break; 
			else if (cmd == 1) //add
			{
				std::string id, usageClass, type; 
				std::cout << "\nWhat appliance? >";
				std::getline(std::cin, type); 

				std::cout << "\nID: "; 
				std::getline(std::cin, id);

				if (type == "refrigerator")
				{
					std::cout << "\nUsage Class(a or a++): ";
					std::getline(std::cin, usageClass);

					std::string freezer;
					bool val; 
					std::cout << "\nHas freezer? y/n? > ";
					std::getline(std::cin, freezer); 
					if (freezer == "y") val = true;
					else val = false; 

					Appliance* a = new Refrigerator(id, usageClass, val);
					s.addAppliance(a); 
				}
				else
				{
					double consumedHour; 
					std::cout << "\nConsumes per hour: "; 
					std::getline(std::cin, input); 
					consumedHour = std::stod(input);
					Appliance* a = new DishWasher(id, consumedHour);
					s.addAppliance(a);
				}
				
			}

			else if (cmd == 2)//show all
			{
				std::vector<Appliance*> all = s.getAllAppliances(); 
				for (auto a : all) std::cout << a->toString() << "\n";
			}

			else if (cmd == 3) //show faulty
			{
				std::vector < Appliance*> faulty = s.getAllWithCEnergyLessThan(100);
				for (auto a : faulty) std::cout << a->toString() << "\n";
			}

			else if (cmd == 4) //write to file
			{
				std::getline(std::cin, input);
				double value = std::stod(input);
				s.writeToFile("appliances.txt", value);
			}
		}
		catch (std::exception& e)
		{
			std::cout << "\nError: " << e.what() << "\n";
		}
	}
}