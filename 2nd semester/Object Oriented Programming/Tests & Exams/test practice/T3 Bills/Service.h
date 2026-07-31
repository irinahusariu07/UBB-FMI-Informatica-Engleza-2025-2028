#pragma once
#include<sstream>
#include<fstream>
#include"Bills.h"

class Service
{
private:
	std::vector<Bills> bills; 
	std::string filename; 

public:
	Service(const std::string& filename) { this->filename = filename; }

	void readFromFile();
	std::vector<Bills> getAll(); 
	std::vector<Bills> getBillsStatus(bool paid); 
	double totalSum(const std::string& company);
};

