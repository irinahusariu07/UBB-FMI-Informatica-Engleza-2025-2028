#pragma once
#include "Observer.h"
#include <string>
#include <vector>

class Subject
{
private:
	std::vector<Observer*> observer_list;
public:
	Subject(std::vector<Observer*> obs) : observer_list{ obs } {}
	void registerObserver(Observer* o);
	void unregisterObserver(Observer* o);
	void notify();
};