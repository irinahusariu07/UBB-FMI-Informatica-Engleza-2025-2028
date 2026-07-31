#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

class Bacteria
{
private:
	std::string name, species; 
	int size; 
	std::vector<std::string>diseases; 

public:
	Bacteria(const std::string& na, const std::string& spec, int siz, std::vector<std::string>dis) :
		name{ na }, species{ spec }, size{ siz }, diseases{ dis } {
	}

	std::string getName() const { return name; }
	std::string getSpecies() const { return species; }
	int getSize() const { return size; }
	std::vector<std::string> getDiseases() const { return diseases; }

	void addDisease(const std::string& dis) { diseases.push_back(dis); }

};