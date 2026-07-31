#pragma once
#include "MedicalAnalysis.h"
class BP : public MedicalAnalysis
{
private:
	int systolic, diastolic; 
public:
	BP(const std::string& date, int systolic, int diastolic) : MedicalAnalysis{date}, systolic{systolic}, diastolic{diastolic} {}
	bool isResultOK() override; 
	std::string toString() override;
	int getSystolic() { return this->systolic; }
	int getDiastolic() { return this->diastolic; }
};

