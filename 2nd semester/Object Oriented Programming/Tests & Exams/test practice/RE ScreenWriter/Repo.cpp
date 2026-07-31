#include "Repo.h"

void Repo::readWriterFile()
{
	std::ifstream file(this->wrfile);
	if (!file.is_open()) throw std::runtime_error("Writer file corrupted");

	writers.clear();
	std::string line; 
	while (std::getline(file, line))
	{
		if (line.empty()) continue; 

		std::stringstream ss(line);
		std::string name, exp; 
		std::getline(ss, name, '|');
		std::getline(ss, exp, '|');

		Writer w(name, exp);
		writers.push_back(w);
	}
	file.close();
}


void Repo::readIdeaFile()
{
	std::ifstream file(this->idfile);
	if (!file.is_open()) throw std::runtime_error("Idea file corrupted");

	ideas.clear();
	std::string line; 
	while (std::getline(file, line))
	{
		if (line.empty()) continue;
		std::stringstream ss(line);
		std::string desc, stat, creator, acts; 
		std::getline(ss, desc, '|');
		std::getline(ss, stat, '|');
		std::getline(ss, creator, '|');
		std::getline(ss, acts, '|');

		Idea i(desc, stat, creator, std::stoi(acts));
		ideas.push_back(i);
	}
	file.close();
}

void Repo::writeIdeaFile()
{
	std::ofstream file(this->idfile);
	
	if (!file.is_open()) throw std::runtime_error("Cannot open file for writing"); 
	for (auto& i : ideas)
	{
		file << i.getDesc() << "|" << i.getStatus() << "|" << i.getCreator() << "|" << i.getAct() << "\n";
	}
	file.close();
}

void Repo::addIdea(Idea& i)
{
	ideas.push_back(i);
	writeIdeaFile(); 
}

void Repo::acceptIdea(const std::string& desc, int act)
{
	bool chg = false; 
	for (auto& i : ideas)
	{
		if (i.getAct() == act && i.getDesc() == desc)
		{
			if (i.getStatus() == "accepted") throw std::runtime_error("Idea already accepted");
			else
			{
				i.setStatus("accepted");
			}
			chg = true;
		}
	}
	if (!chg) throw std::runtime_error("Not found");
	writeIdeaFile();
}

