#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>


class Agent
{
	std::string name, streets; 
	int circlex, circley, rad; 

public:
	Agent(const std::string& name, std::string streets, int circlex, int circley, int rad) :
		name{ name }, streets{ streets }, circlex{ circlex }, circley{ circley }, rad{ rad } {
	}

	std::string getName() const { return name; }
	std::string getStreets() const { return streets; }
	int getCircleX() const { return circlex; }
	int getCircleY() const { return circley; }
	int getRad() const { return rad; }

};