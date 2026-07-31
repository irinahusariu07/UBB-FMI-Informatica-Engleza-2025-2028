#pragma once
#include <vector>
#include"Repo.h"
#include"DynamicVector.h"
#include"Car.h"

class Service
{
private:
	Repo& repository; 
public:
	Service(Repo& repository);
	void addCar(const std::string& manufacturer, const std::string& model,  int year, const std::string& color);
	void removeCar(const std::string& model,  int year);
	int numberOfCars() { return repository.getSize(); }
	Car* allCars();
	void sortCars();
	//bool compareManMod(Car& car1, Car& car2);
	///bool compareColor(Car& car1, Car& car2);
	std::vector<Car> filter();
	void checkString(const std::string& txt);
	void checkYear(int year);
	void addDefault();
	int getDifference(Car car);
};

