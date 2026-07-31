#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>


class User
{
private:
	std::string name, type;
	int id;

public:
	User(const std::string& name, int id, const std::string type) : name{ name }, id{ id }, type{ type } {}
	std::string getName() const { return this->name; }
	std::string getType() const { return this->type; }
	int getID() const { return this->id; }
};