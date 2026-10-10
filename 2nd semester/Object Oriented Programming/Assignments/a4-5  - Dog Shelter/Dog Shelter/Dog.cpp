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



