#pragma once
#include "Astronomer.h"
#include "Star.h"
#include <fstream>
#include <sstream>

class Repo
{
	std::vector<Star> stars;
	std::string filename; 

public:
	Repo(const std::string& filename) : filename{ filename }
	{
		readFromFile();
	}
	void readFromFile(); 
	void writeToFile(); 
	void addStar(Star& s) 
	{
		stars.push_back(s); 
		writeToFile(); 
	}
	std::vector<Star> getStars() const { return stars; }
};

