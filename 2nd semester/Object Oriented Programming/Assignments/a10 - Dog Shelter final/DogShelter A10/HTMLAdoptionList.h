#pragma once
#include "AdoptionList.h"
#include <fstream>

class HTMLAdoptionList : public AdoptionList
{
public:
	HTMLAdoptionList(const std::string& filename) : AdoptionList(filename)
	{
		this->writeToFile();
	}

	void writeToFile() override; 

};

