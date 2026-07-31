#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

class Report
{
private:
	std::string desc, reporter, valid;
	std::vector<std::string> validators; 
	int latit, longit; 

public:
	Report(const std::string& des, const std::string rep, int latit, int longit, const std::string& val) :
		desc{ des }, reporter{ rep }, latit{ latit }, longit{ longit }, valid{ val } {
	}

	std::string getDesc() const { return desc; }
	std::string getReporter() const { return reporter; }
	std::string getValid() const { return valid; }
	int getLatit() const { return latit; }
	int getLongit() const { return longit; }
	std::vector<std::string> getValidators() const { return validators; }
	void addValidator(const std::string val) { validators.push_back(val); }
	void setValid() { valid = "true"; }
};