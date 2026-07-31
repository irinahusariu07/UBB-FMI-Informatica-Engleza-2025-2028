#include "Repo.h"

void Repo::readFromFile()
{
	std::ifstream file(filename);
	if (!file.is_open()) throw std::runtime_error("Star file corrupted!");
	stars.clear();
	std::string line; 
	while (std::getline(file, line))
	{
		if (line.empty()) continue; 
		std::stringstream ss(line);
		std::string name, constel, ras, decs, diams; 
		std::getline(ss, name, '|');
		std::getline(ss, constel, '|');
		std::getline(ss, ras, '|');
		int ra = std::stoi(ras);
		std::getline(ss, decs, '|');
		int dec = std::stoi(decs);
		std::getline(ss, diams, '|');
		int diam = std::stoi(diams);
		Star s(name, constel, ra, dec, diam);
		stars.push_back(s);
	}
	file.close();
}

void Repo::writeToFile()
{
	std::fstream file(filename);
	for (auto& s : stars)
	{
		file << s.getName() << "|" << s.getConstellation() << "|" << s.getRA() << "|" << s.getDec() << "|" << s.getDiam() <<"\n";
	}
	file.close();
}


