#include "Repo.h"

void Repo::addDB(Car car)
{
	carDataBase.add(car);
}

void Repo::removeDB(int car_id)
{
	carDataBase.remove(car_id);
}

Car* Repo::getAll() const
{
	return carDataBase.getAll();
}

int Repo::getSize() const
{
	return carDataBase.getSize();
}

int Repo::findCar(const std::string& model, int year)
{
	Car* cars = carDataBase.getAll();
	int n = carDataBase.getSize();
	for (int i = 0; i < n; i++)
	{
		if (cars[i].getModel() == model && cars[i].getYear() == year)
			return i; 
	}
	return -1; 
}




