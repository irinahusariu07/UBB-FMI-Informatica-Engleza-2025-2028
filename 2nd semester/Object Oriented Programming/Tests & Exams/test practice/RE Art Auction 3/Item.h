#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>


class Item
{
	std::string name, category;
	int current_price;
	std::vector<std::tuple<int, std::string, int>> offers;

public:
	Item(const std::string& name, const std::string& categ, int cp, std::vector<std::tuple<int, std::string, int>> off) :
		name{ name }, category{ categ }, current_price{ cp }, offers{ off } {
	}

	std::string getName() const { return this->name; }
	std::string getCategory() const { return this->category; }
	int getCurrent() const { return this->current_price; }
	std::vector<std::tuple<int, std::string, int>> getOffers() const { return offers; }
	void addOffer(int id, const std::string& date, int price) { this->offers.push_back(std::make_tuple(id, date, price)); }

	void setPrice(int newp) { current_price = newp; }
};