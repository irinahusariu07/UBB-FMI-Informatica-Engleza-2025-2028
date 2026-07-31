#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<algorithm>

class Bills
{
private:
	std::string company_name; 
	std::string serial_number; 
	double sum; 
	bool is_paid;

public:
	Bills(const std::string& company_name = "", const std::string& serial_number = "", double sum = 0.00, bool is_paid = false);
	std::string getCompany() { return this->company_name; }
	std::string getSerial() { return this->serial_number; }
	double getSum() { return this->sum; }
	bool getStatus() { return this->is_paid; }
	std::string toString();
	std::string GUItoString();
};

