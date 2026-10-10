#include "UI.h"
#include <cstring>
#include <string>

UI::UI(Service& service): service { service }
{
}

std::string UI::toLower(const std::string& text)
{
	std::string result = text;
	for (char& c : result) c = std::tolower(c);
	return result; 
}


std::string UI::strip(const std::string& text)
{
	if (text.empty()) return text; 

	size_t start = 0;
	while (start < text.size() && std::isspace(text[start])) start++;

	//if the string was only spaces (start moved until the end) it returns "" 
	if (start == text.size()) return "";

	size_t end = text.size() - 1;
	while (end > start && std::isspace(text[end])) end--;

	return text.substr(start, end - start + 1);
}

int UI::readInt(const std::string& message)
{
	std::string input;

	std::cout << message;
	std::getline(std::cin, input);

	if (input.empty())
		throw ValidationException("Input cannot be empty!");

	for (char c : input)
	{
		if (!std::isdigit(c))
			throw ValidationException("Invalid input!");
	}

	return std::stoi(input);
}

void UI::run()
{
	std::cout << "\033[36m    --- KEEP CALM AND ADOPT A PET ---\033[0m\n";
	std::cout << "\nWelcome to our shelter! Choose mode: \n";
	while (true)
	{
		std::cout << "\n\n";
		std::cout << "1. Admin mode" << "\n";
		std::cout << "2. User mode" << "\n";
		std::cout << "0. Exit" << "\n";
		try 
		{
			int cmd = readInt("\nChoose mode: ");
			std::cout << "\n";

			if (cmd == 0)
			{
				std::cout << "Have a nice day!";
				break;
			}
			else if (cmd == 1)
			{
				std::cout << "Entering admin mode!\n";
				menuAdmin();
			}
			else if (cmd == 2)
			{
				std::cout << "Entering user mode!\n";
				menuUser();
			}
			else
			{
				std::cout << "Invalid command. Try again!\n";
			}
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: " << e.what() << "\n";
		}
	}
}
void UI::printMiniMenu()
{
	std::cout << "\n\n";
	std::cout << "				1. Show photo\n";
	std::cout << "				2. Adopt\n"; 
	std::cout << "				3. Next\n";
	std::cout << "				4. Previous\n";
	std::cout << "				0. Back to user menu\n";
	std::cout << "\n\n";
}

void UI::browseDogs(std::vector<Dog> dogs)
{
	int current = 0; 
	int size = dogs.size();
	if (size == 0)
	{
		std::cout << "No dogs matching that citeria!\n";
		std::cout << "\n\n";
		return;
	}
	while (true)
	{
		try
		{
			Dog d = dogs[current];
			std::cout << "Dog " << current + 1 << " out of " << size << "\n";
			std::cout << "\033[36mBreed: " << d.getBreed() << "\033[0m\n";
			std::cout << "\033[36mName: " << d.getName() << "\033[0m\n";
			std::cout << "\033[36mAge: " << d.getAge().getYears() << " years " << d.getAge().getMonths() << " months \033[0m\n"; 

			printMiniMenu();

			int cmd = readInt("Choose action: ");
			if (cmd == 1)
			{
				std::string command = "start " + d.getLink();
				system(command.c_str());
			}

			else if (cmd == 2) //adopt
			{
				service.adoptDog(d); //adopt it
				dogs.erase(dogs.begin() + current); //remove it from the listing 
				int new_size = dogs.size();
				if (new_size == 0)
				{
					std::cout << "You adopted the last available dog!\n";
					return;
				}
				if (current >= new_size) current = 0; //move it back to beginning if it exceeds the current boundary
				std::cout << "Congrats! Dog was adopted! \n\n\n";
				size = new_size;
			}

			else if (cmd == 3) //next
			{
				current = (current + 1) % size;
			}
			else if (cmd == 4) //previous
			{
				current = (current - 1 + size) % size;
			}
			else if (cmd == 0) //return to user menu 
			{
				return;
			}
			else std::cout << "Unknown command!\n\n";
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << "\n";
		}
	}
}

void UI::menuUser()
{
	std::cout << "\033[34m- USER MODE -\n\033[0m";
	while (true)
	{
		std::cout << "\n\n";
		std::cout << "1. See all dogs\n";
		std::cout << "2. See dogs of a certain breed with age less than given age\n";
		std::cout << "3. Show adoption list\n";
		std::cout << "0. Exit user mode! Return to main menu!\n";
		try
		{
			int cmd = readInt("\nChoose command: ");
			std::cout << "\n";

			if (cmd == 0) return;
			else if (cmd == 1) //show all dogs; 
			{
				std::vector<Dog> all = service.allDogs();
				browseDogs(all);
			}


			else if (cmd == 2) //show dogs with given breed filtered by age less than given age
			{
				std::string breed;
				int years, months;
				std::cout << "Enter breed: ";
				std::getline(std::cin, breed);
				breed = toLower(breed);
				breed = strip(breed);
				std::cout << "\n";

				years = readInt("Enter age - Years: ");
				months = readInt("Enter age - Months: ");
				Age givenAge{ years, months };
				service.monthsToYear(givenAge);

				std::vector<Dog> filtered = service.filterDogBreedByAge(breed, givenAge.getYears(), givenAge.getMonths());
				browseDogs(filtered);
			}

			else if (cmd == 3)
			{
				std::cout << "Your adoption list: \n";
				std::vector<Dog> adoptions = this->service.getAdoptionList();
				if (adoptions.size() == 0)
				{
					std::cout << "Your adoption list is empty! \n\n";
					//return;
				}
				
				std::cout << "Breed | Name | Years | Months\n";
				//int size = adoptions.size();
				for (auto& a : adoptions)
				{
					std::cout << a.getBreed() << " | " << a.getName() << " | " <<a.getAge().getYears() << " | " <<
						a.getAge().getMonths();
					std::cout << "\n";
				}

				//open also the html or csv 
				std::cout << "Opening the adoption list in your desired format... \n";
				service.openAdoptionFile();
				break;

			}

			else if (cmd == 0) return;
			else std::cout << "Invalid command!\n";
		}
		catch(const std::exception& e)
		{
			std::cout << "Error: " << e.what() << "\n";
		}
	}
}

