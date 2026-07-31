#include "Car.h"

Car::Car(const std::string& manufacturer, const std::string& model,  int year, const std::string& color)
{
	this->manufacturer = manufacturer;
	this->model = model;
	this->year = year; 
	this->color = color; 
}
