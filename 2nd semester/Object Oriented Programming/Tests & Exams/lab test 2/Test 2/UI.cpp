#include "UI.h"

void UI::run()
{
	while (true)
	{
		std::cout << "1. Add\n 2.All\n3.Write to file \n"; 
		try {
			std::cout << "Cmd: "; 
			std::string input; 
			int cmd; 
			std::getline(std::cin, input); 
			cmd = std::stoi(input); 

			if (cmd == 0) break; 
			else if (cmd == 1)
			{
				std::string type; 
				std::cout << "\nType: ";
				std::getline(std::cin, type);
				std::string county, name; 
				std::cout << "\nCounty: "; 
				std::getline(std::cin, county); 
				if (type == "party")
				{
					std::cout << "\nname:";
					std::getline(std::cin, name); 
					std::cout << "\nvotes: ";
					std::getline(std::cin, input); 
					int votes = std::stoi(input);
					County* c = new Party(county, name, votes);
					s.addCounty(c);
				}
				else if (type == "alliance")
				{
					std::cout << "\nname:";
					std::getline(std::cin, name);
					std::cout << "\nvotes: ";
					std::getline(std::cin, input);
					int votes = std::stoi(input);
					std::cout << "\n numbers: ";
					std::getline(std::cin, input);
					int numbers = std::stoi(input); 
					
					County* c = new Alliance(county, name, votes, numbers);
					s.addCounty(c);
				}

				else if (type == "independent")
				{
					std::cout << "\nname:";
					std::getline(std::cin, name);
					std::cout << "\nvotes: ";
					std::getline(std::cin, input);
					int votes = std::stoi(input);
					County* c = new Independent(county, name, votes);
					s.addCounty(c); 
				}
			}
			else if (cmd == 2)
			{
				std::vector<County*> all = s.getAll(); 
				for (auto c : all) std::cout << c->toString(); 
			}
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << "\n"; 
		}
	}
}
