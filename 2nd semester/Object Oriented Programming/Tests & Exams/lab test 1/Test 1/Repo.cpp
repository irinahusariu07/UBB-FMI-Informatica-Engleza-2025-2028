#include "Repo.h"

void Repo::addDB(Protein& protein)
{
	dataBase.add(protein);
}

Protein* Repo::getAll()
{
	return dataBase.getAll();
}

int Repo::findID(const std::string& organism, const std::string& name)
{
	Protein* all = dataBase.getAll();
	for (int i = 0; i < dataBase.getSize(); i++)
	{
		if (all[i].getOrganism() == organism && all[i].getName() == name)
			return i; 
	}
	return -1; 
}



