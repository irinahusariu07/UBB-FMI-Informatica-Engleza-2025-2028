#pragma once
#include"Airport.h"

class Service
{
private:
	std::string filename; 
	std::vector<Airport> flights; 

public:
	Service(const std::string& filename) : filename{ filename } {}
	void readFromFile(); 
	std::vector<Airport> getAll(); 
	std::vector<Airport> getWithDelay(int min_delay);
	std::vector<Airport> getAfterHour(int min_hour); 
};

