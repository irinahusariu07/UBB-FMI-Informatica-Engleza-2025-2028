#pragma once
#include"Car.h"
class Service
{
private:
	std::vector<Car> allCars; 
	std::string filename; 

public:
	Service(const std::string& filename) { this->filename = filename; }
	void readFromFile(); 
	std::vector<Car> getAll();
	std::vector<Car> getCarsFromManufacturer(const std::string& manufacturer);

};

