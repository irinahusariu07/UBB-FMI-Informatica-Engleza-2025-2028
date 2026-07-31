#pragma once
#include "Doctor.h"
#include"Patient.h"
#include<sstream>
#include<fstream>

class Repo
{
private:
	std::vector<Doctor> doctors; 
	std::vector<Patient> patients; 
	std::string pfile, dfile; 

public:
	Repo(const std::string& doc, const std::string& pat) : dfile{ doc }, pfile{ pat }
	{
		readPatientFile(); 
		readDoctorFile(); 
	}
	void readPatientFile(); 
	void readDoctorFile(); 
	void writePatientFile(); 

	void addPatient(Patient& p); 
	void updatePatient(const std::string& name, const std::string& diag, const std::string&spec);
	std::vector<Patient> getPatients() { return patients; }
	std::vector<Doctor> getDoctors() { return doctors; }
};



