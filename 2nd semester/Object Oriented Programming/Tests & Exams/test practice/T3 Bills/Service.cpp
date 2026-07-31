#include "Service.h"

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! READ FROM FILE
void Service::readFromFile()
{
	std::ifstream file(this->filename);
	if (!file.is_open()) throw std::runtime_error("File corrupted!\n");
	std::string line; 

	while (std::getline(file, line))
	{
		if (line.empty()) continue;
		std::stringstream ss(line); 
		std::string company, serial, sums, statuss; 
		std::getline(ss, company, '|');
		std::getline(ss, serial, '|');
		std::getline(ss, sums, '|');
		std::getline(ss, statuss, '|');

		double sum = std::stod(sums);
		bool status;
		if (statuss == "false") status = false;
		else if (statuss == "true") status = true; 
		Bills b{ company, serial, sum, status };
		this->bills.push_back(b);
	}
	file.close();
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! SORT 
std::vector<Bills> Service::getAll()
{
	std::sort(bills.begin(), bills.end(), [](Bills& b1, Bills& b2) {
		return b1.getCompany() < b2.getCompany();
		});
	return this->bills;
}

std::vector<Bills> Service::getBillsStatus(bool paid)
{
	std::vector<Bills> all = getAll();
	std::vector<Bills> status;
	//if paid = true => get all paid bills if paid = false => get all unpaid 
	for (auto& b : all)
	{
		if (paid == b.getStatus()) status.push_back(b);
	}
	return status; 
}



double Service::totalSum(const std::string& company)
{
	std::vector<Bills> all = getAll();
	double total = 0.00; 
	bool found = false;

	for (auto& b : all) {
		if (b.getCompany() == company)
		{	
			found = true; 
			if (b.getStatus() == false) total += b.getSum();
		}
	}

	if (found == true) return total;
	else if (total == 0.00 && found == true) throw std::runtime_error("Company doesnt have unpaid bills");
	else if (found == false) throw std::runtime_error("No companies with that name");
}
