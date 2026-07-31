#include "Repo.h"

void Repo::readBiologistFile()
{
	std::ifstream file(bio_file);
	if (!file.is_open()) throw std::runtime_error("Biologist file corrupted"); 

	biologists.clear(); 
	std::string line; 

	while (std::getline(file, line))
	{
		if (line.empty()) continue; 
		std::stringstream ss(line);
		std::string name, species; 
		std::getline(ss, name, '|'); 
		std::getline(ss, species, '|'); 

		std::stringstream sp(species); 
		std::vector<std::string> list; 
		std::string segment; 

		while (std::getline(sp, segment, ';'))
		{
			if (segment.empty()) continue; 
			list.push_back(segment);
		}
		Biologist b{ name, list }; 
		biologists.push_back(b); 
	}
	file.close(); 
}

void Repo::readBacteriaFile()
{
	std::ifstream file(bac_file);
	if (!file.is_open()) throw std::runtime_error("Bacteria file corrupted"); 

	bacteries.clear(); 
	std::string line; 

	while (std::getline(file, line))
	{
		if (line.empty()) continue; 
		std::stringstream ss(line); 
		std::string name, spec, size, diseases; 

		std::getline(ss, name, '|'); 
		std::getline(ss, spec, '|'); 
		std::getline(ss, size, '|'); 
		std::getline(ss, diseases, '|'); 

		std::stringstream ds(diseases); 
		std::vector<std::string> dis; 
		std::string segment; 

		while (std::getline(ds, segment, ';'))
		{
			if (segment.empty()) continue; 
			dis.push_back(segment);
		}
		Bacteria b{ name, spec, std::stoi(size), dis }; 
		bacteries.push_back(b); 
	}
	file.close(); 
}

void Repo::writeBacteriesFile()
{
	std::ofstream file(this->bac_file); 
	for (auto& b : bacteries)
	{
		file << b.getName() << "|" << b.getSpecies() << "|" << b.getSize() << "|";
		for (int i = 0; i < b.getDiseases().size(); i++)
		{
			file << b.getDiseases()[i]; 
			if (i < b.getDiseases().size() - 1) file << ";";
		}
		file << "\n";
	}
	file.close();
}

void Repo::addBacteria(Bacteria& b)
{
	bacteries.push_back(b); 
	writeBacteriesFile(); 
}

void Repo::addDisease(const std::string& name, const std::string& spec, const std::string& disease)
{
	bool found = false;
	for (auto& b : getBacteria())
	{
		if (b.getName() == name && b.getSpecies() == spec) {
			b.addDisease(disease);
			found = true;
		}
	}
	if (!found) throw std::runtime_error("Doesnt exist");
	else writeBacteriesFile();
}
