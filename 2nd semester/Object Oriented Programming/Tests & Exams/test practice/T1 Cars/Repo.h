#pragma once
#include "DynamicVector.h"
#include "Car.h"

class Repo
{
private:
	DynamicVector carDataBase;
public:
	void addDB(Car car);
	void removeDB(int car_id);
	Car* getAll() const; 
	int getSize() const; 
	int findCar(const std::string&model, int year);
};



