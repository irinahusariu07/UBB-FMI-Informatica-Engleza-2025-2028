#include "Repo.h"

void Repo::readDriverFile()
{
	std::ifstream file(this->dfile);
	if (!file.is_open()) throw std::runtime_error("Driver file corrupted");

	drivers.clear(); 
	std::string line; 

	while (std::getline(file, line))
	{
		if (line.empty()) continue; 
		std::stringstream ss(line); 
		std::string name, stat, lati, longi, sc; 

		std::getline(ss, name, '|');
		std::getline(ss, stat, '|');
		std::getline(ss, lati, '|');
		std::getline(ss, longi, '|');
		std::getline(ss, sc, '|');

		Driver d{ name, stat, std::stoi(lati), std::stoi(longi), std::stoi(sc) };
		drivers.push_back(d);
	}
	file.close();
}

void Repo::readReportFile()
{
	std::ifstream file(this->rfile);
	if (!file.is_open()) throw std::runtime_error("Report file corrupted");

	reports.clear();
	std::string line;

	while (std::getline(file, line))
	{
		if (line.empty()) continue;
		std::stringstream ss(line);
		std::string desc, rep, lati, longi, valid;
		
		std::getline(ss, desc, '|');
		std::getline(ss, rep, '|');
		std::getline(ss, lati, '|');
		std::getline(ss, longi, '|');
		std::getline(ss, valid, '|');
		
		Report r{ desc, rep, std::stoi(lati), std::stoi(longi), valid };
		reports.push_back(r); 
	}
	file.close();
}

void Repo::writeReportFile()
{
	std::ofstream file(this->rfile);
	if (!file.is_open()) throw std::runtime_error("Report file writing problem");

	for (auto& r : reports)
	{
		file << r.getDesc() << "|" << r.getReporter() << "|" << r.getLatit() << "|" << r.getLongit() << "|" << r.getValid() << "\n";
	}
	file.close();
}

void Repo::addReport(Report& r)
{
	reports.push_back(r);
	writeReportFile();
}

void Repo::updateStatus(const std::string& desc, int lat, int lon, const std::string& validator)
{
	bool chg = false; 
	std::string driver = "";
	for (auto& r : reports)
	{
		if (r.getDesc() == desc && r.getLatit() == lat && r.getLongit() == lon)
		{
			if (r.getValidators().size() < 2 || r.getValid() == "false") r.addValidator(validator);
			if (r.getValidators().size() == 2 && r.getValid() == "false")
			{
				r.setValid();
				driver = r.getReporter();
			}
			chg = true;
		}
	}
	if (!chg) throw std::runtime_error("Cannot find report with this data");
	if(!driver.empty()) //dam update si la score
	for (auto& d : drivers)
	{
		if (d.getName() == driver)
		{
			d.setScore();
		}
	}
	writeReportFile();
}

