#pragma once
#include "AdoptionList.h"
#include <fstream>

class CSVAdoptionList : public AdoptionList
{
public:
	CSVAdoptionList(const std::string& filename) : AdoptionList{ filename }
	{
		this->writeToFile();
	}

	void writeToFile() override;
};
