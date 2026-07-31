#pragma once
#include"Repo.h"
#include"Observer.h"

class Service
{
	Repo& repo;
	std::vector<Observer*> observers;
public:
	Service(Repo& r) : repo{ r } {}
	void registerObserver(Observer* o) { observers.push_back(o); }
	void notifyObservers() { for (auto& o : observers) o->update(); }

	std::vector<Item> getItems();
	std::vector<Item> filterByCateg(const std::string& cat);
	void addOffer(const std::string& name, int id, const std::string& date, int value);
	void addItem(const std::string& name, const std::string& category, int price);
	std::vector<std::tuple<int, std::string, int>> getOffers(const std::string& name) { return repo.getOffers(name); }
};

