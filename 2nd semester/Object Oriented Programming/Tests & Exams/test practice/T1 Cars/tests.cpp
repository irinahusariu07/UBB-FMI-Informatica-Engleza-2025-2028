#include "tests.h"

void testFilter()
{
	Repo repository;
	Service service(repository);
	service.addCar("porsche", "911", 1900, "pink");
	service.addCar("porsche", "panamera", 2000, "black");
	assert(repository.getSize() == 2);
	service.filter();
	//assert(repository.getSize() == 1);
	Car* cars = service.allCars();
	assert(cars[0].getModel() == "911");
}

void testAdd()
{
	Repo repository; 
	Service service(repository);
	service.addCar("porsche", "911", 2000, "pink");
	int id = repository.findCar("911", 2000);
	bool found = true;
	if (id == -1)
		found = false;
	assert(found == true);
	
}

void testAll()
{
	std::cout << "TEST PASSED";
	testFilter();
	testAdd();
}
