#include "Repo.h"

void Repo::readPatientFile()
{
	std::ifstream file(pfile);
	if (!file.is_open()) throw std::runtime_error("Patient file corrupted");
	patients.clear(); 
	std::string line; 
	while (std::getline(file, line))
	{
		if (line.empty()) continue; 
		std::stringstream ss(line); 
		std::string name, diag, spec, doc, date; 
		std::getline(ss, name, '|');
		std::getline(ss, diag, '|');
		std::getline(ss, spec, '|');
		std::getline(ss, doc, '|');
		std::getline(ss, date, '|'); 
		Patient p(name, diag, spec, doc, date); 
		patients.push_back(p);
	}
	file.close(); 
}

void Repo::readDoctorFile()
{
	std::ifstream file(dfile); 
	if (!file.is_open()) throw std::runtime_error("Doctor file corrupted"); 
	doctors.clear();
	std::string line; 
	while (std::getline(file, line))
	{
		if (line.empty()) continue; 
		std::stringstream ss(line);
		std::string name, spec; 
		std::getline(ss, name, '|'); 
		std::getline(ss, spec, '|'); 
		Doctor d(name, spec); 
		doctors.push_back(d);
	}
	file.close(); 
}

void Repo::writePatientFile()
{
	std::ofstream file(pfile);
	if (!file.is_open()) throw std::runtime_error("Patient file cannot be opened for writing");
	for (auto& p : patients)
	{
		file << p.getName() << "|" << p.getDiag() << "|" << p.getSpec() << "|" << p.getDoc() << "|" << p.getAdmission() << "\n";
	}
	file.close(); 
}

void Repo::addPatient(Patient& p)
{
	patients.push_back(p);
	writePatientFile();
}

void Repo::updatePatient(const std::string& name, const std::string& diag, const std::string& spec)
{
	bool chg = false; 
	for (auto& p : patients)
	{
		if (p.getName() == name)
		{
			p.setDiag(diag);
			p.setSpec(spec);
			chg = true; 
			writePatientFile();
		}
	}
	if (chg == false) throw std::runtime_error("Patient not found"); 
	}



