#pragma once
#include<algorithm>
#include<string>
#include<vector>
#include<iostream>
#include<sstream>
#include<fstream>

class Airport
{
private:
	int hour, minute, delay; 
	std::string status, destination; 

public:
	Airport(int hour, int minute, const std::string& status, const std::string& destination, int delay)
	{
		this->hour = hour; 
		this->minute = minute; 
		this->status = status; 
		this->destination = destination; 
		this->delay = delay; 
	}
	std::string getStatus() { return status;  }
	std::string getDestination() { return destination; }
	int getHour() { return hour; }
	int getMinute() { return minute; }
	int getDelay() { return delay; }
	std::string GUItoString()
	{
		return "Hour: " + std::to_string(getHour()) + " Minutes: " + std::to_string(getMinute()) + " Type: " + getStatus() +
			" Destination: " + getDestination() + " Delay: " + std::to_string(getDelay()) + "\n";
	}

};

