#pragma once
#include<string>
#include<vector>
#include<algorithm>
#include<iostream>

class Writer
{
	std::string name, expertise; 
public:
	Writer(const std::string& name, const std::string& exp) : name{ name }, expertise{ exp } {}
	std::string getName() const { return name; }
	std::string getExpertise() const { return expertise; }
};