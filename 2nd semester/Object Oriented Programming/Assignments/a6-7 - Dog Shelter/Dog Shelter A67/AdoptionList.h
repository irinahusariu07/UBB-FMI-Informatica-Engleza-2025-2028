#pragma once
#include <vector>
#include <string>
#include "Dog.h"

class AdoptionList
{
protected:
	std::vector<Dog> adopted_dogs; 
	std::string filename; 
public:
	AdoptionList(const std::string& filename) : filename{ filename }
	{
	}
	virtual ~AdoptionList() {}
	void add(Dog& d) { adopted_dogs.push_back(d); }
	std::vector<Dog> getAll() const { return this->adopted_dogs;}
	virtual void writeToFile() = 0; 
	std::string getFilename() const { return this->filename; }
};

