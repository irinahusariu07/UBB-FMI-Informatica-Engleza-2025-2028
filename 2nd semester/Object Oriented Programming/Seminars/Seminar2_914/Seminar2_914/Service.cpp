#include "Service.h"

Service::Service(Repo& r): r{r}
{
}

void Service::add(std::string title, std::string artist, std::string link, int minutes, int seconds)
{
	Song s{ title, artist, link, minutes, seconds };
	this->r.add(s);
}

int Service::get_size() const
{
	return this->r.get_size();
}
