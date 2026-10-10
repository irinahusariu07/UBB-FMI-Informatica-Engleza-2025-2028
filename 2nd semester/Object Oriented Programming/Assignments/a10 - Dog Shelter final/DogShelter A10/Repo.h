#pragma once
#include"Dog.h"
#include"Exceptions.h"
#include"DogValidator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Repo
{
private:
	std::vector<Dog> dogDataBase;
	std::string filename; 

	void loadFromFile();
	

public:
	void saveToFile();
	//default constructor
	Repo(const std::string& filename);

	//add a dog to the database
	void addDB(const Dog& dog); 

	//get the number of dogs in the database 
	int getDBSize() const; 

	//delete a dog from the database
	void removeDB(const int dog_id);

	//returns the id of a dog - uniquely given by breed + name 
	int findDog(const std::string& breed, const std::string& name);

	//get the dog by id
	Dog findID(int dog_id) { return dogDataBase[dog_id]; }

	//get all dogs
	std::vector<Dog> getAllDogs() { return dogDataBase; }

	//update a dog obj with a new dog obj
	void updateDB(const std::string& breed, const std::string& name, const Dog& new_dog);

};


