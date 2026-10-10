#include "Repo.h"

void Repo::readAgentFile()
{
	std::ifstream file{ afile };
	if (!file.is_open()) throw std::runtime_error("Agent file corrupted!");
	agents.clear();
	std::string line; 
	while (std::getline(file, line))
	{
		if (line.empty()) continue; 
		std::stringstream ss(line);
		std::string name, streets, xs, ys, rs; 
		std::getline(ss, name, '|');
		std::getline(ss, streets, '|');
		std::getline(ss, xs, '|');
		int x = std::stoi(xs);
		std::getline(ss, ys, '|');
		int y = std::stoi(ys); 
		std::getline(ss, rs, '|');
		int r = std::stoi(rs);
		Agent a{ name, streets, x, y, r };
		agents.push_back(a);
 	}
	file.close();
}

void Repo::readParcelFile()
{
	std::ifstream file{ pfile };
	if (!file.is_open()) throw std::runtime_error("Parcel file corrupted!");
	parcels.clear();
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty()) continue;
		std::stringstream ss(line);
		std::string rec, streets, nums, xs, ys, del;
		std::getline(ss, rec, '|');
		std::getline(ss, streets, '|');
		std::getline(ss, nums, '|');
		int num = std::stoi(nums);
		std::getline(ss, xs, '|');
		int x = std::stoi(xs);
		std::getline(ss, ys, '|');
		int y = std::stoi(ys);
		std::getline(ss, del, '|');
		bool delivery; 
		if (del == "1") delivery = true;
		else delivery = false; 
		Parcel p{ rec, streets, num, x, y, delivery };
		parcels.push_back(p);
	}
	file.close();
}

void Repo::writeParcelFile()
{
	std::ofstream file(pfile);
	if (!file.is_open()) throw std::runtime_error("Cannot write to parcel file!");
	for (auto& p : parcels)
	{
		file << p.getRecipient() << "|" << p.getStreet() << "|" << p.getNumber() << "|" << p.getLocX() << "|" << p.getLocY() << "|" << p.getStatus() << "\n";
	}
	file.close();
}

void Repo::updateParcel(const std::string& recipient)
{
	bool chg = false; 
	for (auto& i : parcels)
	{
		if (i.getRecipient() == recipient)
		{
			i.setStatus(true);
			chg = true; 
			
			return;
		}
	}
	if (chg == false) throw std::runtime_error("No parcel for given recipient");
	writeParcelFile();
}





