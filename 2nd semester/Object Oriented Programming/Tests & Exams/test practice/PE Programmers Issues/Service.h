#pragma once
#include "Repo.h"
#include "Observer.h"
class Service
{
private:
	Repo& repo;
	std::vector<Observer*> observers;
public:
	Service(Repo& r) : repo{ r } {}
	void addIssue(const std::string& desc, const std::string& reporter);
	void resolveIssue(const std::string& desc, const std::string&solver);
	void removeIssue(const std::string& desc);
	void registerObserver(Observer* o) {observers.push_back(o);}
	void notifyObservers() { for (auto o : observers) o->update(); }
	std::vector<Issue> getIssues() const { return repo.getIssues(); }
};

