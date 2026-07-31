#pragma once
#include "MedicalAnalysis.h"
#include "BMI.h"
#include "BP.h"
#include<iostream>
#include<fstream>

class Person
{
private:
	std::string name;
	std::vector<MedicalAnalysis*> analyses; 

public:
	Person(const std::string& name = "") : name{ name } {}
	std::string getName() { return this->name; }
	void addAnalysis(MedicalAnalysis* a) { analyses.push_back(a); }
	std::vector<MedicalAnalysis*> getAllAnalyses() { return analyses; }
	std::vector<MedicalAnalysis*> getAnalysesByMonth(int month);
	bool isIll(int month);
	std::vector<MedicalAnalysis*> getAnalysesBetweenDates(const std::string& date1, const std::string& date2);
	void writeToFile(const std::string& filename, const std::string& date1, const std::string& date2);

};

