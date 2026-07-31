#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

class Driver
{
	std::string name, status; 
	int latit, longit, score; 

public:
	Driver(const std::string& na, const std::string& st, int lat, int longi, int sc) :
		name{ na }, latit{ lat }, longit{ longi }, status{ st }, score{ sc } {
	}

	int getLatit() const { return latit; }
	int getLongit() const { return longit; }
	int getScore() const { return score; }
	std::string getName() const { return name; }
	std::string getStatus() const { return status; }
	void setStatus(const std::string& stat) { status = stat; }
	void setLatit(int newl) { latit = newl; }
	void setLongit(int newl) { longit = newl; }
	void setScore() { score++; }
};
