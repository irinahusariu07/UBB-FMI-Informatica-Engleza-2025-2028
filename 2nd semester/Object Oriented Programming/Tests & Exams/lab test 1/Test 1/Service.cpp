#include "Service.h"


Service::Service(Repo& repository) : repository {repository}
{
}

void Service::addProtein(const std::string& organism, const std::string& name, const std::string& sequence)
{
	Protein protein{ organism, name, sequence };
	if (organism == "" || name == "" || sequence == "") throw std::runtime_error("Fields are empty");

	if (repository.findID(organism, name) != -1) throw std::runtime_error("Protein already exists");
	repository.addDB(protein);
}

void Service::addDefault()
{
	addProtein("human", "myosin2", "sdms");
	addProtein("human", "keratin", "tcgs");
	addProtein("mouse", "keratin", "dvqk");
	addProtein("ecoli", "tufa", "vtle");
	addProtein("ecoli", "cspe", "ms");
}

Protein* Service::listAll()
{
	return repository.getAll();
}

bool compare(Protein p1, Protein p2)
{
	return p1.getOrganism() > p2.getOrganism();
}
std::vector<Protein> Service::getNameSorted(const std::string& name)
{
	int n = repository.getSize();
	Protein* all = repository.getAll();
	std::vector<Protein> result;
	for (int i = 0; i < n; i++)
	{
		if (all[i].getName() == name) result.push_back(all[i]);
	}

	int size = result.size();
	std::sort(result.begin(), result.end(), compare);
	return result;
}





