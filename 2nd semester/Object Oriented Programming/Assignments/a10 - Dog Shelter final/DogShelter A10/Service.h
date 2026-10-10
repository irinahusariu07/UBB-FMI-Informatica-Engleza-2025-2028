#pragma once
#include "Dog.h"
#include "Repo.h"
#include"Exceptions.h"
#include"DogValidator.h"
#include"AdoptionList.h"
#include"Action.h"
#include"ActionAdd.h"
#include"ActionRemove.h"
#include"ActionUpdate.h"
#include <string>
#include <vector>
#include <algorithm>
#include <stack>

class Service
{
private:
	Repo& repository; 
	AdoptionList* adoption_list; 
	std::stack<Action*> undoStack;
	std::stack<Action*> redoStack;

public:
	Service(Repo& repository, AdoptionList* list);
	//add a new dog - throw exception if dog already exists 
	void addDog(std::string breed, std::string name, int years, int months, std::string photo_link);
	
	//get the number of dogs in the shelter 
	int getNumberOfDogs() const;

	//remove a dog uniquely id'd by name and breed - throw exception if dog not found
	void removeDog(std::string breed, std::string name);

	//get all dogs from shelter 
	std::vector<Dog> allDogs() const { return repository.getAllDogs(); }

	//months to year if months > 12
	void monthsToYear(Age& age);

	//update a dog - throw exception if dog not found 
	void updateDog(const std::string& breed, const std::string& name, const std::string& up_breed, const std::string& up_name, const int up_years, const int up_months, const std::string& up_link); 

	
	//check string - should not be empty 
	void checkString(const std::string& text);

	//check age - should not be < 0
	void checkAge(Age age);

	//compares 2 ages - returns true if dogAge < givenAge
	bool compareAges( Age& dogAge, Age& givenAge);
	

	//filters all the dogs from a given breed wih age less than a given age 
	std::vector<Dog> filterDogBreedByAge(const std::string& breed, int years, int months);

	//the process of adopting a dog 
	void adoptDog(Dog d);

	//returning the adoption list
	std::vector<Dog> getAdoptionList() { return adoption_list->getAll(); }
	 
	//function that opens my html or cvs files 
	void openAdoptionFile() const;

	//default entries 
	void addDefaultDogs(); 

	void undo();
	void redo();
};


