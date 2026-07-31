#pragma once
#include <string>
#include<vector>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<sstream>

class Car
{
private:
	std::string manufacturer, model, color; 
	int year; 

public:
	Car(const std::string& manufacturer, const std::string& model, int year, const std::string& color) {
		this->manufacturer = manufacturer;
		this->model = model;
		this->year = year; 
		this->color = color; 
	}
	std::string getManufacturer() { return this->manufacturer; }
	std::string getModel() { return this->model; }
	std::string getColor() const { return this->color; }
	int getYear() { return this->year; }

	std::string GUItoString()
	{
		return "Manufacturer: " + getManufacturer() + " Model: " + getModel() + "\n";
	}
};

