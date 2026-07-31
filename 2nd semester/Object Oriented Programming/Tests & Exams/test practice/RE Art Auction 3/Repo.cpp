#include "Repo.h"

void Repo::readItemFile()
{
	std::ifstream file(this->ifile);
	if (!file.is_open()) throw std::runtime_error("Item file corrupted!");

	items.clear();
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty()) continue;
		std::stringstream ss(line);
		std::string name, categ, cps, offers;
		std::getline(ss, name, '|');
		std::getline(ss, categ, '|');
		std::getline(ss, cps, '|');
		int cp = std::stoi(cps);
		std::getline(ss, offers, '|');

		std::vector<std::tuple<int, std::string, int>> off;
		std::stringstream sso(offers);
		std::string segment;

		while (std::getline(sso, segment, ','))
		{
			if (segment.empty()) continue;
			std::stringstream sst(segment);
			std::string ids, date, vals;
			std::getline(sst, ids, '~');
			std::getline(sst, date, '~');
			std::getline(sst, vals, '~');
			off.push_back(std::make_tuple(std::stoi(ids), date, std::stoi(vals)));
		}
		Item i{ name, categ, cp, off };
		items.push_back(i);
	}
	file.close();
}

void Repo::readUserFile()
{
	std::ifstream file(this->ufile);
	if (!file.is_open()) throw std::runtime_error("User file corrupted");

	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty()) continue;
		std::stringstream ss(line);
		std::string name, ids, type;
		std::getline(ss, name, '|');
		std::getline(ss, ids, '|');
		std::getline(ss, type, '|');
		User u(name, std::stoi(ids), type);
		users.push_back(u);
	}
	file.close();
}

void Repo::writeItemFile()
{
	std::ofstream file(this->ifile);
	if (!file.is_open()) throw std::runtime_error("Cannot open items file for writing");

	for (auto& i : items)
	{
		file << i.getName() << "|" << i.getCategory() << "|" << i.getCurrent() << "|";
		const auto& off = i.getOffers();
		for (int j = 0; j < off.size(); j++)
		{
			file << std::get<0>(off[j]) << "~" << std::get<1>(off[j]) << "~" << std::get<2>(off[j]);
			if (j < off.size() - 1) file << ",";
		}
		file << "\n";
	}
	file.close();
}

void Repo::addItem(Item& i)
{
	items.push_back(i);
	writeItemFile();
}

void Repo::addOffer(const std::string& name, int id, const std::string& date, int value)
{
	for (auto& i : items)
	{
		if (i.getName() == name)
		{
			if (value <= i.getCurrent())
				throw std::runtime_error("Cannot bid with value <= current price");

			i.setPrice(value);
			i.addOffer(id, date, value);

			writeItemFile();
			return;
		}
	}

	throw std::runtime_error("Item not found");
}


