#pragma once
#include "repo.h"

class Service
{
private:
	Repo& r;

public:
	Service(Repo& r);
	void add(std::string title, std::string artist, std::string link, int minutes, int seconds);
	int get_size() const;
};

