#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<algorithm>

class Doctor
{
private:
	std::string name, specialisation; 

public:
	Doctor(const std::string& na, const std::string sp) : name{ na }, specialisation{ sp } {}
	std::string getName() const { return this->name; }
	std::string getSpecial() const { return this->specialisation; }
};