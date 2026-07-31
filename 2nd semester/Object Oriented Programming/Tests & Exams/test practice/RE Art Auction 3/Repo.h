#pragma once
#include"Item.h"
#include"User.h"
#include<fstream>
#include<sstream>

class Repo
{
private:
	std::string ufile, ifile;
	std::vector<User> users;
	std::vector<Item> items;

public:
	Repo(const std::string& uf, const std::string& itf) : ufile{ uf }, ifile{ itf } { readUserFile(); readItemFile(); }

	void readItemFile();
	void readUserFile();
	void writeItemFile();
	std::vector<Item> getItems() { return items; }
	std::vector<User> getUsers() { return users; }

	std::vector<std::tuple<int, std::string, int>> getOffers(const std::string& name)
	{
		for (auto& i : items)
			if (i.getName() == name)
				return i.getOffers();

		throw std::runtime_error("Item not found");
	}

	void addItem(Item& i);
	void addOffer(const std::string& name, int id, const std::string& date, int value);
};


