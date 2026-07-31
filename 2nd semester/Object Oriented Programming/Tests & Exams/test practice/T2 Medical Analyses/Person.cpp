#include "Person.h"

std::vector<MedicalAnalysis*> Person::getAnalysesByMonth(int month)
{
	std::vector<MedicalAnalysis*> analyses_month;
	for (auto a : analyses)
	{
		int a_month = std::stoi(a->getDate().substr(5, 2));
		if (a_month == month) analyses_month.push_back(a);
	}
	return analyses_month; 
}

bool Person::isIll(int month)
{ 
	std::vector<MedicalAnalysis*>corresponding = getAnalysesByMonth(month); 
	for (auto a : corresponding)
	{
		if (a->isResultOK()) return false;
	}
	return true;
}

std::vector<MedicalAnalysis*> Person::getAnalysesBetweenDates(const std::string& date1, const std::string& date2)
{
	std::vector<MedicalAnalysis*> analyses_month;
	for (auto a : analyses)
	{
		if (date1 < a->getDate() && date2 > a->getDate()) analyses_month.push_back(a);
	}
	return analyses_month;
}

void Person::writeToFile(const std::string& filename, const std::string& date1, const std::string& date2)
{
	std::ofstream file(filename);
	std::vector<MedicalAnalysis*> corresponding = getAnalysesBetweenDates(date1, date2);
	for (MedicalAnalysis* a : corresponding)
	{
		file << a->toString() << "\n";
	}
	file.close();
}


