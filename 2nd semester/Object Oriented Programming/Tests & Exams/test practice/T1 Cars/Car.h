#pragma once
#include<string>
#include <iostream>
class Car
{
private:
	std::string manufacturer; 
	std::string model;
	std::string color; 
	int year; 
public:
	Car(const std::string& manufacturer = "", const std::string& model = "", int year = 0, const std::string& color = "");
	std::string getManufacturer() const { return manufacturer; }
	std::string getModel() const { return model; }
	std::string getColor() const { return color; }
	int getYear() const { return year; }
	

};
	

