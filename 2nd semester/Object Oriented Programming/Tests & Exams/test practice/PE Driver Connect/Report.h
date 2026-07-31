#pragma once 
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

class Report
{
	std::string desc, reporter; 
	int latitude, longitude;
	bool status; 
	std::vector<std::string>validators; 

public:
	Report(const std::string& desc, const std::string& rep, int lat, int longi, bool status) :
		desc{ desc }, reporter{ rep }, latitude{ lat }, longitude{ longi }, status{ status } {
	}
	
	std::string getDesc() const { return desc; }
	std::string getReporter() const { return reporter; }
	int getLat() const { return latitude; }
	int getLong() const { return longitude; }
	bool getStatus() const { return status; }
	void setReporter(const std::string& rep) { reporter = rep; }
	void setStatus(bool stat) { status = stat; }
	void addValidator(const std::string& name) {
		if (name != reporter) validators.push_back(name);
	}
	int getValidatorCount() const { return validators.size(); }
	bool checkValidator(std::string name)
	{
		for (auto n : validators)
		{
			if (n == name) return true;
		}
		return false;
	}
};