#pragma once
#include"County.h"
#include"Party.h"
#include"Alliance.h"
#include"Independent.h"
#include<vector>

class Service
{
private:
	std::vector<County*> counties; 
public:
	void addCounty(County* c) { counties.push_back(c); }
	std::vector<County*> getAll() { return counties; }

};

