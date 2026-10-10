#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

class Chef
{
	std::string name, cuisine; 

public:
	Chef(const std::string& na, const std::string& cui) : name{ na }, cuisine{ cui } {}
	std::string getName() const { return name; }
	std::string getCuisine() const { return cuisine; }

};