#include "UI.h"

void UI::printMenu()
{
	std::cout << "1. Add a new analysis \n";
	std::cout << "2. Show all \n";
	std::cout << "3. Show if person is ill \n";
	std::cout << "4. Save to file analyses between 2 dates \n";
	std::cout << "0. exit \n";
	std::cout << "\n\n";
}

void UI::run()
{
	printMenu(); 
	while (true)
	{
		try
		{
			std::string input;
			std::cout << "Choose cmd: ";
			std::getline(std::cin, input); 
			int cmd = std::stoi(input); 

			if (cmd == 0) break;
			else if (cmd == 1) //add
			{
				std::string type, date;
				std::cout << "Choose type: ";
				std::getline(std::cin, type);
				std::cout << "\n";

				std::cout << "Date: ";
				std::getline(std::cin, date);
				std::cout << "\n";

				if (type == "bmi")
				{
					int value;
					std::cout << "Input value of BMI: ";
					std::getline(std::cin, input); 
					value = std::stoi(input); 
					std::cout << "\n";
					MedicalAnalysis* a = new BMI(date, value);
					p.addAnalysis(a);
					std::cout << "Added successfully! \n\n";
				}

				else if (type == "bp")
				{
					double val1, val2;

					std::cout << "Input systolic of BP: ";
					std::getline(std::cin, input); 
					val1 = std::stod(input); 
					std::cout << "\n";

					std::cout << "Input diastolic of BP: ";
					std::getline(std::cin, input);
					val2 = std::stod(input);
					std::cout << "\n";

					MedicalAnalysis* a = new BP(date, val1, val2);
					p.addAnalysis(a);
					std::cout << "Added successfully! \n\n";
				}
			}
			else if (cmd == 2)
			{
				std::vector<MedicalAnalysis*> all = p.getAllAnalyses();
				for (auto a : all) std::cout << a->toString();
				std::cout << "\n";
			}

			else if (cmd == 3)
			{
				std::cout << "\nInput month: ";
				std::getline(std::cin, input);
				int month = std::stoi(input);
				if (p.isIll(month)) std::cout << "\nIll\n";
				else std::cout << "\n NOT Ill\n";
			}

			else if (cmd == 4)
			{
				std::string date1, date2;

				std::cout << "\nInput date1 : ";
				std::getline(std::cin, date1);

				std::cout << "\nInput date2 : ";
				std::getline(std::cin, date2);

				p.writeToFile("analyses.txt", date1, date2);
				std::cout << "\n Written!\n";
			}

			else std::cout << "Unknown\n"; 
		}
		catch (std::exception& e)
		{
			std::cout << "\nError: " << e.what() << "\n"; 
		}
	}
}