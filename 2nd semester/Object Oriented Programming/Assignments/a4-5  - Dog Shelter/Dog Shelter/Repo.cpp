#include "Repo.h"

void Repo::addDB(const Dog& dog)
{
	this->dogDataBase.add(dog);
}

int Repo::getDBSize() const
{
	return this->dogDataBase.getSize();
}

void Repo::removeDB(const int dog_id)
{
	this->dogDataBase.remove(dog_id); 
}

int Repo::findDog(const std::string& breed, const std::string& name)
{
	for (int i = 0; i < getDBSize(); i++)
	{
		if (findID(i).getBreed() == breed && findID(i).getName() == name) //found the dog
			return i; 
	}
	return -1; 
}

void Repo::updateDB(const std::string& breed, const std::string& name, const Dog& new_dog)
{
	int id = findDog(breed, name); 
	if (id != -1) dogDataBase.getElem(id) = new_dog; 
}

