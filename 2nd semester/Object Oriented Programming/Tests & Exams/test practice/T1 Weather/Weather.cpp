#include "Weather.h"

Weather::Weather(const std::string& location, const std::string& name, const std::string& sensors)
{
	this->location = location; 
	this->name = name; 
	this->sensors = sensors; 
}
