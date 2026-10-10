#pragma once
#include"DynamicVector.h"
#include"Protein.h"
#include<string>

class Repo
{
private:

	DynamicVector dataBase;
public:

	void addDB(Protein& protein);
	Protein* getAll();
	int getSize() { return dataBase.getSize(); }
	//int findProtein(int id);
	int findID(const std::string& organism, const std::string& name);

};

