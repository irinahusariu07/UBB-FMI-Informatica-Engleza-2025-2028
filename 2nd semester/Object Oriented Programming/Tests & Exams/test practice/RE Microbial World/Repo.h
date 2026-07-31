#pragma once
#include"Biologist.h"
#include"Bacteria.h"
#include<sstream>
#include<fstream>

class Repo
{
private:
	std::string bio_file, bac_file; 
	std::vector<Bacteria> bacteries; 
	std::vector<Biologist> biologists; 

public:
	Repo(const std::string& bio, const std::string& bac) : bio_file{ bio }, bac_file{ bac } { this->readBiologistFile(); this->readBacteriaFile(); }
	void readBiologistFile();
	void readBacteriaFile(); 
	void writeBacteriesFile(); 
	
	void addBacteria(Bacteria& b);
	std::vector<Biologist>& getBiologists() { return biologists; }
	std::vector<Bacteria>& getBacteria() { return bacteries; }
	void addDisease(const std::string& name, const std::string& spec, const std::string& disease);

};

