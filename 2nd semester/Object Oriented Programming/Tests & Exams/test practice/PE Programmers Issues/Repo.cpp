#include "Repo.h"

void Repo::readFromIssueFile()
{
	std::ifstream file(this->issue_file);
	if (!file.is_open()) throw std::runtime_error("Issue file corrupted");
	issues.clear();
	std::string line; 
	while (std::getline(file, line))
	{
		if (line.empty()) continue; 
		std::stringstream ss(line);
		std::string description, type, reporter, solver; 
		std::getline(ss, description, '|');
		std::getline(ss, type, '|');
		std::getline(ss, reporter, '|');
		std::getline(ss, solver, '|');
		Issue i{ description, type, reporter, solver };
		issues.push_back(i);
	}
	file.close();
}


void Repo::writeToIssueFile()
{
	std::ofstream file(this->issue_file);
	if (!file.is_open()) throw std::runtime_error("Cannot write to issue file!");
	for (auto& i : issues)
	{
		file << i.getDescription() << "|" << i.getType() << "|" << i.getReporter() << "|" << i.getSolver() <<"\n";
	}
	file.close(); 
}

void Repo::updateIssue(const std::string& desc, const std::string& new_type, const std::string& new_solver)
{
	bool changed = false;
	for (auto& i : issues)
	{
		if (i.getDescription() == desc)
		{
			i.setType(new_type);
			i.setSolver(new_solver);
			changed = true;
			writeToIssueFile();
			return;
		}
	}
	if (changed == false) throw std::runtime_error("No issue matches description");
}

void Repo::removeIssue(const std::string& desc)
{
	int idx = -1; 
	for (int i = 0; i < issues.size(); i++)
	{
		if (issues[i].getDescription() == desc) {
			idx = i;
			break;
		}
	}
	if (idx != -1)
	{
		issues.erase(issues.begin() + idx);
		writeToIssueFile();
	}
	else throw std::runtime_error("No issue with matching description!");
}


