#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<algorithm>

class Patient
{
private:
	std::string name, diagnosis, specialisation, doctor, admission; 

public:
	Patient(const std::string& na="", const std::string& diag = "undiagnosed",
		const std::string& spec = "", const std::string& doc = "", const std::string& ad="") :
		name{ na }, admission{ ad }, diagnosis{ diag }, specialisation{ spec }, doctor{ doc } {
	}

	std::string getName() const { return name; }
	std::string getDiag() const { return diagnosis; }
	std::string getSpec() const { return specialisation; }
	std::string getDoc() const { return doctor; }
	std::string getAdmission() const { return admission; }
	void setDiag(const std::string new_diag) { diagnosis = new_diag; }
	void setSpec(const std::string new_spec) { specialisation = new_spec; }
	void setDoc(const std::string new_doc) { doctor = new_doc; }
};