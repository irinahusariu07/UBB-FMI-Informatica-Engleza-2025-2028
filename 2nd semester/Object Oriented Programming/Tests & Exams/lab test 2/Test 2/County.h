#pragma once
#include <iostream>
#include <string>

class County
{
protected:
	std::string name; 

public:
	County(const std::string& name) : name{ name } {}
	virtual bool eligible() = 0; 
	virtual int mandates() = 0; 
	virtual  std::string toString() = 0; 
	virtual ~County() {};
	std::string getCounty() { return name; }
};

