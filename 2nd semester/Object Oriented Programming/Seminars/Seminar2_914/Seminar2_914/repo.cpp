#include "repo.h"

void Repo::add(const Song& s)
{
	this->da.add(s);
}

int Repo::get_size() const
{
	return this->da.get_size();
}
