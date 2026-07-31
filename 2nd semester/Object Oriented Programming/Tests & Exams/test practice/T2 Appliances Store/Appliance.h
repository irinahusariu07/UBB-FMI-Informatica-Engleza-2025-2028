#pragma once
#include<string>
#include<algorithm>
#include<vector>

class Appliance
{
protected:
	std::string id; 
public:
	Appliance(const std::string& id) : id{ id } {}
	virtual double consumeElectricity() = 0; 
	virtual std::string toString() = 0;
	std::string getID() { return id; }
	~Appliance() {};
};

