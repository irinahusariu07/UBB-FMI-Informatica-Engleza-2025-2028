#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

class Biologist
{
private:
	std::string name; 
	std::vector<std::string> studied_species; 

public:
	Biologist(const std::string& na, std::vector<std::string>stsp) : name{ na }, studied_species{ stsp } {}
	std::string getName() const { return name; }
	std::vector<std::string> getStudied() const { return studied_species; }
};