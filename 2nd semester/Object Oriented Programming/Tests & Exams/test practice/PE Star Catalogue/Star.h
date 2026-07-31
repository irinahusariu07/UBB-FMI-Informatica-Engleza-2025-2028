#pragma once
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

class Star
{
	std::string name, constellation; 
	int ra, dec, diam;

public:
	Star(const std::string& name, const std::string& constellation, int ra, int dec, int diam) {
		this->name = name; 
		this->constellation = constellation; 
		this->ra = ra;
		this->dec = dec; 
		this->diam = diam;
	}

	std::string getName() const { return name; }
	std::string getConstellation() const { return constellation; }
	int getRA() const { return ra; }
	int getDec() const { return dec; }
	int getDiam() const { return diam; }
};