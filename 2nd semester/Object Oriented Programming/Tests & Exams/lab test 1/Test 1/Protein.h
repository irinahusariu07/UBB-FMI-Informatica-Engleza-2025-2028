#pragma once
#include <string>

class Protein
{
private:
	std::string organism; 
	std::string name; 
	std::string sequence; 

public:
	Protein(const std::string& organism = "", const std::string& name = "", const std::string& sequence = "");
	std::string getOrganism() const { return organism; }
	std::string getName() const { return name; }
	std::string getSequence() const { return sequence; }
};

