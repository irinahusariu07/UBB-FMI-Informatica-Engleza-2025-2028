#pragma once
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

class Astronomer
{
	std::string name, constellation; 
public:
	Astronomer(const std::string& name, const std::string& constellation) :name{ name }, constellation{ constellation } {}
	std::string getName() const { return name; }
	std::string getConstellation() const { return constellation; }
};