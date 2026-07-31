#pragma once
#include"Driver.h"
#include"Report.h"
#include<sstream>
#include<fstream>

class Repo
{
private:
	std::string dfile, rfile; 
	std::vector<Driver> drivers; 
	std::vector<Report> reports; 

public:
	Repo(const std::string& dr, const std::string& re) : dfile{ dr }, rfile{ re } {
		readDriverFile(); 
		readReportFile(); 
	}

	void readDriverFile();
	void readReportFile();
	void writeReportFile(); 

	std::vector<Driver>& getDrivers() { return drivers; }
	std::vector<Report>& getReports() { return reports; }

	void addReport(Report& r);
	void updateStatus(const std::string& desc, int lat, int lon, const std::string& validator);
};

