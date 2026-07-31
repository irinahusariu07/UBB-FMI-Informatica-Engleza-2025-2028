#include "Bills.h"

Bills::Bills(const std::string& company_name, const std::string& serial_number, double sum, bool is_paid)
{
	this->company_name = company_name;
	this->serial_number = serial_number;
	this->sum = sum; 
	this->is_paid = is_paid;
}

std::string Bills::toString()
{
	return "Company: " + getCompany() + " Serial number: " + getSerial() + " Sum: " + std::to_string(getSum()) + " Status: " + std::to_string(getStatus()) + "\n";
}

std::string Bills::GUItoString()
{
	return "Company: " + getCompany() + " Sum: " + std::to_string(getSum()) + "\n";
}
