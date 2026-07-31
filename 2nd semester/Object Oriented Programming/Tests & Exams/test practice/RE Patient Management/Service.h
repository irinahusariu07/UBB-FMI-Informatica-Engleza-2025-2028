#pragma once
#include "Repo.h"
#include "Observer.h"

class Service
{
private:
	Repo& repo; 
	std::vector<Observer*> observers; 
public:
	Service(Repo& r) : repo{ r } {}
	std::vector<Patient> getPatients() { return repo.getPatients();}
	std::vector<Doctor> getDoctors() { return repo.getDoctors(); }

	void addPatient(const std::string& name, const std::string& diagnosis, const std::string& speci,
		const std::string& doc, const std::string& date); 
	bool compareDates(const std::string& date1, const std::string& date2) { return date1 < date2; }
	std::vector<Patient> sortByDates(std::vector <Patient> tosort);
	std::vector<Patient> getSpecialisationPatients(const std::string& special);
	std::string getDocByName(const std::string& name) {
		for (auto& d : getDoctors())
			if (d.getName() == name) return d.getSpecial();
	}
	std::vector<Patient> getDocNamePatients(const std::string& doc) {
		std::vector<Patient> result; 
		for (auto& p : getPatients())
		{
			if (p.getDoc() == doc) result.push_back(p);
		}
		return result; 
	}

	void updatePatient(const std::string& pname, const std::string& doc, const std::string& diagn, const std::string& spec);

	void addObserver(Observer* o) { observers.push_back(o); }
	void notifyObservers() { for (auto o : observers) o->update(); }
};