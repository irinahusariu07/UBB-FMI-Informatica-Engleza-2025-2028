#include "Service.h"
#include <stdexcept>
#include <algorithm>

Service::Service(Repo& repository) : repository(repository )
{
}

void Service::addCar(const std::string& manufacturer, const std::string& model,  int year, const std::string& color)
{
	Car car{ manufacturer, model, year, color };
	checkString(car.getManufacturer());
	checkString(car.getModel());
	checkYear(car.getYear());
	checkString(car.getColor());
	if (repository.findCar(model, year) != -1) throw std::runtime_error("Car already exists");
	repository.addDB(car);
}

void Service::removeCar(const std::string& model,  int year)
{
	int id = repository.findCar(model, year);
	if (id == -1) throw std::runtime_error("Car doesnt exist");
	repository.removeDB(id);
}

Car* Service::allCars()
{
	return repository.getAll();
}



bool compareManMod(const Car& car1, const Car& car2)
{
	if (car1.getManufacturer() != car2.getManufacturer())
		return car1.getManufacturer() > car2.getManufacturer();
	return car1.getModel() > car2.getModel();
}

void Service::sortCars()
{
	int n = repository.getSize();
	Car* cars = repository.getAll();
	std::sort(cars, cars + n, compareManMod);
}


bool compareColor(const Car& car1, const Car& car2)
{
	return car1.getColor() > car2.getColor();
}

std::vector<Car> Service::filter()
{
	std::vector<Car> result; 
	Car* cars = repository.getAll();
	int n = repository.getSize();
	for (int i = 0; i < n; i++)
	{
		if (getDifference(cars[i]) > 45)
			result.push_back(cars[i]);
	}
	std::sort(result.begin(), result.end(), compareColor);
	return result; 
}

void Service::checkString(const std::string& txt)
{
	if (txt == "") throw std::runtime_error("String cannot be empty");
}

void Service::checkYear( int year)
{
	if (year < 0 || year > 2026) throw std::runtime_error("Invalid year");
}

void Service::addDefault()
{
	addCar("fiat", "bravo", 2007, "red");
	addCar("fiat", "idea", 1970, "black");
	addCar("audi", "a5", 2007, "blue");
	addCar("bmw", "coupe", 2014, "pink");
	addCar("ford", "fiesta", 1978, "yellow");
}

int Service::getDifference(Car car)
{
	return (2026 - car.getYear());
}


