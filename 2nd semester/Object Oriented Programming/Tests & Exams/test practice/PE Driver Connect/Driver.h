#pragma once 
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

class Driver
{
	std::string name; 
	int latitude, longitude;
	int score; 

public:
	Driver(const std::string& name, int latitude, int longitude, int score) :
		name{ name }, latitude{ latitude }, longitude{ longitude }, score{ score } {
	}

	std::string getName() const { return name; }
	int getLat() const { return latitude; }
	int getLong() const { return longitude; }
	int getScore() const { return score; }
	void incrementScore() { score++; }
};