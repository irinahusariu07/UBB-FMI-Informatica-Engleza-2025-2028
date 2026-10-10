#include "Repo.h"

Repo::Repo(const std::string& filename) : filename{ filename }
{
	this->loadFromFile();
}

void Repo::loadFromFile()
{
	std::ifstream file(this->filename);
	if (!file.is_open()) return;

	Dog d; 
	while (file >> d)
	{
		this->dogDataBase.push_back(d);
	}
	file.close();
}

void Repo::saveToFile()
{
	std::ofstream file(this->filename);
	if (!file.is_open()) return;

	for (auto& d : dogDataBase) file << d << "\n";
	file.close();
}

void Repo::addDB(const Dog& dog)
{
	this->dogDataBase.push_back(dog);
	this->saveToFile();
}

int Repo::getDBSize() const
{
	return this->dogDataBase.size();
}

void Repo::removeDB(const int dog_id)
{
	this->dogDataBase.erase(dogDataBase.begin() + dog_id); 
	this->saveToFile();
}

int Repo::findDog(const std::string& breed, const std::string& name)
{
	auto it = std::find_if(dogDataBase.begin(), dogDataBase.end(), [&](const Dog& d)
		{
			return d.getBreed() == breed && d.getName() == name;
		});
	//check if the dog was found => we re not at the end of the DB 
	if (it != dogDataBase.end()) return std::distance(dogDataBase.begin(), it); 
	return -1; 
}

void Repo::updateDB(const std::string& breed, const std::string& name, const Dog& new_dog)
{
	int id = findDog(breed, name); 
	if (id != -1) dogDataBase[id] = new_dog;
	this->saveToFile();
}

