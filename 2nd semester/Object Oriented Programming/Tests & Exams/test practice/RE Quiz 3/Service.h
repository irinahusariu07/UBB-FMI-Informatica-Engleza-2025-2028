#pragma once
#include"Repo.h"
#include"Observer.h"

class Service
{
private:
	Repo& repo;
	std::vector<Observer*> obs;

public:
	Service(Repo& r) :repo{ r } {}
	std::vector<Question> getAllID();
	std::vector<Question> getAllScore();

	void addQuestion(int id, const std::string& txt, const std::string& ans, int sc);
	bool correctAns(int id, const std::string& ans);
	void updateScore(const std::string& name, int score) { repo.updateScore(name, score); notifyObs(); }
	int getScoreById(int id);

	void notifyObs() { for (auto* o : obs) o->update(); }
	void registerObs(Observer* o) { obs.push_back(o); }
};

