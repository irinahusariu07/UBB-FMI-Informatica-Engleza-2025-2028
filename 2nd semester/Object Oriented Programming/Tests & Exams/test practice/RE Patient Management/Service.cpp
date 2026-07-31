#include "Service.h"

void Service::addPatient(const std::string& name, const std::string& diagnosis, const std::string& speci, const std::string& doc, const std::string& date)
{
	if (name.empty() || date < "2026-06-30") throw std::runtime_error("Invalid data for patient");
	for (auto& p : repo.getPatients())
	{
		if (p.getName() == name) throw std::runtime_error("Patient already exists");
	}
	std::string finalDiag = diagnosis;
	std::string finalSpec = speci;
	std::string finalDoc = doc;

	if (diagnosis.empty()) finalDiag = "undiagnosed";
	if (speci.empty()) finalSpec = "";
	if (doc.empty()) finalDoc = "";
	Patient p{ name, finalDiag, finalSpec, finalDoc, date };
	repo.addPatient(p);
	notifyObservers(); 
}

std::vector<Patient> Service::sortByDates(std::vector<Patient> tosort)
{
	std::sort(tosort.begin(), tosort.end(), [&](const Patient& p1, const Patient& p2) {
		return compareDates(p1.getAdmission(), p2.getAdmission());
		});
	return tosort;
}

std::vector<Patient> Service::getSpecialisationPatients(const std::string& special)
{
	std::vector<Patient> special_patients; 
	for (auto& p : repo.getPatients())
	{
		if (p.getSpec() == special || p.getDiag() == "undiagnosed")

		{
			special_patients.push_back(p);
		}
	}
	if (special_patients.size() == 0) throw std::runtime_error("No patients that have same specialisation as doctor");
	return special_patients;
}

void Service::updatePatient(const std::string& pname, const std::string& doc, const std::string& diagn, const std::string& spec)
{
	bool chg = false; 
	if (diagn == "undiagnosed" || diagn.empty()) throw std::runtime_error("Invalid diagnosis");
	for (auto& p : repo.getPatients())
	{
		if (p.getName() == pname)
		{
			if (p.getDiag() == "undiagnosed" || p.getDoc() == doc)
			{
				repo.updatePatient(pname, diagn, spec);
				chg = true;
			}
		}
	}
	if (chg == false) throw std::runtime_error("Not a valid patient");
	else notifyObservers();
}