void UI::menuAdmin()
{
	std::cout << "\033[34m- ADMIN MODE - \n\033[0m";
	while (true)
	{
		std::cout << "\n\n";
		std::cout << "1. Add a dog \n";
		std::cout << "2. Remove a dog\n";
		std::cout << "3. Update a dog's details\n";
		std::cout << "4. List all dogs in the shelter\n";
		std::cout << "0. Exit admin mode! Return to main menu!\n";
		int cmd = readInt("\nChoose command: ");
		std::cout << "\n";


		try
		{
			if (cmd == 1) //add a new dog
			{
				std::cout << "Add a new dog!\n";
				std::string breed, name, link;
				int years, months;

				std::cout << "Breed: ";
				std::getline(std::cin, breed);
				breed=toLower(breed);
				breed=strip(breed);
				std::cout << "\n";

				std::cout << "Name: ";
				std::getline(std::cin, name);
				name=toLower(name);
				name=strip(name);
				std::cout << "\n";

				std::cout << "Age: \n";
				years = readInt("Years: ");
				std::cout << "\n";
				months = readInt("Months: ");
				std::cout << "\n";

				std::cout << "Link to photo: ";
				std::getline(std::cin, link);
				link=toLower(link);
				link=strip(link);
				std::cout << "\n";

				service.addDog(breed, name, years, months, link);
				std::cout << "Dog added successfully!";
				std::cout << "\n";
				std::cout << "\n";
				std::cout << "\n";
			}


			else if (cmd == 2) //remove a dog
			{
				std::cout << "Remove a dog!\n";
				std::string breed, name;
				std::cout << "A dog is uniquely given by breed and name \n";

				std::cout << "Breed: ";
				std::getline(std::cin, breed);
				breed=toLower(breed);
				breed=strip(breed);
				std::cout << "\n";

				std::cout << "Name: ";
				std::getline(std::cin, name);
				name=toLower(name);
				name=strip(name);
				std::cout << "\n";

				service.removeDog(breed, name);
				std::cout << "Dog removed successfully!";
				std::cout << "\n";
				std::cout << "\n";
				std::cout << "\n";
			}

			else if (cmd == 3) //update a dog
			{
				std::cout << "Update a dog's details!\n";
				std::string unique_breed, unique_name, breed, name, link;
				int years, months;

				std::cout << "A dog is uniquely given by breed and name \n";

				std::cout << "Breed of the dog you want to update: ";
				std::getline(std::cin, unique_breed);
				unique_breed = toLower(unique_breed);
				unique_breed = strip(unique_breed);
				std::cout << "\n";

				std::cout << "Name of the dog you want to update: ";
				std::getline(std::cin, unique_name);
				unique_name = toLower(unique_name);
				unique_name = strip(unique_name);
				std::cout << "\n";

				std::cout << "Updated breed: ";
				std::getline(std::cin, breed);
				breed = toLower(breed);
				breed = strip(breed);
				std::cout << "\n";

				std::cout << "Updated name: ";
				std::getline(std::cin, name);
				name = toLower(name);
				name = strip(name);
				std::cout << "\n";

				std::cout << "Updated age: \n";
				years = readInt("Years: ");
				std::cout << "\n";
				months = readInt("Months: ");
				std::cout << "\n";

				std::cout << "Updated link to photo: ";
				std::getline(std::cin, link);
				link = toLower(link);
				link = strip(link);
				std::cout << "\n";

				service.updateDog(unique_breed, unique_name, breed, name, years, months, link);
				std::cout << "Dog updated successfully!";
				std::cout << "\n";
				std::cout << "\n"; 
				std::cout << "\n";
			}

			else if (cmd == 4) //list all dogs 
			{
				std::vector<Dog> dogs = service.allDogs();
				int size = service.getNumberOfDogs();
				std::cout << "Breed | Name | Years | Months | Photo link\n";
				std::cout << "\n";
				for (auto& d  : dogs)
				{
					std::cout << d.getBreed() << " | " << d.getName() << " | " << d.getAge().getYears() << " | " <<
						d.getAge().getMonths() << " | " << d.getLink();
					std::cout << "\n";
				}
				std::cout << "\n";
				std::cout << "\n";
				std::cout << "\n";
			}

			else if (cmd == 0) //back
			{
				return;
			}

			else std::cout << "Invalid command!\n";
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: " << e.what() << "\n";
		}
	}
}



