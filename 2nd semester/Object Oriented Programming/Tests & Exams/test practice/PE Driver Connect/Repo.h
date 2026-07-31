#pragma once
#include "Report.h"
#include"Driver.h"
#include<sstream>
#include<fstream>

class Repo
{
	std::vector<Driver> drivers; 
	std::vector<Report> reports; 
	std::string driver_file, report_file; 

public:
	Repo(const std::string& driver_file, const std::string& report_file) :
		driver_file{ driver_file }, report_file{ report_file } {
		readDriverFile(); 
		readReportFile();
	}
	void readDriverFile(); 
	void readReportFile();
	void writeReportFile(); 
	void addReport(Report& r) { reports.push_back(r); writeReportFile(); }
	void updateReport(Report& r);
	void updateDriver(Driver& d);
	std::vector<Report>& getReports()  { return reports; }
	std::vector<Driver> getDrivers()  { return drivers;  }
	Driver& getDriverByName(const std::string& name) {
		for (auto& d : drivers)
		{
			if (d.getName() == name) return d; 
		}
		throw std::runtime_error("Driver not found");
	}
};


