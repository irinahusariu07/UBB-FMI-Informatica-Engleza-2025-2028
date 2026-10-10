#include "Dog.h"

//default constructor Age()
/*
Age::Age()
{
	this->months = 0;
	this->years = 0; 
}
*/

Age::Age(int years, int months)
{
	this->months = months; 
	this->years = years;
}

Dog::Dog(const std::string& breed, const std::string& name, int years, int months, const std::string& photo_link)
{
	this->breed = breed; 
	this->name = name; 
	Age age{ years, months };
	this->age = age;
	this->photo_link = photo_link;
}

std::ostream& operator<<(std::ostream& out, const Dog& d)
{
	out << d.getBreed() << '|' << d.getName() << '|' << d.age.getYears() << '|' << d.age.getMonths() << '|' << d.getLink();
	return out; 
}
std::istream& operator>>(std::istream& in, Dog& d)
{
	std::string line;
	if (std::getline(in, line)) 

	{
		if (line.empty()) return in;

		std::stringstream ss(line);
		std::string breed, name, link, years_str, months_str;
		std::getline(ss, breed, '|');
		std::getline(ss, name, '|');
		std::getline(ss, years_str, '|');
		std::getline(ss, months_str, '|');
		std::getline(ss, link, '|');

		if (!breed.empty() && !name.empty() && !years_str.empty() && !months_str.empty() && !link.empty())
		{
			d = Dog(breed, name, std::stoi(years_str), std::stoi(months_str), link);
		}
	}
	return in; 
}

