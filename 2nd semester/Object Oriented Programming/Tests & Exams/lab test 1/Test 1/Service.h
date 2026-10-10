#pragma once
#include<stdexcept>
#include<algorithm>
#include"Repo.h"
#include"DynamicVector.h"
#include"Protein.h"
#include<vector>

class Service
{
private:
	Repo& repository;
public:
	Service(Repo& repository);
	//adds a protein to the list - protein given by name organism and sequence 
	void addProtein(const std::string& organism, const std::string& name, const std::string& sequence);
	void addDefault();
	int getSize() { return repository.getSize(); }
	Protein* listAll();

	//shows all proteins sorted by organism with a given name
	std::vector<Protein> getNameSorted(const std::string& name);
};