#pragma once
#include <iostream>
#include<string>
#include<vector>
#include<algorithm>

class User
{
private:
	std::string name, type; 
public:
	User(const std::string& name = "", const std::string& type = "") : name{ name }, type{ type } {}
	std::string getName() const { return name; }
	std::string getType() const { return type; }
	std::string toString() { return "Name: " + getName() + " Type: " + getType() + "\n"; }
};

