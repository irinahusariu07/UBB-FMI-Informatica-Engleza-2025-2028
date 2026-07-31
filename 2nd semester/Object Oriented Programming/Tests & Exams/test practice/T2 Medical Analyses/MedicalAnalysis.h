#pragma once
#include <string>
#include <vector>
class MedicalAnalysis
{
protected:
	std::string date; 
public:
	MedicalAnalysis(const std::string& date = "") : date{ date } {}
	virtual ~MedicalAnalysis() {}; 
	virtual bool isResultOK() = 0; 
	virtual std::string toString() = 0; 
	std::string getDate() { return date; }
};

