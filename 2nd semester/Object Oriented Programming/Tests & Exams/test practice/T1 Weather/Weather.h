#pragma once
#include<string>

class Weather 
{
private:
	std::string location, name, sensors;
public:
	Weather(const std::string& location="", const std::string& name = "", const std::string& sensors = "");
	std::string getLocation() const { return location; }
	std::string getName() const {return name;}
	std::string getSensors() const { return sensors; }
};